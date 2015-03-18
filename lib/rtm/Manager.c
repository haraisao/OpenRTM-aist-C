/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Manager.c
 * \brief RTC管理用Managerファイルで、Manager構造体と各種処理関数の実装。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/OpenRTM.h>
#include <rtm/DefaultConfig.h>
#include <sys/utsname.h>

/*********************** [ Prototype (static) ] ******************************/
static void RTC_Manager_initManager(RTC_Manager *mgr, int argc, char **argv);
static void RTC_Manager_initLogger(RTC_Manager *mgr);
static void RTC_Manager_initORB(RTC_Manager *mgr);
static void RTC_Manager_initNaming(RTC_Manager *mgr);
static void RTC_Manager_initFactories(RTC_Manager *mgr);
static void RTC_Manager_initExecContext(RTC_Manager *mgr);
static void RTC_Manager_initComposite(RTC_Manager *mgr);
static void RTC_Manager_initTimer(RTC_Manager *mgr);
static void RTC_Manager_initManagerServant(RTC_Manager *mgr);
static RTC_Properties * RTC_Manager_configure(int argc, char **argv);
static RTC_Properties *RTC_Manager_setSystemInformation(RTC_Properties *prop);
static int RTC_Manager_procComponentArgs(RTC_Manager *mgr, const char *args, RTC_Properties **id, RTC_Properties **conf);
static void RTC_Manager_configureComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp, RTC_Properties *prop);

/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/*
 Create RTC_Manager and initialize...
 Called from [<Comp.c> main()].
*/
RTC_Manager *
RTC_Manager_init(int argc, char **argv)
{
  RTC_Manager *res = (RTC_Manager *)calloc(1,sizeof(RTC_Manager));

  if(res != NULL){
    RTC_Manager_initManager(res, argc, argv);
    RTC_Manager_initLogger(res);
    RTC_Manager_initORB(res);
    RTC_Manager_initNaming(res);
    RTC_Manager_initFactories(res);
    RTC_Manager_initExecContext(res);
    RTC_Manager_initComposite(res);
    RTC_Manager_initTimer(res);
    RTC_Manager_initManagerServant(res);
    res->status = RTC_INACTIVE;
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_init: fail to create manager\n");
  }

  return res;
}

/*
   set an initializing procedure of the RTComponent to the manager.
 Called from [<Comp.c> main()].
*/
void 
RTC_Manager_setModuleInitProc(RTC_Manager *manager,
                              RTC_ReturnCode_t (*init_func)(RTC_Manager *manager))
{

  if(manager != NULL){
    manager->ModuleInitProc = init_func;
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_setModuleInitProc: no manager\n");
  }
  return;
}

/*
   activate the manager.
 Called from [<Comp.c> main()].
*/
int 
RTC_Manager_activateManager(RTC_Manager *manager)
{
  int ret = 0;

  if(manager != NULL){
    if(manager->ModuleInitProc != NULL){
      RTC_ReturnCode_t res = (manager->ModuleInitProc)(manager);
      if(res == RTC_RTC_OK){
        manager->status = RTC_ACTIVE;
        ret = 1;
      }else{
         fprintf(stderr, "ERROR in RTC_Manager_activateManager: fail to initilize module\n");
      }
    }else{
      fprintf(stderr, "ERROR in RTC_Manager_activateManager: no init_func\n");
    }
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_activateManager: no manager\n");
  }
  return ret;
}

/*
   run the manager.
 Called from [<Comp.c> main()].
*/
void 
RTC_Manager_runManager(RTC_Manager *manager, ECMode_t mode)
{
  CORBA_Environment env;
  if(manager != NULL){
    manager->status = RTC_RUNNING;
    clearEnvironment(&env);
    CORBA_ORB_run(manager->m_pORB, &env);
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_runManager: no manager\n");
  }
  return;
}

/*
   stop the manager.
  (Uncalled.)
*/
void 
RTC_Manager_stopManager(RTC_Manager *manager)
{
  manager->status = RTC_INACTIVE;
  return;
}


/*
   delete the manager.
  (Uncalled.)
*/
void 
RTC_Manager_delete(RTC_Manager *manager)
{
  free(manager);
  return;
}


/*
 Called from [<Comp.c> MyModuleInit()].
*/
CORBA_RTC_RTObject
RTC_Manager_createComponent(RTC_Manager *manager, const char *comp_args)
{
  CORBA_RTC_RTObject res;
  CORBA_Environment env;
 
  RTC_Properties *id=NULL;
  RTC_Properties *conf=NULL;
  RTC_Properties *prop=NULL;
  int i;

  /* Pick out [RTC_id] [RTC_configuration] info from comp_args([id]?[configuration]) */
  if(RTC_Manager_procComponentArgs(manager, comp_args, &id, &conf) != 1) return NULL;

  /* Create new RTC_Properties data [prop] */
  prop = Properties__new("root");
  /* Append [conf] to [prop] (Only [conf], not [id]) */
  prop = Properties_appendProperties(prop, conf);
  /* Append system values (OS info, Process_id, ...) to [prop]. */
  prop = RTC_Manager_setSystemInformation(prop);

  /* Create [name] for RTC_Properties data, append related values to [prop] */
  const char *inherit_prop[] = {
      "exec_cxt.periodic.type",
      "exec_cxt.periodic.rate",
      "exec_cxt.evdriven.type",
      "naming.formats",
      "logger.enable",
      "logger.log_level",
      "naming.enable",
      "naming.type",
      ""
  };
  for(i=0; inherit_prop[i][0] != '\0' ; i++) {
    if(Properties_getProperty(prop,(char *)inherit_prop[i]) == NULL){
      Properties_setProperty(prop, (char *)inherit_prop[i],
                             Properties_getProperty(manager->m_config, (char *)inherit_prop[i]));
    } 
  }

  /* Call RTC Creator, and create RTC. */
  RTComp* comp = (manager->ModuleCreateProc)(manager);   /* call ["UserRTCname"create()] */
  if( (comp == NULL) || (comp->m_rtobjRef == NULL)) {
    fprintf(stderr, "ERROR: Fail to create a component.\n");
    return NULL;
  } else {
    manager->m_pComp = comp;
    res = manager->m_pComp->m_rtobjRef;  /* [CORBA_RTC_RTObject] object reference */
  }

  /* Append [prop] to [m_properties] of created object. */
  RTC_RTObject_appendProperties(res, prop);

  /* Create RTC's instance name */
  char inst_name[MAX_STRBUF];
  sprintf(inst_name, "%s%d",  RTC_RTObject_getTypeName(res), manager->m_counter); /* ex) SampleRTC1 */
  manager->m_counter += 1;  /* increment instance counts */

  /* Set instance name to  [m_properties] of created object as "instance_name". */
  RTC_RTObject_setInstanceName(res,inst_name);

  /* Append properties(config_file/NameServer/...) to [m_properties] of created object. */
  RTC_Manager_configureComponent(manager, res, prop);

  /* Call initialize(), error check, exit() */
  clearEnvironment(&env);
  if ( RTC_RTObject_initialize(res, &env) != RTC_RTC_OK){
    fprintf(stderr, "ERROR: Fail to initialize a component.\n");
    RTC_RTObject_exit(res, &env);  /* ==>  RTC_LightweightRTObject_exit() */
    return NULL;
  }

  /* Bind RTC to NameServer */
  fprintf(stderr, "=== registerComponent === \n");
  RTC_Manager_registerComponent(manager, res);
  fprintf(stderr, "=== done === \n");

  return res;
}

/*
 Called from [[USER_RTCOMP] Init() func.
*/
void
RTC_Manager_registerFactory(RTC_Manager *manager, const char **profile,
                            RTComp* (*create_func)(RTC_Manager *manager),
			    void (*delete_func)(RTComp *obj))
{
  manager->ModuleCreateProc = create_func;
  manager->ModuleDeleteProc = delete_func;
  manager->ModuleProfile = (char**)profile;

  return;
}


/*
 Called from [RTC_Manager_createComponent()].
*/
void
RTC_Manager_registerComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp)
{
  int i,len;
  char **names;

  fprintf(stderr, " ===> registerComponet \n");
  names = RTC_RTObject_getNamingNames(comp, &len);

  fprintf(stderr, " len=%d, names ===> %s \n", len, names[0]);
  for (i = 0; i < len; ++i){
    /* Bind */
    RTC_NamingManager_bindObject(mgr->m_namingManager, names[i], comp);
  }
  fprintf(stderr, " [NameServer] Binding RTC to NameServer is done.\n");

  return;
}

/*
 Called from [].
*/
void
RTC_Manager_unregisterComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp)
{
  int i,len;
  char **names;

  names = RTC_RTObject_getNamingNames(comp, &len);

  for (i = 0; i < len; ++i){
    /* Unbind */
    RTC_NamingManager_unbindObject(mgr->m_namingManager, names[i]);
  }
  fprintf(stderr, " [NameServer] Unbinding RTC to NameServer is done.\n");

  return;
}


/*****************************************************************************/
/********************* [ static functions ] **********************************/
/*****************************************************************************/

/*!
 * \brief 生成した[RTC_Manager]型データ内の要素に初期値をセットする。さらに、[m_config]にデフォルトプロパティ値をセットする。[RTC_Manager_init()]からcallされる関数。
 *
 *        (1) 要素[argc][argv]を引数のデータからセットし、[m_counter]は"0"にする。 <BR>
 *        (2) [RTC_Manager_configure()]をcallし、[m_config]に[RTC_Properties]型データ([デフォルト値/システム情報/rtc.confで指定の値]などセット済み)のポインタをセットする。
 * \param mgr [RTC_Manager]型データ
 * \param argc Managerオプション用引数(未使用)
 * \param argv Managerオプション用引数(未使用)
 * \return void
 */
static void
RTC_Manager_initManager(RTC_Manager *mgr, int argc, char **argv)
{
  mgr->argc = argc;
  mgr->argv = argv;
  mgr->m_counter = 0;
  mgr->m_config = RTC_Manager_configure(argc, argv);

#if 0
  mgr->m_module = ModuleManager__new(mgr->m_config);
  mgr->m_terminator = Terminator__new(mgr);
#endif

  return;
}


/*!
 * \brief (未実装)  [RTC_Manager_init()]からcallされる関数。
 */
static void
RTC_Manager_initLogger(RTC_Manager *mgr)
{
  return;
}


/*!
 * \brief 引数[mgr]の要素の[CORBA_ORB/POA/POAManager]をそれぞれ生成する。　[RTC_Manager_init()]からcallされる関数。
 * \param mgr [RTC_Manager]型データ
 * \return void
 */
static void
RTC_Manager_initORB(RTC_Manager *mgr)
{
  CORBA_Environment env;

  /* ORB initialization */
  mgr->m_pORB = (CORBA_ORB)CORBA_ORB_init(&mgr->argc, mgr->argv, 0, &env);

  /* Get the RootPOA */
#if 0
  CORBA_Object poa_obj = CORBA_ORB_resolve_initial_references(mgr->m_pORB, "RootPOA", &env);
  mgr->m_pPOA = poa_obj->poa;
#else
  mgr->m_pPOA = The_RootPOA;
#endif

  catchDefaultException(&env);

  /* Get the POAManager */
  mgr->m_pPOAManager =
         (PortableServer_POAManager)PortableServer_POA__get_the_POAManager(mgr->m_pPOA, &env);

  PortableServer_POAManager_activate(mgr->m_pPOAManager, &env);

  return;
}


/*!
 * \brief NameServer情報の[RTC_NamingManager]型データの生成。　[RTC_Manager_init()]からcallされる関数。
 *
 *        (1) [RTC_NamingManager]型データを生成し、引数[mgr]の要素[m_namingManager]にセットする。<BR>
 *        (2) プロパティデータ[m_config]から、["naming.type"]に対応する値を取得する。(初期値:["corba"]) <BR>
 *        (3) (2)で生成した文字列と".nameservers"を合体させた文字列に対応する値を取得する。(初期値:["corba.nameservers"])<BR>
 *        (4) (3)で生成した文字列に対応する値を[m_config]から取得する。(初期値:["ocalhost:2809"]) <BR>
 *        (5) [RTC_NamingManager_registerNameServer()]をcallし、[m_namingManager]内に、NameServerの情報をセットする。(RTCを登録する際には、その情報を元にNameServerにアクセスする。)
 * \param mgr [RTC_Manager]型データ
 * \return void
 */
static void
RTC_Manager_initNaming(RTC_Manager *mgr)
{
  char *type;

  /* Create [NamingManager] and set pointer mutually ([Manager]<->[NamingManager]) */
  mgr->m_namingManager = RTC_NamingManager__new(mgr);

  /* [naming.type] ==> method */
  type = Properties_getProperty(mgr->m_config, "naming.type"); /* (Def : "corba") */
  if(type == NULL){
    fprintf(stderr, "Invalid naming.type\n");
  }else{
    int i;
    string_sequence *meth = split_string(type, ',', 0);
    for(i=0; i<meth->length;i++){
      char ns[MAX_STRBUF];
      char *nss;
      int j;
      sprintf(ns, "%s.nameservers", meth->buffer[i]);  /* (Def : "corba.nameservers") */
      nss = Properties_getProperty(mgr->m_config, ns); /* (Def : "localhost:2809") */
      string_sequence *names = split_string(nss, ',', 0);
      /* Create NameServer's info */
      for(j=0;j<names->length;j++){
        RTC_NamingManager_registerNameServer(mgr->m_namingManager, meth->buffer[i], names->buffer[j]);
      }
      free_string_sequence(names);
    }
    free_string_sequence(meth);
  }
  return;
}


/*!
 * \brief (未実装)　[RTC_Manager_init()]からcallされる関数。
 */
static void
RTC_Manager_initFactories(RTC_Manager *mgr)
{
  return;
}


/*!
 * \brief ECの初期化処理。　[RTC_Manager_init()]からcallされる関数。(現在、未使用）
 * \param mgr [RTC_Manager]型データ
 * \return void
 */
static void
RTC_Manager_initExecContext(RTC_Manager *mgr)
{
  RTC_PeriodicExecutionContextInit(mgr);
  RTC_ExtTrigExecutionContextInit(mgr);
  RTC_OpenHRPExecutionContextInit(mgr);

  return;
}


/*!
 * \brief Composite型(複合RTC)の初期化処理。[RTC_Manager_init()]からcallされる関数。（現在、未使用）
 * \param mgr [RTC_Manager]型データ
 * \return void
 */
static void
RTC_Manager_initComposite(RTC_Manager *mgr)
{
  RTC_PeriodicECSharedCompositeInit(mgr);

  return;
}


/*!
 * \brief (未実装)　[RTC_Manager_init()]からcallされる関数。
 */
static void
RTC_Manager_initTimer(RTC_Manager *mgr)
{
  return;
}


/*!
 * \brief RTCをローダブル可能なManagerのManagerServant([RTM_Manager]型オブジェクト)を生成し、管理するユーザRTCをNameServerへ登録する。　[RTC_Manager_init()]からcallされる関数。 (現状、未使用)
 * \param mgr [RTC_Manager]型データ
 * \return void
 */
static void
RTC_Manager_initManagerServant(RTC_Manager *mgr)
{
#if 0
  CORBA_Environment ev;
  int i, len;
  RTC_Properties *prop;
  string_sequence *names;

  mgr->m_mgrservant = impl_RTM_Manager__create(mgr->m_pPOA, &ev);

  prop = Properties_getNode(mgr->m_config,"manager");

  char *value = Properties_getProperty(prop,"naming_formats");

  if(value == NULL){
    names = split_string(value, ',', 0);
  }

  char *is_master = Properties_getProperty(prop,"is_master");

  if(is_master != NULL &&  strcmp(is_master, "YES") == 0){
    for(i=0;i<names->length;i++){
      char *mgr_name = Properties_formatString(names->buffer[i], prop);
      RTC_NamingManager_bindObject(mgr->m_namingManager, mgr_name, mgr->m_mgrservant);
    }
  }
#else
  mgr->m_mgrservant = NULL;
#endif
  return;
}


/*!
 * \brief [RTC_Properties]型データを新規生成し、「デフォルト値」「システム情報」「rtc.confで指定の値」の各種プロパティ情報をセットし、そのポインタ[res]を返す。<BR> [RTC_Manager_initManager()]からcallされる関数。
 *
 *        (1) RTCのConfファイルとして、["rtc.conf"]を指定する。<BR>
 *        (2) [Properties_make_system_default()]をcallし、「DefaultConfig.h」で用意された「default_config[]」のデフォルト値を[res]として取得する。<BR>
 *        (3) [RTC_Manager_setSystemInformation()]をcallし、[res]にOSなどのシステム情報をプロパティとして追加セットする。<BR>
 *        (4) [Properties_load()]をcallし、引数の[fname]に指定されたファイル([rtc.conf][RTC名.conf]など)の中身に記述された、プロパティ情報を読み込み、[res]に追加セットする。
 * \param argc Managerオプション用引数 (未使用)
 * \param argv Managerオプション用引数 (未使用)
 * \return 生成した[RTC_Properties]型データ
 */
static RTC_Properties *
RTC_Manager_configure(int argc, char **argv)
{
  const char conf_file_name[] = "./rtc.conf";
  RTC_Properties *res = NULL;

#if 0
  /*** parse argument and set options **/
  res = Properties_setDefaults(res, argv, argc);
#endif

  /* Set default values (default_config[]) */
  res = Properties_make_system_default();

  /* Set system values (OS info, Process_id, ...) */
  res = RTC_Manager_setSystemInformation(res);

  /* Set config_file's values ("rtc.conf", etc) */
  res = Properties_load(res, (char *)conf_file_name);


#if 1
  /* Dump properties */
  Properties_dumpProperties(res, 0);
#endif

  return res;
}


/*!
 * \brief 引数の[RTC_Properties]型データ[prop]に、内部取得したOSのシステム情報やプロセスIDなどを、"manager."で始まるnameに対応したvalue値としてセットする。 <BR> [RTC_Manager_createComponent(),RTC_Manager_configure()]からcallされる関数。
 * \param prop OS情報などをセットする[RTC_Properties]型データ
 * \return データセット後の[RTC_Properties]型データ
 */
static RTC_Properties *
RTC_Manager_setSystemInformation(RTC_Properties *prop)
{
    char pidc[8];
    struct utsname sysinfo;
    uname(&sysinfo);
    sprintf(pidc, "%d", getpid());

    prop = Properties_setProperty(prop, "manager.os.name",     sysinfo.sysname);
    prop = Properties_setProperty(prop, "manager.os.release",  sysinfo.release);
    prop = Properties_setProperty(prop, "manager.os.version",  sysinfo.version);
    prop = Properties_setProperty(prop, "manager.os.arch",     sysinfo.machine);
    prop = Properties_setProperty(prop, "manager.os.hostname", sysinfo.nodename);
    prop = Properties_setProperty(prop, "manager.pid",         pidc);

  return prop;
}


/*!
 * \brief 引数文字列からコンポーネント型名・プロパティを抽出する。 <BR> [RTC_Manager_createComponent()]からcallされる関数。
 *
 *        (1)引数[args]を[ID]/[Conf]部分に区切り文字"?"で分割する。<BR>
 *        (2)[ID]部分について、ImplementIDとオプションの個数を区切り文字":"で算出する。<BR>
 *        (3)[ID]部分について、(2)の個数に応じて、各情報を、引数のRTC_Properties型の[id]にセットする。<BR>
 *        (4)デフォルトのRTC情報(spec[])を、引数のRTC_Properties型の[conf]にセットする。<BR>
 *        (5)[Conf]部分について、[name/value]のペアを区切り文字"&"で、[name][value]自体を区切り文字"="で分割し、引数のRTC_Properties型の[conf]にセットする。<BR>
 *        (6)全ての処理が正常終了すれば[1]を、失敗すれば[0]を返す。
 *
 *        [引数{args}について] (OpenRTM-aist-C++説明より引用) <BR>
 *          文字列からコンポーネント型とコンポーネントのプロパティを抽出する。 与えられる文字列のフォーマットは RTC の ID とコンフィギュレーショ ンからなる。<BR>
 * comp_args:     [id]?[configuration]形式。 [id]は必須、[configuration]はオプション。<BR>
 * id形式:        [implementation_id]のみの指定。もしくは、以下のフォーマット形式。 <BR>
                  RTC:[vendor]:[category]:[implementation_id]:[version]<BR>
 *                "RTC"は固定、[implementation_id]は必須で、[vendor], [category], [version]は任意の指定。オプションを省略する場合でも ":" は省略不可<BR>
 * configuration: [key0]=[value0]&[key1]=[value1]&[key2]=[value2].....の形式で指定。<BR>
 *                RTCが持つPropertiesの値をすべて上書き可能。key=value の形式で記述し、"&" で区切る。<BR>
 * (例1) args = "SampleRTC" <BR>
 * (例2) args = "RTC:jp.go.aist:example:ConfigSample:1.0?conf.default.str_param0=munya" <BR>
 * (例3) args = "RTC::example:ConfigSample:?conf.default.int_param0=100" <BR>
 * [id] は、 "vendor", "category", "implementation_id", "version" のキーを持つ Properties 型のオブジェクトとして返される。<BR>
 * [conf] には "?" 以下に記述されるコンポーネントに与えるプロパティ が Properties 型のオブジェクトとして返される。
 *
 * \param mgr [RTC_Manager]型データ
 * \param args 抽出元となる文字列
 * \param id [ID]部抽出データセット用のRTC_Properties型データポインタ
 * \param conf [Configuration]部抽出データセット用のRTC_Properties型データポインタ
 * \return 正常:[1]、抽出エラー:[0]
 */
static int
RTC_Manager_procComponentArgs(RTC_Manager *mgr, const char *args, RTC_Properties **id, RTC_Properties **conf)
{
  int count;

  /* Split [args] to [ID],[Conf] parts by delimiter "?". */
  string_sequence *id_and_conf = split_string((char *)args, '?', 0); 

  if(id_and_conf->length > 2){
    fprintf(stderr, "Invalid arguments. Too more '?' in arg: %s\n", args);
    free_string_sequence(id_and_conf);
    return 0;
  }

  /* Calculate counts of [RTC_id] options by delimiter ":" from [ID] part. */
  count = count_delim(id_and_conf->buffer[0], ':');

  /* Set [RTC_id] info to [id](RTC_Properties). */
  if(count == 0){
    *id = Properties_setProperty(NULL, "RTC", "RTC");
    *id = Properties_setProperty(NULL, "vendor", "");
    *id = Properties_setProperty(NULL, "category", "");
    *id = Properties_setProperty(NULL, "implementation_id", id_and_conf->buffer[0]);
    *id = Properties_setProperty(NULL, "version", "");
  }else if(count == 4){
    string_sequence *id_prop;
    id_prop = split_string((char *)args, ':', 0);
    *id = Properties_setProperty(NULL, "RTC", id_prop->buffer[0]);
    *id = Properties_setProperty(NULL, "vendor", id_prop->buffer[1]);
    *id = Properties_setProperty(NULL, "category", id_prop->buffer[2]);
    *id = Properties_setProperty(NULL, "implementation_id", id_prop->buffer[3]);
    *id = Properties_setProperty(NULL, "version", id_prop->buffer[4]);
    free_string_sequence(id_prop);
  }else{
    fprintf(stderr, "Invalid id type: %s\n", id_and_conf->buffer[0]);
    free_string_sequence(id_and_conf);
    return 0;
  }

  /* Set default RTC's properties(spec[]) to [conf](RTC_Properties). */
  *conf = Properties_createDefaultProperties((const char **)mgr->ModuleProfile);

  if(id_and_conf->length == 2){
    int i;
    /* Split [Conf] part to {[name]=[value]} pairs. */
    string_sequence *confs = split_string(id_and_conf->buffer[1],'&',0);
    
    for(i=0; i<confs->length; i++){
     /* Split {[name]=[value]} pairs to [name] and [value] data. */
      string_sequence *keyval = split_string(confs->buffer[i], '=', 0);
      if(keyval->length == 2){
         /* Set [name] and [value] data to [conf](RTC_Properties). */
         *conf = Properties_setProperty(*conf, keyval->buffer[0], keyval->buffer[2]);
      }
      free_string_sequence(keyval);
    }
    free_string_sequence(confs);
  }

  free_string_sequence(id_and_conf);

  return 1;
}


/*!
 * \brief RTCのプロパティ情報を定義出来る、Configファイルが存在する場合に、中身の情報をRTCのプロパティとして設定する。さらに、RTCのNameService登録用の名称生成し、RTCのプロパティとして設定する。 <BR> [RTC_Manager_createComponent()]からcallされる関数。
 *
 *        (1) [category][type_name][instance_name]情報を、引数[comp]が持つPropertiesデータから取得する。<BR>
 *        (2) RTCのConfigファイル名をvalueとしてセットする時の[name]を生成する([type_conf][name_conf])。 <BR>
 *        (3) (2)の[name]から、該当するファイル名(value)が存在すれば取得し、そのファイルをOpenし、中身のプロパティ情報を取得し、RTCのプロパティとして設定する。 <BR>
 *        (4) NameServer登録用のプロパティ[naming_formats][naming_name]を生成し、RTCのプロパティとして設定する。
 *
 * \param mgr [RTC_Manager]型データ
 * \param comp 対象のRTCのRTC_RTObjectオブジェクト
 * \param prop (未使用)
 * \return void
 */
static void
RTC_Manager_configureComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp, RTC_Properties *prop)
{
  RTC_Properties *type_prop=NULL, *name_prop=NULL;
  char type_conf[128], name_conf[128];
  char naming_formats[MAX_STRBUF];
  char *naming_name;

  /* Get [category][type_name][instance_name] from RTC's properties. */
  char *category  = RTC_RTObject_getCategory(comp);
  char *type_name = RTC_RTObject_getTypeName(comp);
  char *inst_name = RTC_RTObject_getInstanceName(comp);
  if(category == NULL){
   fprintf(stderr, "ERROR: category not found\n");
   return ;
  }
  if(type_name == NULL){
   fprintf(stderr, "ERROR: type_name not found\n");
   return ;
  }
  if(inst_name == NULL){
   fprintf(stderr, "ERROR: inst_name not found\n");
   return ;
  }

  /* Make RTC's Configuration files. */
  sprintf(type_conf, "%s.%s.config_file", category, type_name);
  sprintf(name_conf, "%s.%s.config_file", category, inst_name);

  /* Open files, read cotents, and set to RTC_Properties data. */
  char *conf_file  = Properties_getProperty(mgr->m_config, name_conf);
  if(conf_file != NULL){
    Properties_load(name_prop, conf_file);
  }
  char *type_file  = Properties_getProperty(mgr->m_config, type_conf);
  if(type_file != NULL){
    Properties_load(type_prop, type_file);
  }

  /* Append [name_prop] and [type_prop] to [RTC's properties] */
  Properties_appendProperties(type_prop, name_prop);
  RTC_RTObject_appendProperties(comp, type_prop);
 
  /* Create "naming.formats" string. */
  sprintf(naming_formats, "%s, %s"
         ,Properties_getProperty(mgr->m_config, "naming.formats")
         ,RTC_RTObject_getProperty(comp, "naming.formats") );

  /* Create "naming.names" string. */
  naming_name = Properties_formatString(naming_formats, RTC_RTObject_getProperties(comp));

  /* Append [naming_formats] and [naming_name] to [RTC's properties] */
  RTC_RTObject_setProperty(comp, "naming.formats", strdup(naming_formats));  /* for NameServer */
  RTC_RTObject_setProperty(comp, "naming.names", naming_name); /* for NameServer */
  free(naming_name);

  return;
}

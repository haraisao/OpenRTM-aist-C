/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file NamingManager.c
 * \brief Naming Manager (NameServer情報の取得、NameServer登録用RTC情報の生成、NameServerへのRTC登録/解除処理)
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/OpenRTM.h>

/***************** [ Prototype declaration (static) ] ************************/
static RTC_NamingBase *NamingOnCorba__new(CORBA_ORB orb, char *name_server);
static int NamingOnCorba_resolve(RTC_NamingBase *nb);
static void NamingOnCorba_delete(RTC_NamingBase *nb);
static RTC_NamingBase *RTC_NamingBase_createNamingObj(RTC_NamingManager *nm, char *method, char *name_server);
static RTC_Name *RTC_Name__new(char *method, char *name_server, RTC_NamingBase *name);
static void RTC_NamingManager_appendNamingBase(RTC_NamingManager *mgr, RTC_Name *name);
static int RTC_NamingBase_bindObject(RTC_NamingBase *nb, const char *name, const CORBA_Object obj);
static int RTC_NamingBase_unbindObject(RTC_NamingBase *nb, const char *name);

/*****************************************************************************/
/**************************** [ Functions ] **********************************/
/*****************************************************************************/

/*
 Create RTC_Manager and initialize...
 Called from [RTC_Manager_initNaming()].
*/
RTC_NamingManager *
RTC_NamingManager__new(RTC_Manager *mgr)
{
  RTC_NamingManager *res = NULL;
  res = (RTC_NamingManager *)calloc(1,sizeof(RTC_NamingManager));
  if (res != NULL) {
    res->m_manager = mgr; /* Set pointer mutually ([Manager]<->[NamingManager]) */
  }

  return res;
}


/*
 Called from [<Manager> RTC_Manager_initNaming()].
*/
void
RTC_NamingManager_registerNameServer(RTC_NamingManager *mgr, const char *method, const char *name_server)
{
  RTC_NamingBase* name = NULL;
  fprintf(stderr, "	registerNameServer: (%s : %s)\n",method, name_server);
    /* (Def: [method]="corba", [name_server]="localhost:2809") */

  /* Create [RTC_NamingBase] */
  name = RTC_NamingBase_createNamingObj(mgr, (char *)method, (char *)name_server);
  
  /* Append new NameServer([RTC_Name]) to [RTC_NamingManager] */
  RTC_NamingManager_appendNamingBase(mgr, 
	RTC_Name__new((char *)method, (char *)name_server, name));

  return;
}


/*
 Called from [RTC_Manager_initManagerServant(), RTC_Manager_registerComponent()].
*/
void
RTC_NamingManager_bindObject(RTC_NamingManager *mgr, const char *name, const RTC_RTObject rtobj)
{
  int i;

  for(i=0; i < mgr->n_name; i++){
    /* Get NameServer info */
    RTC_NamingBase *nb = mgr->m_names[i]->name;
    if (nb != NULL){
      /* Bind RTC to NameServer */
      RTC_NamingBase_bindObject(nb, name, rtobj);
    }
  }

  return;
}


/*
 (未実装)
*/
void
RTC_NamingManager_update(RTC_NamingManager *mgr)
{
  return;
}


/*
 (Uncalled).  from Shutdown()
*/
void
RTC_NamingManager_unbindObject(RTC_NamingManager *mgr, const char *name)
{
  int i;

  for(i=0; i < mgr->n_name; i++){
    /* Get NameServer info */
    RTC_NamingBase *nb = mgr->m_names[i]->name;
    if (nb != NULL){
      /* Unbind RTC from NameServer */
      RTC_NamingBase_unbindObject(nb, name);
    }
  }

  return;
}


/*
 (未実装)
*/
void
RTC_NamingManager_unbindAll(RTC_NamingManager *mgr)
{
  return;
}


/*****************************************************************************/
/********************* [ static functions ] **********************************/
/*****************************************************************************/

/*
 Called from [RTC_NamingBase_createNamingObj()].
*/
/*!
 * \brief [static] [RTC_NamingBase]構造体のメモリ確保し、要素[name_server][orb]にそれぞれ引数の値をセットし、そのポインタをreturnする。
 * \param orb CORBA_ORB
 * \param name_server NameServer名
 * \return 生成した[RTC_NamingBase]構造体のポインタ、失敗時は[NULL]。
 */
static RTC_NamingBase *
NamingOnCorba__new(CORBA_ORB orb, char *name_server)
{
  RTC_NamingBase *res = NULL;
  res = (RTC_NamingBase *)calloc(1, sizeof(RTC_NamingBase));
  if (res != NULL) {
    res->name_server = strdup(name_server); 
    res->orb = orb; 
  }

  return res;
}


/*
 Called from [RTC_NamingBase_createNamingObj()].
*/
/*!
 * \brief [static] 引数の要素の[name_server]より、[CORBA_Loc]形式の文字列を生成し、それをコンバートし、[NameServer]の[NamingContext]型のオブジェクトリファレンスを得て、[RTC_NamingBase]の要素[rootContext]にセットする。<BR>
 *        成功すれば[0]、失敗すれば[-1]を返す。
 * \param nb 作成済みの[RTC_NamingBase]型データ
 * \return "0":Success, "-1":Fail
 */
static int
NamingOnCorba_resolve(RTC_NamingBase *nb)
{
  int res = -1;
  char loc[256];

  clearEnvironment(&nb->env);

  /* Create [Corbaloc] and convert to NamingContext object as [rootContext] */
  sprintf(loc, "corbaloc::%s/NameService", nb->name_server);
  nb->rootContext = CORBA_ORB_string_to_object(nb->orb, loc, &nb->env); /* <RtORB> */
  if(nb->rootContext == NULL){
    fprintf(stderr, "ERROR : in string_to_object\n\n");
  } 
  res = catchDefaultException(&nb->env); /* [CORBA_NO_EXCEPTION = "0"] is succeed. */

  return res;
}


/*
 Called from [RTC_NamingBase_createNamingObj()].
*/
/*!
 * \brief [static] 作成済みの[RTC_NamingBase]型データを削除(free)する。
 * \param nb 作成済みの[RTC_NamingBase]型データ
 * \return void
 */
static void
NamingOnCorba_delete(RTC_NamingBase *nb)
{
  free(nb->name_server);
  free(nb);
  return;
}


/*
 Called from [RTC_NamingManager_registerNameServer()].
*/
/*!
 * \brief [static] 引数の[nm]内のManager内の[ORB]と、[method]、[name_server]を使い、[RTC_NamingBase]型データを生成し、中身の要素(orb/name_server/rootContext)にセットし、ポインタを返す。失敗したら、[NULL]を返す。 
 *
 *        [RTC_NamingManager_registerNameServer()]よりcallされ、内部で、[NamingOnCorba__new()],[NamingOnCorba_resolve()], [NamingOnCorba_delete()]の3関数をcallする。
 * \param nm 新規作成済みの[RTC_NamingManager]型データ
 * \param method 通信メソッド(デフォルト:"corba")
 * \param name_server NameServer名
 * \return 内部で生成した[RTC_NamingBase]型データ、失敗時は[NULL]。
 */
static RTC_NamingBase *
RTC_NamingBase_createNamingObj(RTC_NamingManager *nm, char *method, char *name_server)
{
  RTC_NamingBase *res = NULL;

  if(strcmp(method, "corba") == 0){
    /* Create RTC_NamingBase data and set [orb],[name_server] */
    res = NamingOnCorba__new(nm->m_manager->m_pORB, name_server);
    if(res == NULL){
      /* Fail */
      fprintf(stderr, "ERROR in create NamingOnCorba: (%s)\n", name_server);
    }else{
      /* Get NamingContext object by [name_server] */
      if(NamingOnCorba_resolve(res) == 0){
        /* Success */
        fprintf(stderr, "=== NameServer resolve suceeded:%s/%s ===\n"
                      , method, name_server);
      }else{
        /* Fail */
        fprintf(stderr, "=== NameServer resolve fail:%s/%s ===\n"
                      , method, name_server);
        NamingOnCorba_delete(res); /* free action */
        res = NULL;
      }
    }  
  }else{
    /* Fail */
    fprintf(stderr, "Sorry, unsupport type of NamingService required. (%s)\n", method);
  }

  return res;
}


/*
 Called from [RTC_NamingManager_registerNameServer()].
*/
/*!
 * \brief [static] RTC_Name型データを生成し、引数を[method][name_server][name]にそれぞれセットし、そのポインタを返す、失敗時は[NULL]を返す。
 *
 *  [RTC_NamingManager_registerNameServer()]よりcallされる。
 * \param method 通信メソッド(デフォルト:"corba")
 * \param name_server NameServer名
 * \param name 作成済みの[RTC_NamingBase]型データ
 * \return 生成した[RTC_Name]構造体のポインタ、失敗時は[NULL]。
 */
static RTC_Name *
RTC_Name__new(char *method, char *name_server, RTC_NamingBase *name)
{
  RTC_Name *res = NULL;
  res = (RTC_Name *)malloc(sizeof(RTC_Name));

  if (res != NULL) {
    res->methods = strdup(method);
    res->nsname = strdup(name_server);
    res->name = name;
  }

  return res;
}


/*
 Called from [RTC_NamingManager_registerNameServer()].
*/
/*!
 * \brief [static] 作成済みの[RTC_NamingManager]型データに、作成済みの[RTC_Name]型データ(NameServer情報)を追加する。
 *
 *        この時、内部でメモリの再確保やカウンタのインクリメントが行われる。<BR>
 *        [RTC_NamingManager_registerNameServer()]よりcallされる。
 * \param mgr 作成済みの[RTC_NamingManager]型データ
 * \param name 作成済みの[RTC_Name]型データ
 * \return void
 */
static void
RTC_NamingManager_appendNamingBase(RTC_NamingManager *mgr, RTC_Name *name)
{
  /* Create(new) or Reallocate */
  if(mgr->n_name == 0){   
    mgr->m_names = malloc(sizeof(RTC_Name *));
  }else{
    mgr->m_names = realloc(mgr->m_names, sizeof(RTC_Name *) * (mgr->n_name + 1));
  }

  /* Append [RTC_Name] as last elements */
  mgr->m_names[mgr->n_name] = name;

  /* Increment counter */
  if(mgr->m_names != NULL){
    mgr->n_name += 1;
  }
  return;
}


/*
 Called from [RTC_NamingManager_bindObject()].
*/
/*!
 * \brief [static] [RTC_NamingBase]型データに格納されているNameServer情報と、引数の[name][rtobj]より、登録するRTC情報を用いて、NameServerへの登録(bind)を行う。
 *
 *        [CosNaming_Name]型データを生成し、引数の[name]から、登録すべきRTCの情報[id][kind]を生成する。<BR>
 *        NameServerの[rootContext]とRTCの[CORBAオブジェクト]と生成した[CosNaming]データを引数として、CosNaming_NamingContext_rebind()関数をcallすることで、NameServer側に情報が正式に登録される。<BR>
 * 成功すれば[1]、失敗すれば[0]を返す。
 * \param nb 生成済みの[RTC_NamingBase]データ(NameServer情報)
 * \param name 登録するRTCの名前("naming.formats"で指定された形式の文字列)
 * \param obj 登録するRTCのCORBAオブジェクト
 * \return 成功[1]/失敗[0]
 */
static int RTC_NamingBase_bindObject(RTC_NamingBase *nb, const char *name, const CORBA_Object obj)
{
  CosNaming_Name *namingName;
  string_sequence *names = split_string((char*)name, '/',0);
  int i;

  /* Create [CosNaming_Name] data */
  namingName = CosNaming_Name__alloc();
  namingName->_buffer = CosNaming_Name_allocbuf(names->length);
  namingName->_length = namingName->_maximum = names->length;

  for(i=0;i<names->length;i++){
    char *nn = names->buffer[i];
    if(count_delim(nn, '.') > 0){
      char *str = rindex(nn, '.'); 
      char str1[256];
      memset(str1, 0, 256);
      strncpy(str1, nn, strlen(nn) - strlen(str));
      namingName->_buffer[i].id = strdup(str1);    /* [NameComponent].[id] */
      namingName->_buffer[i].kind = strdup(str+1); /* [NameComponent].[kind] */
    }
  }

  /* Bind to NameServer([CosNaming]) */
  clearEnvironment(&nb->env);
  CosNaming_NamingContext_rebind(nb->rootContext, namingName, obj, &nb->env); 
  if(catchException(&nb->env, NULL) ){
    fprintf(stderr, " [ERROR] <NameServer> Can't Bind Object. [repo_id=%s]\n", nb->env._repo_id);
    return 0; /* Fail */
  }

  /* free */  
  for(i=0; i < namingName->_maximum ;i++){
    free(namingName->_buffer[i].id);
    free(namingName->_buffer[i].kind);
  }
  free(namingName->_buffer);
  free(namingName);
  
  free_string_sequence(names);

  return 1;
}


/*
 Called from [RTC_NamingManager_unbindObject()].
*/
/*!
 * \brief [static] [RTC_NamingBase]型データに格納されているNameServer情報と、引数の[name]より、複数のNameServerから、登録されているRTCを解除/消去する。 
 *
 *        [CosNaming_Name]型データを生成し、引数の[name]から、解除/消去すべきRTCの情報[id][kind]を生成する。<BR>
 *        NameServerの[rootContext]と生成した[CosNaming]データを引数として、CosNaming_NamingContext_unbind()関数をcallすることで、NameServer側から情報が正式に解除/消去される。<BR> 
 *  成功すれば[1]、失敗すれば[0]を返す。
 * \param nb 生成済みの[RTC_NamingBase]データ(NameServer情報)
 * \param name 登録されているRTCの名前("naming.formats"で指定された形式の文字列)
 * \return 成功[1]/失敗[0]
 */
static int RTC_NamingBase_unbindObject(RTC_NamingBase *nb, const char *name)
{
  CosNaming_Name *namingName;
  string_sequence *names = split_string((char*)name, '/',0);
  int i;

  /* Create [CosNaming_Name] data */
  namingName = CosNaming_Name__alloc();
  namingName->_buffer = CosNaming_Name_allocbuf(names->length);
  namingName->_length = namingName->_maximum = names->length;

  for(i=0;i<names->length;i++){
    char *nn = names->buffer[i];
    if(count_delim(nn, '.') > 0){
      char *str = rindex(nn, '.'); 
      char str1[256];
      memset(str1, 0, 256);
      strncpy(str1, nn, strlen(nn) - strlen(str));
      namingName->_buffer[i].id = strdup(str1);    /* [NameComponent].[id] */
      namingName->_buffer[i].kind = strdup(str+1); /* [NameComponent].[kind] */
    }
  }

  /* Unbind from NameServer([CosNaming]) */
  clearEnvironment(&nb->env);
  CosNaming_NamingContext_unbind(nb->rootContext, namingName, &nb->env); 
  if(catchException(&nb->env, NULL) ){
    fprintf(stderr, " [ERROR] <NameServer> Can't Unbind Object. [repo_id=%s]\n", nb->env._repo_id);
    return 0; /* Fail */
  }

  /* free */  
  for(i=0; i < namingName->_maximum ;i++){
    free(namingName->_buffer[i].id);
    free(namingName->_buffer[i].kind);
  }
  free(namingName->_buffer);
  free(namingName);
  
  free_string_sequence(names);

  return 1;
}


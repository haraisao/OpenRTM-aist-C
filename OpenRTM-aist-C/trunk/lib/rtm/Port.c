/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Port.c
 * \brief RTCが保持するDataPortの管理全般と各種操作を行う。
 *
 * 「OpenRTM-aist-C++」の「PortAdmin」「PortBase」の必要機能を統合し、C言語版用に整備したもの。
 *
 *「PortServiceList」を管理するPortAdmin構造体の生成と、それらの取得処理機能や、DataPort全般の操作に関わるファイルDataPort管理用構造体と、DataPort(PortService)の生成+削除/可変長データ型処理/CDRデータMarshal+Unmarshal/PortProfileの生成+取得などの操作を行う関数群からなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/OpenRTM.h>
#include <rtm/Port.h>

/*********************** [ Prototype (static) ] ******************************/
/* =========================== [ Create ] ================================== */
static void Port_createRepositryID(const char* type_name, char* repoid);
static CORBA_TypeCode Port_getTypeCode(char* repoid);
static void Port_splitDataTypeName(const char *src, char* dest, CORBA_TypeCode tc);
static CORBA_RTC_PortService Port_create_PortService(CORBA_RTC_RTObject rtobj, const char *port_name, char *type_name, DataPortType port_type);
static CORBA_RTC_PortService Port_set_PortService(CORBA_RTC_RTObject obj);
static RTC_PortAdmin *Port_newPortAdmin();
static void Port_set_PortProfile(CORBA_RTC_PortService portobj, const char *port_name, CORBA_RTC_RTObject rtobj, char *data_type_name, DataPortType port_type);
static int Port_create_DataPortBase(RTC_DataPortBase *port, DataPortType port_type,  CORBA_TypeCode tc, CORBA_RTC_PortService psobj);
static void *Port_alloc_by_TypeCode(CORBA_TypeCode tc);
/* =========================== [ Delete ] ================================== */
static void Port_delete_DataPortBase(RTC_DataPortBase *port);
static void Port_delete_PortService(CORBA_RTC_RTObject rtobj);
static void Port_free_by_TypeCode(CORBA_TypeCode tc, void *val);
/* ========================== [ Sequence ] ================================= */
static CORBA_TypeCode Port_getIndexOfTypeCode(CORBA_TypeCode tc, int* idx, const char* value_name);

/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/* =========================== [ Create ] ================================== */

/*
 Called from [RTC_OutPort_create(), RTC_inPort_create()].
*/
RTC_DataPortBase* Port_createPort(CORBA_RTC_RTObject rtobj, const char *port_name, const char *type_name, DataPortType port_type)
{

  /* create RepositoryID and get TypeCode */
  char repoid[MAX_STRBUF];
  memset(repoid, 0, MAX_STRBUF);
  Port_createRepositryID(type_name, repoid);
  CORBA_TypeCode typecode = Port_getTypeCode(repoid);
  if (typecode == NULL) {
    fprintf(stderr, "Data Type Error. [%s] is not matched.\n",type_name);
    return NULL;
  }

  /* get DataTypeName separated ModuleName */
  int size = strlen(type_name)+1;  
  char typename[size];
  Port_splitDataTypeName(type_name, typename, typecode);

  /* create PortService and PortProfile */
  CORBA_RTC_PortService ps_obj;
  ps_obj = Port_create_PortService(rtobj, port_name, typename, port_type);

  /* Create Port's parameter to RTC_DataPort struct */
  RTC_DataPortBase* dataport;
  if (port_type == INPORT_TYPE) {
    dataport = (RTC_InPort *)RtORB_calloc(1, sizeof(RTC_InPort)
                                           , "Create RTC_InPort");
  } else if (port_type == OUTPORT_TYPE) {
    dataport = (RTC_OutPort *)RtORB_calloc(1, sizeof(RTC_OutPort)
                                            , "Create RTC_OutPort");
  } else {
    fprintf(stderr
         , " [ERROR] Can't create DataPortBase by unknown 'DataPortType'.\n");
    return  NULL;
  }
  if (Port_create_DataPortBase(dataport, port_type, typecode, ps_obj) <0) {
    /* Release heap memory */
    Port_deletePort();
    return NULL;
  }

  return dataport;
}


/* =========================== [ Delete ] ================================== */
void Port_deletePort()
{
  return;
}


/* ========================== [ Sequence ] ================================= */

/*
 Called from [RTC_OutPort_setSeqLength()].
*/
int Port_setSequenceLength(RTC_OutPort *out_port, CORBA_unsigned_long length, void* val, const char* val_name)
{
  int index = -1;

  CORBA_TypeCode tc, tc_member,tc_base;
  tc = out_port->m_typecode;
  tc_member = tc_base = NULL;

  /* get Index of [member_type] from [member_name] and error check */
  if (tc->kind == tk_alias) {
    /* ([IDL] typedef sequence<DataType> TypeName; ==> kind:tk_alias) */
    index = 0;  /* Because first member_type must be 'tk_sequence'. */
  } else if (tc->member_name == NULL) {
    fprintf(stderr, " [ERROR] Can't alloc Seq_data. No 'member_name'.\n");
    return -1;
  } else {
    tc = Port_getIndexOfTypeCode(tc, &index, val_name);
    if ( (index < 0) || (!tc) ) {
      fprintf(stderr, " [ERROR] Can't allocate Sequence data. [%s] is not exist.\n", val_name);
      return -1;
    }
  }
  
  /* Set TypeCode of member */
  tc_member = tc->member_type[index]; 

  /* Skip 'tk_alias' member of Complex DataType (ref: <RtORB> SKIP_ALIAS(tc) macro) */
  while (tc_member->kind == tk_alias)  tc_member = tc_member->member_type[0];

  /* get TypeCode and error check*/
  if (tc_member->kind != tk_sequence) { // ref: <RtORB>[typecode.h]
    fprintf(stderr, 
         " [ERROR] Can't allocate Sequence data. [%s] is not Sequence type.\n", val_name);
    return -1;

  } else {
    /* get TypeCode of Sequence_Data_type */
    if (tc_member->member_count != 1) {
       fprintf(stderr, " [ERROR] Can't allocate Sequence data in [%s].\n", val_name);
       return -1;
    }

    /* get TypeCode of Contents_Data_type */
    tc_base = tc_member->member_type[0]; 

    /* Allocate memory of Sequence data */
    CORBA_SequenceBase *sb = (CORBA_SequenceBase*)val;
    if (sb->_buffer) {
      RtORB__free(sb->_buffer, "Port_setSequenceLength()");
      sb->_buffer = NULL;
    }
    if (length > 0) {
      sb->_buffer = RtORB_alloc_by_typecode(tc_base, length, "Allocate Sequence Data.");
      if (sb->_buffer == NULL) {
        fprintf(stderr, " [ERROR] Can't allocate Sequence data in [%s].\n", val_name);
        return -1;
      }
    }
    sb->_length = length;
    if (sb->_maximum < length) sb->_maximum = length;
    sb->_release = 0; 
  }

  return 1;
}


/*
 Called from [RTC_OutPort_getSeqLength(), RTC_InPort_getSeqLength()].
*/
uint32_t Port_getSequenceLength(RTC_DataPortBase *port, void* val, const char* val_name)
{

  uint32_t length = 0;
  int index = -1;
  CORBA_TypeCode tc = port->m_typecode;
  CORBA_TypeCode tc_member;

  /* get Index of [member_type] from [member_name] and error check */
  if (tc->kind == tk_alias) {
    /* ([IDL] typedef sequence<DataType> TypeName; ==> kind:tk_alias) */
    index = 0;  /* Because first member_type must be 'tk_sequence'. */
  } else if (tc->member_name == NULL) {
    fprintf(stderr, " [ERROR] Can't get Sequence length. No 'member_name'.\n");
    return -1;
  } else {
    tc = Port_getIndexOfTypeCode(tc, &index, val_name);
    if (index < 0) {
      fprintf(stderr, " [ERROR] Can't get Sequence length. Not exist.\n");
      return -1;
    }
  }

  /* Set TypeCode of member */
  tc_member = tc->member_type[index]; 

  /* Skip 'tk_alias' member of Complex DataType (ref: <RtORB> SKIP_ALIAS(tc) macro) */
  while (tc_member->kind == tk_alias)  tc_member = tc_member->member_type[0];

  /* get Sequence_Length and Error check*/
  if (tc_member->kind != tk_sequence) { // ref: <RtORB>[typecode.h]
    fprintf(stderr, " [ERROR] Can't get Sequence length. Not Sequence type.\n");
  } else if (tc_member->member_count != 1) {
    fprintf(stderr, " [ERROR] Can't get Sequence length. member_count is not matched.\n");
  } else {
    /* get Sequence_Length */
    CORBA_SequenceBase *sb = (CORBA_SequenceBase*)val;
    if ( sb->_length > 0 )  length = sb->_length;
  }

  return length;
}


/* ====================== [ Marsha/Unmarshal ] ============================= */

/*
 Called from [RTC_OutPort_write()].
*/
int Port_Marshal_by_TypeCode(OpenRTM_CdrData *cdr_data,  RTC_OutPort *out_port)
{

  char *cdr_buf = NULL;
  int32_t data_size = 0;
  int pos = 0;  /* address of octet_data */

  /* Allocate memory for Buffer by MaxSize */
  cdr_buf = (char *)RtORB_alloc( MAX_MARSHALBUF, "Port_Marshal_by_TypeCode");
  if(!cdr_buf){ 
    fprintf(stderr, "[ERROR] <OutPort_write> Can't allocate memory for Buffer.\n");
    return -1;
  }
  memset(cdr_buf, 0, MAX_MARSHALBUF);

  /* Marshal to Buffer, and calculate DataSize */
  data_size = marshal_by_typecode((octet*)cdr_buf, out_port->m_value, out_port->m_typecode, &pos);

  /* Allocate memory for CDR_Stream data */
  cdr_data->_buffer = OpenRTM_CdrData_allocbuf(data_size);
  if (!cdr_data->_buffer) {
    fprintf(stderr, " [ERROR] <OutPort_write> Can't allocate memory for CdrData.\n");
    RtORB_free(cdr_buf, "Port_Marshal_by_TypeCode (Fail to alloc)");
    cdr_buf = NULL;
    return -1;
  }

  /* Copy buffer to CDR_Stream data */
  memcpy(cdr_data->_buffer, cdr_buf, data_size);
  cdr_data->_length = cdr_data->_maximum = data_size;
  cdr_data->_release = 0;

  /* Free buffer */
  RtORB_free(cdr_buf, "Port_Marshal_by_TypeCode");
  cdr_buf = NULL;

  return 1;
}


/*
 Called from [RTC_InPort_read()].
*/
void Port_UnMarshal_by_TypeCode(OpenRTM_CdrData *cdr_data,  RTC_InPort *in_port)
{

  int pos = 0;  /* address of octet_data */

  /** UnMarshal [CDR_Stream] data to [DataType] data **/
  demarshal_by_typecode((void**)in_port->m_value, in_port->m_typecode, cdr_data->_buffer, &pos, 1); 

  return;
}


/* =========================== [ Tools ] =================================== */

/*
  Called from [impl_RTC_RTObject_get_ports()]
*/
RTC_PortServiceList *
Port_getPortServiceList(RTC_PortAdmin *admin)
{
  RTC_PortServiceList* retval;

  if( admin == NULL ){
    retval = RTC_PortServiceList__alloc();
  }else{
    if( admin == NULL && admin->m_portRefs == NULL){
      retval = RTC_PortServiceList__alloc();
    }else{
      retval = RTC_PortServiceList__alloc();
      retval->_maximum = admin->m_portRefs->_maximum;
      retval->_length = admin->m_portRefs->_length;
      retval->_release = admin->m_portRefs->_release;
      retval->_buffer = malloc(sizeof(RTC_PortService) * admin->m_portRefs->_length);
      int i;
      for(i=0; i< retval->_length; i++)
      {
         retval->_buffer[i] = CORBA_Object_dup(admin->m_portRefs->_buffer[i]);
      }
    }
  }

  return retval;
}


/*
  Called from [impl_RTC_RTObject_get_component_profile()] 
*/
void
Port_getPortProfileList(RTC_PortAdmin *admin, RTC_PortProfileList *ppl)
{
  int i;

  if(admin == NULL || admin->m_portRefs == NULL){
    ppl->_maximum = ppl->_length = 0;
    ppl->_buffer  = NULL;
    ppl->_release = 0;
  }else{
    ppl->_length  = admin->m_portRefs->_length;
    ppl->_maximum = admin->m_portRefs->_maximum;
    ppl->_buffer  = RTC_PortProfileList_allocbuf(ppl->_length);
    for(i = 0; i< ppl->_length ; i++){
      Port_getPortProf((RTC_PortService)admin->m_portRefs->_buffer[i], &ppl->_buffer[i]); 
    }
  }

  return;
}


/*
 Called from [Port_getPortProfileList(), impl_RTC_PortService_get_port_profile()].
*/
void Port_getPortProf(CORBA_RTC_PortService obj, RTC_PortProfile *prof)
{
  /* <PortProfile> (name/interfaces/port_ref/connector_profiles/owner/properties) */

  impl_POA_RTC_PortService *servant = (impl_POA_RTC_PortService*)obj->servant;

  if(servant->m_portProfile == NULL){
    prof->name = NULL;
    prof->interfaces._length = 0;
    prof->owner = CORBA_OBJECT_NIL;
    prof->connector_profiles._length = 0;
    prof->properties._length = 0;
  }else{
    prof->name = strdup(servant->m_portProfile->name); 
    prof->interfaces._length = servant->m_portProfile->interfaces._length; 
    prof->port_ref = CORBA_Object_dup(servant->m_portProfile->port_ref); 
    prof->owner = CORBA_Object_dup(servant->m_portProfile->owner); 
    /* connector_profiles */
    Port_dupConnProfList(&prof->connector_profiles, servant->m_portProfile->connector_profiles);
    /* properties */
    NVUtil_dupNVList(&prof->properties, servant->m_portProfile->properties);
  }

  return;
}


/*
 Called from [impl_RTC_PortService_get_connector_profiles(), Port_getPortProf()].
*/
void Port_dupConnProfList(RTC_ConnectorProfileList* dest, RTC_ConnectorProfileList src)
{
  int i;
  
  if(src._length < 1){
    dest->_length = dest->_maximum = 0;
    dest->_release = 0;
    dest->_buffer = NULL;
  } else {
    dest->_length = src._length;
    dest->_maximum = src._maximum;
    dest->_release = src._release; 
    dest->_buffer = RTC_ConnectorProfileList_allocbuf(dest->_length);
    /* Duplicate ConnectorProfile */
    for(i = 0; i < dest->_length; i++){
      Port_dupConnProf(&dest->_buffer[i], src._buffer[i]);
    }
  }

  return;
}


/*
 Called from [impl_RTC_PortService_get_connector_profile(), Port_dupConnProfList()].
*/
void Port_dupConnProf(RTC_ConnectorProfile* dest, RTC_ConnectorProfile src)
{
  int i;

  dest->name = strdup(src.name);
  dest->connector_id = strdup(src.connector_id);
  /* ports (PortServiceList) */
  dest->ports._length = src.ports._length;
  dest->ports._maximum = src.ports._maximum;
  dest->ports._release = src.ports._release;
  dest->ports._buffer = RTC_PortServiceList_allocbuf(dest->ports._length);
  for(i = 0; i < dest->ports._length; i++){
    dest->ports._buffer[i] = CORBA_Object_dup(src.ports._buffer[i]); 
  }
  /* properties (NVList) */
  NVUtil_dupNVList(&dest->properties, src.properties);

  return;
}

/*****************************************************************************/
/********************* [ static functions ] **********************************/
/*****************************************************************************/

/* =========================== [ Create ] ================================== */

/*
 Called from [Port_createPort()].
*/
/*!
 * \brief Portで扱うデータのデータ型名称から、[RepositryID]を生成する。
 * \param type_name 生成するPortで扱うデータのデータ型名称(モジュール名_変数名の必要あり。例として、[RTC_TimedLong]など)
 * \param repoid 内部生成された[RepositryID]
 * \return void
 */
static void Port_createRepositryID(const char* type_name, char* repoid)
{
  /* [type_name]: "ModuleName"_"DataTypeName" (ex: RTC_TimedLong) */
  /* [RepositryID]: IDL:"ModuleName"/"DataTypeName":1.0 */

  int size = strlen(type_name) + 1;  
  char buf[size];
  char *module, *datatype;
  string_sequence *names;

  /* Split type_name by token "_" */
  names = split_string((char*)type_name, '_', 0); 

  if ((names != NULL) && (names->length == 2)) {
    module = strdup(names->buffer[0]);
    datatype = strdup(names->buffer[1]);
  } else {
    module = datatype = NULL;
  }

  /* free */
  free_string_sequence(names);

  /* make RepositryID */
  sprintf(repoid, "IDL:%s/%s:1.0",module, datatype); 

  return;
}


/*
 Called from [Port_createPort()].
*/
/*!
 * \brief 引数[repoid]に対応した、[TypeCode]をTypeCode一覧から取得し、そのポインタを返す。
 * \param repoid 生成済みの[RepositryID]
 * \return 該当するTypeCodeデータ、見つからなければNULL
 */
static CORBA_TypeCode Port_getTypeCode(char* repoid)
{
  /* [refer to] <RtORB> [corba-typecode.c] CORBA_TypeCode_get_by_repoid() */

  int i,len;
  len = sizeof(TypeCodeTbl)/sizeof(TypeCodeTbl[0]);

  for (i=0; i<len; i++) {
    if (!TypeCodeTbl[i]) { continue; }
    if (strcmp(TypeCodeTbl[i]->repository_id, repoid) == 0) {
      return TypeCodeTbl[i];  // Matched
    }
  }
  return NULL;  //Unmatched

  //TODO: TypeCodeテーブルの事前作成と、その取得方法などは別途検討

}


/*
 Called from [Port_createPort()].
*/
/*!
 * \brief 引数[src]のデータ型名(モジュール名など含む階層を"_"で付与した状態)から、"_"をデリミタとして分割し、最後のデータ型名を取得する。
 *
 *        ここで、指定しているデータ型名は、ユーザが記述するのだが、IDLにデータ型を記述する際に、OpenRTMデフォルトのデータ型以外にユーザが定義したものの使用もありえるため、IDL内のModule名が異なるが型名が同一の場合などに対応し、絶対PATHの形式で「モジュール名_データ型名」で指定されることを前提としている。
 * \param src split処理前のデータ型名("_"付与状態)
 * \param dest split済みのデータ型名
 * \param tc 取得済みのデータ型に応じたTypeCode
 * \return void
 */
static void Port_splitDataTypeName(const char *src, char* dest, CORBA_TypeCode tc)
{
  CORBA_Identifier identifier = tc->identifier;

  if (!strcmp(identifier,src)) {  /* If no "Module_" name */
    dest = (char*)src;
  } else {
    /* Split src by token "_" */
    string_sequence *names = split_string((char*)src, '_', 0); 
    if ((names != NULL) && (names->length == 2)) {
      strcpy(dest, names->buffer[1]);
    } else {
      dest = NULL;  /* ERROR */
      fprintf(stderr, " [ERROR] Can't split DataType Name.\n");
    }
    free_string_sequence(names);
  }

  return ;
}


/*
 Called from [Port_createPort()].
*/
/*!
 * \brief 引数のPort情報を元に、[PortService]オブジェクトと[PortProfile]を生成する。内部で、[RTC_PortAdmin]型データのセットと、[PortProfile]型データをセットする。
 * \param rtobj DataPortを保持する親のRTC_RTObjectオブジェクト
 * \param port_name 生成するPortの名前
 * \param type_name 生成するPortで扱うデータ型名称("モジュール名_"が除かれた文字列)
 * \param port_type 生成するPortの種別(INPORT_TYPE/OUTPORT_TYPE)
 * \return 生成されたRTC_PortServiceオブジェクトリファレンス
 */
static CORBA_RTC_PortService Port_create_PortService(CORBA_RTC_RTObject rtobj, 
                                 const char *port_name, 
                                 char *type_name,
                                 DataPortType port_type)
{

  /* PortService */
  CORBA_RTC_PortService port_service;

  /* create PortService and set to PortAdmin */
  port_service = Port_set_PortService(rtobj);

  /* set PortProfile in PortService */
  Port_set_PortProfile(port_service, port_name, rtobj, type_name, port_type);

  return port_service;
}


/*
 Called from [Port_create_PortService()].
*/
/*!
 * \brief RTC_PortServiceオブジェクトを生成する。
 *
 *       親のRTC_RTObjectオブジェクトがもつ[RTC_PortAdmin]型データ[m_portAdmin]の要素[m_portRefs]に、今回生成したRTC_PortServiceオブジェクトをセットする。この時[m_portRefs]が既に存在しなければ、新規生成、存在すれば、List形式に追加する。（１つのRTC_RTObjectオブジェクトが複数のDataPortを持つことを考慮）
 * \param obj DataPortを保持する親のRTC_RTObjectオブジェクト
 * \return 生成されたRTC_PortServiceオブジェクトリファレンス
 */
static CORBA_RTC_PortService Port_set_PortService(CORBA_RTC_RTObject obj)
{
  CORBA_RTC_PortService port_service;
  CORBA_Environment ev;
  int i;
  int length = 0;
  impl_POA_RTC_RTObject *implobj = (impl_POA_RTC_RTObject *)obj->servant;

  /* Action like [addPort()] */
  if (implobj->m_portAdmin == NULL) 
  {
    implobj->m_portAdmin = Port_newPortAdmin();
    implobj->m_portAdmin->m_portRefs = RTC_PortServiceList__alloc();
    implobj->m_portAdmin->m_portRefs->_length = 1;
    implobj->m_portAdmin->m_portRefs->_maximum = 1;
    implobj->m_portAdmin->m_portRefs->_release = 0;
    implobj->m_portAdmin->m_portRefs->_buffer = RTC_PortServiceList_allocbuf(1); 
    fprintf(stderr, "Create new PortAdmin.\n");
  } else {
    length = implobj->m_portAdmin->m_portRefs->_length;
    implobj->m_portAdmin->m_portRefs->_length = length + 1;
    implobj->m_portAdmin->m_portRefs->_maximum = length + 1;
    /* data copy to buffer */
    RTC_PortService* dummy_buf;
    dummy_buf = RTC_PortServiceList_allocbuf(length);
    for(i = 0; i < length; i++)
    {
       memcpy( &dummy_buf[i], &implobj->m_portAdmin->m_portRefs->_buffer[i]
                            , sizeof(RTC_PortService));
    }
    /* free + Realloc */
    RtORB_free(implobj->m_portAdmin->m_portRefs->_buffer, "Free PortService_buffer.");
    implobj->m_portAdmin->m_portRefs->_buffer = NULL;
    implobj->m_portAdmin->m_portRefs->_buffer = RTC_PortServiceList_allocbuf(length+1); 
    /* data set */
    for(i = 0; i < length; i++)
    {
       memcpy( &implobj->m_portAdmin->m_portRefs->_buffer[i], &dummy_buf[i]
                            , sizeof(RTC_PortService));
    }
    /* free buffer */
    RtORB_free(dummy_buf, "Free PortService dummy_buffer.");
    dummy_buf = NULL;
  }

  /* create new PortService */
  port_service = impl_RTC_PortService__create(implobj->poa, &ev);
  implobj->m_portAdmin->m_portRefs->_buffer[length] = port_service;

  return port_service;
}


/*
 Called from [Port_set_PortService()].
*/
/*!
 * \brief RTC_PortAdmin型データ用のメモリをcallocにて確保し、[res]にセットし、返り値として返す。
 * \return RTC_PortAdmin型データのポインタ
 */
static RTC_PortAdmin *Port_newPortAdmin()
{
  RTC_PortAdmin *res;
  res = (RTC_PortAdmin *)calloc(1, sizeof(RTC_PortAdmin));

  return res;
}


/*
 Called from [Port_create_PortService()].
*/
/*!
 * \brief PortProfileを生成する。
 *
 *       生成されたRTC_PortServiceオブジェクトがもつ[RTC_PortProfile]型データ[m_portProfile]を生成し、引数の各パラメータをセットする。この時、[connector_profiles]のmaximumは"1"固定(1対1通信対応のみ)で、[properties]部は、各種固定のプロパティ情報をセットする。
 *
 * \param portobj 生成されたRTC_PortServiceオブジェクト
 * \param port_name 生成するPortの名前
 * \param rtobj DataPortを保持する親のRTC_RTObjectオブジェクト
 * \param data_type_name 生成するPortで扱うデータ型名称("モジュール名_"が除かれた文字列)
 * \param port_type 生成するPortの種別(INPORT_TYPE/OUTPORT_TYPE)
 * \return void
 */
static void Port_set_PortProfile(CORBA_RTC_PortService portobj, const char *port_name, CORBA_RTC_RTObject rtobj, char *data_type_name, DataPortType port_type)
{

  impl_POA_RTC_PortService *implobj = (impl_POA_RTC_PortService *)portobj->servant;

  implobj->m_portProfile = RTC_PortProfile__alloc();
  implobj->m_portProfile->name = (char*)port_name;
  implobj->m_portProfile->port_ref = portobj; /* ObjRef of CORBA_RTC_PortService */ 
  implobj->m_portProfile->owner = rtobj; /* owner is CORBA_RTC_RTObject */

  /* interfaces */
  implobj->m_portProfile->interfaces._length = 0;
  implobj->m_portProfile->interfaces._maximum = 0;
  implobj->m_portProfile->interfaces._release = 0;

  /* connector_profiles (ConnectorProfile_List => Size is fixed as '1' in OpenRTM-aist-C) */
  implobj->m_portProfile->connector_profiles._length = 0;  
  implobj->m_portProfile->connector_profiles._maximum = 1; 
  implobj->m_portProfile->connector_profiles._release = 0;

  /* properties (set Default values) */
  implobj->m_portProfile->properties._length = 5;
  implobj->m_portProfile->properties._maximum = 5;
  implobj->m_portProfile->properties._release = 0;
  implobj->m_portProfile->properties._buffer = RTC_NVList_allocbuf(5); 
  NVUtil_setNV(&implobj->m_portProfile->properties._buffer[0]
                 , "dataport.data_type", data_type_name); 
  NVUtil_setNV(&implobj->m_portProfile->properties._buffer[1]
                 , "dataport.dataflow_type", "push");
  NVUtil_setNV(&implobj->m_portProfile->properties._buffer[2]
                 , "dataport.subscription_type", "flush");
  NVUtil_setNV(&implobj->m_portProfile->properties._buffer[3]
                 , "dataport.interface_type", "corba_cdr");
  if (port_type == INPORT_TYPE) 
  {
    NVUtil_setNV(&implobj->m_portProfile->properties._buffer[4]
                   , "port.port_type", "DataInPort");
  } else {
    NVUtil_setNV(&implobj->m_portProfile->properties._buffer[4]
                   , "port.port_type", "DataOutPort");
  }

  /* m_name */
  implobj->m_name = (char*)port_name;

  return;
}


/*
 Called from [Port_createPort()].
*/
/*!
 * \brief 引数の情報を元に、[RTC_DataPortBase]型データを生成する。要素の[m_value]には、関連するデータの型に応じたTypeCodeにより、メモリ確保を行う。成功すれば[1]、失敗すれば[-1]を返す。
 * \param port 生成する[RTC_DataPortBase]型データ
 * \param port_type 生成するPortの種別(INPORT_TYPE/OUTPORT_TYPE)
 * \param tc Portに関連するデータの型に応じたTypeCodeデータ
 * \param psobj 生成されたRTC_PortServiceオブジェクトリファレンス
 * \return 成功:[1],失敗:[-1]
 */
static int Port_create_DataPortBase(RTC_DataPortBase *port, DataPortType port_type,  CORBA_TypeCode tc, CORBA_RTC_PortService psobj)
{

  /* Set default value to DataPortBase struct */ 
  port->m_portType = port_type;  
  port->m_typecode = tc; 
  port->m_objref = psobj;
  port->m_value = Port_alloc_by_TypeCode(port->m_typecode); 
  if (!(port->m_value)) return  -1;

  /* set [impl_POA_RTC_PortService::m_portBase] */
  impl_POA_RTC_PortService *ps_servant;
  ps_servant = (impl_POA_RTC_PortService*)psobj->servant;
  ps_servant->m_portBase = port;  

  return 1;
}


/*
 Called from [Port_create_DataPortBase()].
*/
/*!
 * \brief 引数のTypeCodeデータ[tc]に対応したメモリ領域を確保し、そのポインタを返す、
 * \param tc メモリ確保対象のTypeCodeデータ
 * \return メモリ確保された領域のポインタ
 */
static void *Port_alloc_by_TypeCode(CORBA_TypeCode tc)
{

  void *retval; /* address of allocated memory */
  retval = RtORB_typecode_alloc(tc);  // => calloc() [init to '0']

  return retval;  /* OK: pointer / ERROR: 'NULL' */
}


/* =========================== [ Delete ] ================================== */

/*
 Called from [Port_createPort()].  (Uncalled)
*/
/*!
 * \brief (T.B.D)
 * \param rtobj (T.B.D)
 * \return void
 */
static void Port_delete_PortService(CORBA_RTC_RTObject rtobj)
{
  impl_POA_RTC_RTObject* impl_rtobj;
  impl_POA_RTC_PortService* impl_portservice;
  impl_POA_OpenRTM_InPortCdr *impl_inportcdr;
  CORBA_RTC_PortService port_service;
  CORBA_OpenRTM_InPortCdr inport_cdr;
  RTC_PortProfile *portprof;
  CORBA_Environment ev;
  memset (&ev, 0, sizeof (CORBA_Environment)); 

  impl_rtobj = (impl_POA_RTC_RTObject *)rtobj->servant;
  port_service = impl_rtobj->m_portAdmin->m_portRefs->_buffer[0];
  impl_portservice = (impl_POA_RTC_PortService *)port_service->servant;
  portprof = (RTC_PortProfile*)impl_portservice->m_portProfile;

  /* free [m_PortProfile] */
  if (!portprof->properties._buffer) {
    RtORB_free(portprof->properties._buffer
               ,"[Port_delete_PortService] free(properties._buffer)");
    portprof->properties._buffer = NULL;
  }

  if (!portprof->connector_profiles._buffer) {
    RtORB_free(portprof->connector_profiles._buffer
               ,"[Port_delete_PortService] free(connector_profiles._buffer)");
    portprof->connector_profiles._buffer = NULL;
  }

  if (!portprof) {
    RtORB_free(portprof, "[Port_delete_PortService] free(PortProfile)");
    portprof = NULL;
  }

  /* free [PortService] */
  impl_RTC_PortService__destroy(impl_portservice, &ev);
  impl_rtobj->m_portAdmin = NULL;

  return;
}


/*
 Called from [Port_createPort()].  (Uncalled)
*/
/*!
 * \brief (T.B.D)
 * \param port (T.B.D)
 * \return void
 */
static void Port_delete_DataPortBase(RTC_DataPortBase *port)
{

  /* free [port->m_value] */
  Port_free_by_TypeCode(port->m_typecode, port->m_value); 

  /* free [port] */
  if (!port) {
    RtORB_free(port, "[PortBase_delete_DataPortBase] free()");
    port = NULL;
  }
}


/*!
 * \brief (T.B.D)
 * \param tc (T.B.D)
 * \param val (T.B.D)
 * \return void
 */
static void Port_free_by_TypeCode(CORBA_TypeCode tc, void *val)
{

  RtORB_free_by_typecode(tc, val, 1, 0);  

  return; 
}


/* ========================== [ Sequence ] ================================= */

/*
 Called from [Port_setSequenceLength(), Port_getSequenceLength()].
*/
/*!
 * \brief 深い階層も想定の複合型のデータ型の中から、引数の[value_name]で指定した、可変長サイズ指定対象の変数名に該当する、要素の部分を見つけだし、その[TypeCode]と[index]を取得する。
 *
 *        (1)引数[value_name]に対し、split_string()で区切り文字"."により分割する。 <BR>
 *        (2)分割の数の分だけforループで、複合型のデータ構造の階層の中までを対象とし、順次、そのデータ構造内の要素から、名前が一致する部分を検索し、一致した時には、引数[tc]をその要素のTypeCodeに上書きしていく。<BR>
 *           最下層まで到達し、その中の要素と一致した時に、その要素のindexを引数の[idx]にセットする。
 *        (3)可変長サイズ指定対象の変数名に該当する、[TypeCode]を返す。
 * \param tc Portに関連したデータの型に応じたTypeCode
 * \param idx 複合型のデータ構造内で何番目の要素かを表すindex。(主に、構造体などのデータの場合の要素の順番。)
 * \param value_name 可変長(sequence型)で定義された変数の名前("data" or "parent.child.data")
 * \return 検索語の該当する要素の一つ上位に当たるTypeCode、見つからなければ[NULL]
 */
static CORBA_TypeCode Port_getIndexOfTypeCode(CORBA_TypeCode tc, int* idx, const char* value_name)
{

  int size = strlen(value_name)+1;  
  int flag, i, j;
  string_sequence *names;

  *idx = -1;  /* init */

  /* Split value_name by token "." */
  names = split_string((char*)value_name, '.', 0); /* ex) name: "data" or "parent.child.data" */

  for (j=0; j < names->length ; j++) {  /* 1st for */
    flag = 0; /* init */
    /* get Index of [member_type] from [member_name] */  
    for (i=0; i < tc->member_count; i++) {  /* 2nd for */ 
      /* tk_alias,tk_sequence ==>  'typecode->member_count=1' */
      if( (tc->member_name != NULL) && (strcmp(names->buffer[j], tc->member_name[i]) == 0)) {
        if (j == (names->length - 1)) {
          *idx = i;  /* Find [index] ==>  Finish search */
        } else {
          tc = tc->member_type[i];  /* go Child data */
          while ((tc->kind == tk_sequence) || (tc->kind == tk_alias)) {
            tc = tc->member_type[0]; /* Skip ('tk_sequence' and 'tk_alias' has no member.) */
          }
        }
        flag = 1;  /* name matched */
        break; /* break out 2nd 'for' */
      }
    } /* 2nd for */
    if (flag == 0) {
      fprintf(stderr, " [ERROR] Can't allocate Sequence data. 'ValueName' is invalid.\n");
      tc = NULL;
      break;
    }
  } /* 1st for */

  /* free */
  free_string_sequence(names);

  return tc;
}

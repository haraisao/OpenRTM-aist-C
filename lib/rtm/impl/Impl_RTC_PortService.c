/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_PortService.c
 * \brief <RTC::PortServiceインタフェース> 主に、Portに関する主要関数(接続/切断/Profileの取得)の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : PortService                          ***/
/***        Inheritance : SDOPackage::SDOService  [Empty]    ***/
/***************************************************************/

CORBA_RTC_PortService 
impl_RTC_PortService__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_PortService retval;
  impl_POA_RTC_PortService *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_PortService *)RtORB_calloc(1, sizeof(impl_POA_RTC_PortService)," create...");
  newservant->servant.vepv = &impl_RTC_PortService_vepv;
  newservant->poa = poa;
  POA_RTC_PortService__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */

  newservant->m_name = NULL;
  newservant->m_portProfile = NULL;
  newservant->m_InPortCdr = CORBA_OBJECT_NIL;
  newservant->m_portBase = NULL;

   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTC_PortService__destroy(impl_POA_RTC_PortService *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_PortService__fini((PortableServer_Servant)servant, ev);
#if 0 /* メモリ2重解放回避のため (POA_OpenRTM_InPortCdr__fini()関数ないでもfreeしているため) */
    RtORB_free (servant, "servant");
# endif
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_PortService__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_PortService *newservant;

  newservant = (impl_POA_RTC_PortService *)RtORB_calloc(1, sizeof(impl_POA_RTC_PortService), "  create_servant");
  newservant->servant.vepv = &impl_RTC_PortService_vepv;
  newservant->poa = poa;
  POA_RTC_PortService__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief 自PortServiceが保持している、Port情報である、RTC_PortProfile型データを返す。 
 * \return RTC_PortProfile型データ
 */
RTC_PortProfile*
impl_RTC_PortService_get_port_profile(
  impl_POA_RTC_PortService *servant,
  CORBA_Environment *ev)
{
  RTC_PortProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  CORBA_RTC_PortService objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 
  retval = RTC_PortProfile__alloc();  /* Client needs to free this memory. */
  Port_getPortProf(objref, retval);

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 自PortServiceが保持している、接続情報である、RTC_ConnectorProfileListデータを返す。 
 *
 *        1対1の通信のみ対応のため、一つのPortServiceが持つConnectorProfileは、実際には「一つ」である。
 * \return RTC_ConnectorProfileListデータ (実際に中身は1つ)
 */
RTC_ConnectorProfileList*
impl_RTC_PortService_get_connector_profiles(
  impl_POA_RTC_PortService *servant,
  CORBA_Environment *ev)
{
  RTC_ConnectorProfileList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  /* <ConnectorProfile> (name/connector_id/ports/properties) */
  retval = RTC_ConnectorProfileList__alloc();  /* Client needs to free this memory. */
  Port_dupConnProfList(retval, servant->m_portProfile->connector_profiles);

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 自PortServiceが保持している、接続情報の[ConnectorProfile]で引数の[connector_id]にマッチしたものを返す。 
 * \param connector_id 取得するConnectorProfileの[connector_id]
 * \return RTC_ConnectorProfileデータ
 */
RTC_ConnectorProfile*
impl_RTC_PortService_get_connector_profile(
  impl_POA_RTC_PortService *servant,
  const CORBA_char * connector_id,
  CORBA_Environment *ev)
{
  RTC_ConnectorProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = NULL;
  int i;
  int index = -1;
  
  /* Search ConnectorProfile by ID. */ 
  for(i = 0; i < servant->m_portProfile->connector_profiles._length; i++){
    if(strcmp(servant->m_portProfile->connector_profiles._buffer[i].connector_id, connector_id) == 0) {
      index = i;
      break;
    }
  }

  /* Allocate */
  retval = RTC_ConnectorProfile__alloc();   /* Client needs to free this memory. */

  /* Set ConnectorProfile */
  if (index < 0) {
    /* Not found. ==> Create empty Profile. */  
    retval->name = NULL;
    retval->connector_id = NULL;
    retval->ports._length = 0;
    retval->properties._length = 0;
  } else {
    /* duplicate */
    Port_dupConnProf(retval, servant->m_portProfile->connector_profiles._buffer[index]);
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief OutPortとInPortを接続の際に、いずれかのPort側の当関数がcallされ、引数の[connector_profile]に従い、各種接続手続きを行う。
 *
 *        (1) 引数の[connector_profile]内の[connector_id]が空の場合、UUIDでIDを生成(RtORBの[new_ObjectID()]によりIDを生成)する。もし空でない場合、既に接続が存在するので、リターンコードに[PRECONDITION_NOT_MET]をセットする。<BR>
 *        (2) [notify_connect()]をcallし、接続メイン処理を行う。<BR>
 *        (3) 接続に失敗した場合、[RTC_PortService_disconnect()]をcallし、切断処理を行う。<BR>
 *        (4) 返り値として、リターンコードを返す。
 * \param connector_profile Port間接続の情報用データ(ConnectorProfile)
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR]/既接続あり:[RTC_PRECONDITION_NOT_MET])
 */
RTC_ReturnCode_t
impl_RTC_PortService_connect(
  impl_POA_RTC_PortService *servant,
  RTC_ConnectorProfile* connector_profile,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
  retval = RTC_RTC_OK;

  /* If connector_id is empty, create new ID  */
  if (strcmp(connector_profile->connector_id, "") == 0){
    connector_profile->connector_id = new_ObjectID();  /* <RtORB>new_ObjectID() */
    fprintf(stderr,"[New connector_id] : %s\n",connector_profile->connector_id);

    /* Call <notify_connect()> of 1st PortService. */
    retval = RTC_PortService_notify_connect(connector_profile->ports._buffer[0], connector_profile, ev);

    if(retval != RTC_RTC_OK) {
      fprintf(stderr, " [ERROR] <%s> Connection failed.\n",connector_profile->name);
      RTC_PortService_disconnect(connector_profile->ports._buffer[0], connector_profile->connector_id, ev);
    }
  } else {
    fprintf(stderr, " [ERROR] Connection already exists. <ID = %s> \n",connector_profile->connector_id);
    retval = RTC_PRECONDITION_NOT_MET;
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 既に接続されたDataPortの切断の際に、いずれかのPort側の当関数がcallされ、切断処理を行う。
 *
 *        (1) 保持しているConectorProfileリストから、引数の[connector_id]と一致するConnectorProfileを探し出す。見つからない場合、リターンコードに[RTC_BAD_PARAMETER]をセットする。<BR>
 *        (2) [notify_disconnect()]をcallし、切断メイン処理を行う。<BR>
 *        (3) 返り値として、リターンコードを返す。
 * \param connector_id 切断対象の接続情報(ConnectorProfile)のID
 * \return RTC_ReturnCode_t型リターンコード。(切断成功:[RTC_RTC_OK]/切断失敗:[RTC_RTC_ERROR]/ConnectorProfileが見つからない:[RTC_BAD_PARAMETER])
 */
RTC_ReturnCode_t
impl_RTC_PortService_disconnect(
  impl_POA_RTC_PortService *servant,
  const CORBA_char * connector_id,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;
  int i;
  int index = -1;

#ifdef DEBUG
  fprintf(stderr,"[Disconnect] (connector_id : %s)\n",connector_id);
#endif

  /* Search ConnectorProfile by ID. */ 
  for(i = 0; i < servant->m_portProfile->connector_profiles._length; i++){
    if(strcmp(servant->m_portProfile->connector_profiles._buffer[i].connector_id, connector_id) == 0){
      index = i;
      break;
    }
  }

  if (index < 0) {
    fprintf(stderr, " [ERROR] Can't disoconnect. Invalid connector id: %s \n",connector_id);
    retval = RTC_BAD_PARAMETER;
  } else {
    /* Call <notify_disconnect()> of 1st PortService in ConnectorProfile which matched to connector_id. */
    retval = RTC_PortService_notify_disconnect(servant->m_portProfile->connector_profiles._buffer[index].ports._buffer[0], connector_id, ev);

    if(retval == RTC_RTC_ERROR){
      fprintf(stderr, " [ERROR] Failed to disconnect. (connector_id=%s) \n",connector_id);
    }
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 現在ある複数のDataPort間接続の切断を行う際に、当関数がcallされる。切断の数の分だけ、内部で[disconnect()]をcallしてメイン処理を行う。
 * \return RTC_ReturnCode_t型リターンコード。(切断成功:[RTC_RTC_OK]/切断失敗:[RTC_RTC_ERROR]/ConnectorProfileが見つからない:[RTC_BAD_PARAMETER])
 */
RTC_ReturnCode_t
impl_RTC_PortService_disconnect_all(
  impl_POA_RTC_PortService *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  int i;
  retval = RTC_RTC_OK;

#ifdef DEBUG
  fprintf(stderr,"[Disconnect_all] (counts = %d)\n",servant->m_portProfile->connector_profiles._length);
#endif

  /* Disconnect all connection */
  for(i = 0; i < servant->m_portProfile->connector_profiles._length; i++) {
    /* Call RTC_PortService_disconnect(CORBA_Object, connector_id, environment) */
    retval = RTC_PortService_disconnect(servant->m_portProfile->connector_profiles._buffer[i].ports._buffer[0], servant->m_portProfile->connector_profiles._buffer[i].connector_id, ev);
  }
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief [connect()]からcallされ、DataPort接続の詳細処理を行う。
 *
 * 1対1の通信のみ対応のため、[OutPort<-->InPort]の対の接続しか想定していないため、
 * 「ConnectorProfile」が持つPortServiceListの「ports」には、InPort/OutPortの
 * 「二つ」しか入っていない。
 *
 * 接続処理は、InPort側のObjectが持つ、「InPortCdr」オブジェクトのObjRefを、
 * OutPort側が知ることが、出来れば、メソッドの呼び出しが可能となるので、
 * 接続状態となる。そこで、手順の概要は以下となる。
 *
 * (1)InPort側では、[impl_OpenRTM_InPortCdr__create()]により、[InPortCdr]オブジェクトを生成し、その「InPortCdr」の「IOR」を作成し、ConnectorProfileの「properties」に[NVUtil_appendNVList()]でセットしておく。<BR>
 * (2)OutPort側にて、ConnectorProfileの「properties」にセットされた「IOR」を取得し、そこから、
 * 相手先の[InPortCdr]ObjRefを取得する。(データ送信処理時に、送信先の指定として、このObjRefを使用する) <BR>
 * (3)内部で変更を加えた[connector_profile]を自分の[m_portProfile->connector_profile]にコピーして保持する。
 *
 * なお、Port１つにつき、１つのConnectionしか許可しない仕様のため、[PortProfile]の[ConnectorProfileList]は、
 * Port_set_PortProfile()で、サイズが[ConnectorProfile]１つ分で既に固定確保されているので、当関数で確保は不要。
 * \param connector_profile Port間接続の情報用データ(ConnectorProfile)
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_BAD_PARAMETER]/既接続あり(1接続のみ許可):[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_PortService_notify_connect(
  impl_POA_RTC_PortService *servant,
  RTC_ConnectorProfile* connector_profile,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;
  int i,index;
  CORBA_RTC_PortService objref;  
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  if(servant->m_portProfile->connector_profiles._length){
    fprintf(stderr, " [ERROR] <%s> Connection already existed. (Because only One-on-One connection is enable.) \n",connector_profile->name);
    retval = RTC_RTC_ERROR;

  } else {
    /* [InPort action] Create my InPortCdr, ior(=>properties) */
    if(servant->m_portBase->m_portType == INPORT_TYPE) 
    {
      if(servant->m_InPortCdr) {
        RtORB_free(servant->m_InPortCdr,"Target InPortCdr"); 
        servant->m_InPortCdr = NULL; 
      }

      /* Create InPortCdr on InPort's PortService */
      servant->m_InPortCdr = impl_OpenRTM_InPortCdr__create(servant->poa, ev);

      /* set [impl_POA_OpenRTM_InPortCdr::m_inport] */
      impl_POA_OpenRTM_InPortCdr *inportcdr_servant;
      inportcdr_servant = (impl_POA_OpenRTM_InPortCdr*)servant->m_InPortCdr->servant;
      inportcdr_servant->m_inport = servant->m_portBase;

      /* Get [IOR] and set to [properties]. (Because Client needs [IOR] to connect to Server.) */
      NVUtil_appendNVList( &connector_profile->properties, 
                           "dataport.corba_cdr.inport_ior",
                           CORBA_ORB_object_to_string(The_ORB, servant->m_InPortCdr, ev) );
    }

    /* Search current PortService in ConnectorProfile's PortServiceList by ObjRef. */ 
    for(i = 0; i < connector_profile->ports._length; i++){
      if( CORBA_Object_is_equivalent(connector_profile->ports._buffer[i], objref, ev) ) {
        if(i < (connector_profile->ports._length - 1)){
          /* Call next PortService's notify_connect()  */
          retval = RTC_PortService_notify_connect(connector_profile->ports._buffer[i+1], connector_profile, ev);
        }
        break;
      }
      if (i == (connector_profile->ports._length - 1))  retval = RTC_BAD_PARAMETER;  /* Not found my ObjRef */
    }

    /* Connect action */
    if(retval == RTC_RTC_OK){

      /* [OutPort action] Connect action (Get [InPort's ObjectRef] from IOR) */
      if(servant->m_portBase->m_portType == OUTPORT_TYPE){
        for(i = 0; i < connector_profile->properties._length; i++){
          if(strcmp(connector_profile->properties._buffer[i].name,"dataport.corba_cdr.inport_ior") == 0){
            /* Convert IOR to ObjeRef, and set */
            servant->m_InPortCdr = CORBA_ORB_string_to_object(The_ORB, connector_profile->properties._buffer[i].value._val->val_str,ev);
          }
        }
      }

      /* Save current ConnectorProfile in [m_portProfile] (Only One-on-One port's connection) */
      servant->m_portProfile->connector_profiles._buffer = RTC_ConnectorProfileList_allocbuf(1);
      servant->m_portProfile->connector_profiles._length = 1;
      servant->m_portProfile->connector_profiles._buffer[0].name = strdup(connector_profile->name);
      servant->m_portProfile->connector_profiles._buffer[0].connector_id = strdup(connector_profile->connector_id);
      NVUtil_dupNVList(&servant->m_portProfile->connector_profiles._buffer[0].properties, connector_profile->properties);
      servant->m_portProfile->connector_profiles._buffer[0].ports._length = connector_profile->ports._length;
      servant->m_portProfile->connector_profiles._buffer[0].ports._maximum = connector_profile->ports._maximum;
      servant->m_portProfile->connector_profiles._buffer[0].ports._release = connector_profile->ports._release;
      servant->m_portProfile->connector_profiles._buffer[0].ports._buffer = RTC_PortServiceList_allocbuf(connector_profile->ports._length);
      for(i = 0; i < servant->m_portProfile->connector_profiles._buffer[0].ports._length; i++){
        servant->m_portProfile->connector_profiles._buffer[0].ports._buffer[i] = CORBA_Object_dup(connector_profile->ports._buffer[i]);
      }
    } /* end if (retval) */
  } /* end if (length) */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief [disconnect()]からcallされ、DataPort切断の詳細処理を行う。
 *
 * 1対1の通信のみ対応のため、[OutPort<-->InPort]の対の接続しか想定していないため、
 * 「ConnectorProfile」が持つPortServiceListの「ports」には、InPort/OutPortの
 * 「二つ」しか入っていない。
 *
 * 切断処理は、InPort側のObjectが持つ、「InPortCdr」オブジェクトのObjRefをdestroyし、かつ、
 * OutPort側が既セットされている、「InPortCdr」オブジェクトを削除すれば接続状態となる。
 * そこで、手順の概要は以下となる。
 *
 *        (1) 保持しているConectorProfileリストから、引数の[connector_id]と一致するConnectorProfileを探し出す。<BR>
 *        (2) 見つかったConnectorProfileの要素[ports]内に自PortServiceオブジェクトがあるか検索する。見つからない場合、リターンコードに[RTC_BAD_PARAMETER]をセットする。<BR>
 *        (3) 見つかった場合、InPort/OutPort側両方共に、connect()時にセットされた[InPortCdr]オブジェクトを削除する。<BR>
 *        (4) 内部保持している[connector_profile]を削除する。
 *
 * なお、Port１つにつき、１つのConnectionしか許可しない仕様のため、[PortProfile]の[ConnectorProfileList]は、
PortBase_set_PortProfile()で、サイズが[ConnectorProfile]１つ分で固定されており、当関数ではfree()せず、保持する。
 * \param connector_id 切断対象の接続情報(ConnectorProfile)のID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_BAD_PARAMETER])
 */
RTC_ReturnCode_t
impl_RTC_PortService_notify_disconnect(
  impl_POA_RTC_PortService *servant,
  const CORBA_char * connector_id,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;
  RTC_ConnectorProfile *prof = NULL;
  int i, index;
  CORBA_RTC_PortService objref;  
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 
  
  /* Search ConnectorProfile by ID. */ 
  for(i = 0; i < servant->m_portProfile->connector_profiles._length; i++){
    if(strcmp(servant->m_portProfile->connector_profiles._buffer[i].connector_id, connector_id) == 0){
      prof = &servant->m_portProfile->connector_profiles._buffer[i];
      /* Unnecessary to Error check, because this action was already done in impl_RTC_PortService_disconnect(). */
      break;
    }
  }

  /* Search current PortService in ConnectorProfile's PortServiceList by ObjRef. */ 
  for(i = 0; i < prof->ports._length; i++){
    if(CORBA_Object_is_equivalent(prof->ports._buffer[i], objref, ev)){
      if(i < (prof->ports._length - 1)){
        /* Call next PortService's notify_disconnect()  */
        retval = RTC_PortService_notify_disconnect(prof->ports._buffer[i+1], connector_id, ev);
      }
      break;
    }
    if (i == (prof->ports._length - 1))  retval = RTC_BAD_PARAMETER;  /* Not found my ObjRef */
  }

  /* Disconnect action */
  if(retval == RTC_RTC_OK){
    /* [OutPort action] ( Unset InPort's ObjectRef. ) */
    if(servant->m_portBase->m_portType == OUTPORT_TYPE)
    {
      RtORB_free(servant->m_InPortCdr,"Target InPortCdr");  
      servant->m_InPortCdr = CORBA_OBJECT_NIL;  
    }

    /* [InPort action] Destroy my InPortCdr */
    if(servant->m_portBase->m_portType == INPORT_TYPE) 
    {
#if 1  /* TODO: [Caution] Memory Release error. ("double free or corruption") */
      impl_POA_OpenRTM_InPortCdr *inportcdr_servant;
      inportcdr_servant = (impl_POA_OpenRTM_InPortCdr*)servant->m_InPortCdr->servant;
      impl_OpenRTM_InPortCdr__destroy(inportcdr_servant, ev);  
#endif
    }

    /* Delete [ConnectorProfile] */
    servant->m_portProfile->connector_profiles._length = 0;  /* Not free memory, keep 1 block size. */
    RtORB_free(servant->m_portProfile->connector_profiles._buffer[0].name, "[Conn]name");
    RtORB_free(servant->m_portProfile->connector_profiles._buffer[0].connector_id, "[Conn]id");
      /* buffer->ports */
    servant->m_portProfile->connector_profiles._buffer[0].ports._length = 0;
    RtORB_free(servant->m_portProfile->connector_profiles._buffer[0].ports._buffer, "[Conn]ports");  
    servant->m_portProfile->connector_profiles._buffer[0].ports._buffer = NULL;
      /* buffer->properties */
    NVUtil_freeNVList(&servant->m_portProfile->connector_profiles._buffer[0].properties);
      /* buffer */
    RtORB_free(servant->m_portProfile->connector_profiles._buffer, "[Conn]buffer");
    servant->m_portProfile->connector_profiles._buffer = NULL;
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}


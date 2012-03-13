/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_RTObject.c
 * \brief <RTC::RTObjectインタフェース> RTC生成のBaseとなるオブジェクトに関する処理。主に、オブジェクトの生成とProfile情報の取得関数の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : RTObject                             ***/
/***        Inheritance : RTC::LightweightRTObject           ***/
/***          Inheritance : RTC::ComponentAction             ***/
/***        Inheritance : SDOPackage::SDO                    ***/
/***          Inheritance : SDOPackage::SDOSystemElement     ***/
/***************************************************************/

CORBA_RTC_RTObject 
impl_RTC_RTObject__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_RTObject retval;
  impl_POA_RTC_RTObject *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_RTObject *)RtORB_calloc(1, sizeof(impl_POA_RTC_RTObject)," create...");
  newservant->servant.vepv = &impl_RTC_RTObject_vepv;
  newservant->poa = poa;
  POA_RTC_RTObject__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */

  newservant->m_properties = NULL;
  newservant->m_portAdmin = NULL;
  newservant->m_rtobjRef = CORBA_OBJECT_NIL;
  newservant->m_dfcompRef = CORBA_OBJECT_NIL;
  newservant->m_ecRef = CORBA_OBJECT_NIL;
  
   /* ------ ---------- end ------------- ------ */
  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

/* ====== [Add] ====== */
  /* Set myself */
  newservant->m_rtobjRef = retval;   
  /* Create and init DataFlowComponentAction (Because RTObject call on_execute(), ...) */
  newservant->m_dfcompRef = impl_RTC_DataFlowComponentAction__create(poa, ev);   
  impl_POA_RTC_DataFlowComponentAction *dfc_servant;
  dfc_servant = newservant->m_dfcompRef->servant;
  dfc_servant->m_rtobjRef = retval;
/* ====== [Add] ====== */

  return retval;
}

void
impl_RTC_RTObject__destroy(impl_POA_RTC_RTObject *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_RTObject__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_RTObject__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_RTObject *newservant;

  newservant = (impl_POA_RTC_RTObject *)RtORB_calloc(1, sizeof(impl_POA_RTC_RTObject), "  create_servant");
  newservant->servant.vepv = &impl_RTC_RTObject_vepv;
  newservant->poa = poa;
  POA_RTC_RTObject__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief 自RTCが保持(properties管理)している、RTC情報(ComponentProfile)を返す。(必須項目のみ) 
 *
 *        当関数は、[RtSystemEditor]にて、起動後に周期的にcallされる。
 * \return RTC_ComponentProfileデータ
 */
RTC_ComponentProfile*
impl_RTC_RTObject_get_component_profile(
  impl_POA_RTC_RTObject *servant,
  CORBA_Environment *ev)
{
  RTC_ComponentProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  /* <ComponentProfile> */
  /* (instance_name/type_name/description/version/vendor/category/port_profiles/parent/properties) */
  retval = RTC_ComponentProfile__alloc();

  retval->instance_name = strdup(Properties_getProperty(servant->m_properties,"instance_name"));
  retval->type_name     = strdup(Properties_getProperty(servant->m_properties,"type_name"));
  retval->description   = strdup(Properties_getProperty(servant->m_properties,"description"));
  retval->version       = strdup(Properties_getProperty(servant->m_properties,"version"));
  retval->vendor        = strdup(Properties_getProperty(servant->m_properties,"vendor"));
  retval->category      = strdup(Properties_getProperty(servant->m_properties,"category"));
  retval->parent        = CORBA_OBJECT_NIL;
    /* PortProfileList */
  Port_getPortProfileList(servant->m_portAdmin, &retval->port_profiles);
    /* properties (CORBA_sequence_SDOPackage_NameValue_allocbuf(0);) */
  retval->properties._maximum = 0; 
  retval->properties._length  = 0;
  retval->properties._buffer  = NULL;
  retval->properties._release = 0;

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 自RTCが保持(portAdmin管理)している、DataPort情報(PortServiceオブジェクトリファレンス)を返す。
 *
 *        当関数は、現状、ユーザRTCの[Comp.c]ファイル内で、デバッグ用にcallされている用途でのみ使用されている。
 * \return RTC_PortServiceListデータ(PortServiceオブジェクトリファレンスのリスト)
 */
RTC_PortServiceList*
impl_RTC_RTObject_get_ports(
  impl_POA_RTC_RTObject *servant,
  CORBA_Environment *ev)
{
  RTC_PortServiceList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));

    /* ------   insert method code here (2)  ------ */

  /* sequence<PortService(interface)> */
  retval = Port_getPortServiceList(servant->m_portAdmin);
  
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/**********************************************************************************/
/* Caution : Comment out unused functions by "#if 0". 
 * Ref : [OpenRTM-aist.h :: #define RTC_RTObject_Func ANY_OTHER-INTERFACE_Func ]  
 */
/**********************************************************************************/

#if 0

RTC_ReturnCode_t
impl_RTC_RTObject_on_initialize(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_finalize(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_startup(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_shutdown(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_activated(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_deactivated(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_aborting(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_error(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_on_reset(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_initialize(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;

    /* ------   insert method code here  (6) ------ */
fprintf(stderr, "CALL RTC_RTObject_initialize\n");
  retval = RTC_RTC_OK;
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_finalize(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_RTC_RTObject_is_alive(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContext exec_context,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_boolean retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_exit(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionContextHandle_t
impl_RTC_RTObject_attach_context(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContext exec_context,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionContextHandle_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_RTObject_detach_context(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionContext
impl_RTC_RTObject_get_context(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionContext retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionContextList*
impl_RTC_RTObject_get_owned_contexts(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionContextList* retval;
    /* ------   insert method code here  (6) ------ */
  retval = NULL;
  fprintf(stderr, "impl_RTC_RTObject_get_owned_contexts \n");
    /* ------ ---------- end ------------ ------ */

  return retval;
}


RTC_ExecutionContextList*
impl_RTC_RTObject_get_participating_contexts(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionContextList* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionContextHandle_t
impl_RTC_RTObject_get_context_handle(
    impl_POA_RTC_RTObject *servant,
    RTC_ExecutionContext cxt,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionContextHandle_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_OrganizationList*
impl_RTC_RTObject_get_owned_organizations(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_OrganizationList* retval;
    /* ------   insert method code here  (6) ------ */
  retval=NULL;
  fprintf(stderr, " impl_RTC_RTObjec_get_owned_organizations \n");
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_UniqueIdentifier
impl_RTC_RTObject_get_sdo_id(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_UniqueIdentifier retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_string
impl_RTC_RTObject_get_sdo_type(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_string retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_DeviceProfile*
impl_RTC_RTObject_get_device_profile(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_DeviceProfile* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ServiceProfileList*
impl_RTC_RTObject_get_service_profiles(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_ServiceProfileList* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ServiceProfile*
impl_RTC_RTObject_get_service_profile(
    impl_POA_RTC_RTObject *servant,
    const CORBA_char * id,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_ServiceProfile* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_SDOService
impl_RTC_RTObject_get_sdo_service(
    impl_POA_RTC_RTObject *servant,
    const CORBA_char * id,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_SDOService retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_Monitoring
impl_RTC_RTObject_get_monitoring(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_Monitoring retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_OrganizationList*
impl_RTC_RTObject_get_organizations(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_OrganizationList* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_NVList*
impl_RTC_RTObject_get_status_list(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_NVList* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_any*
impl_RTC_RTObject_get_status(
    impl_POA_RTC_RTObject *servant,
    const CORBA_char * nme,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_any* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_Configuration
impl_RTC_RTObject_get_configuration(
    impl_POA_RTC_RTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_Configuration retval;
    /* ------   insert method code here  (6) ------ */
  retval = NULL;
  fprintf(stderr, " impl_RTC_RTObject_get_configuration\n");
    /* ------ ---------- end ------------ ------ */

  return retval;
}

#endif

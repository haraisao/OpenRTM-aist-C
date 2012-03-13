/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_OpenRTM_ExtTrigExecutionContextService.c
 * \brief (未使用)
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : OpenRTM                                ***/
/***      Interface   : ExtTrigExecutionContextService       ***/
/***        Inheritance : RTC::ExecutionContextService       ***/
/***          Inheritance : RTC::ExecutionContext            ***/
/***          Inheritance : SDOPackage::SDOService  [Empty]  ***/
/***************************************************************/

CORBA_OpenRTM_ExtTrigExecutionContextService 
impl_OpenRTM_ExtTrigExecutionContextService__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_OpenRTM_ExtTrigExecutionContextService retval;
  impl_POA_OpenRTM_ExtTrigExecutionContextService *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_OpenRTM_ExtTrigExecutionContextService *)RtORB_calloc(1, sizeof(impl_POA_OpenRTM_ExtTrigExecutionContextService)," create...");
  newservant->servant.vepv = &impl_OpenRTM_ExtTrigExecutionContextService_vepv;
  newservant->poa = poa;
  POA_OpenRTM_ExtTrigExecutionContextService__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */
   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_OpenRTM_ExtTrigExecutionContextService__destroy(impl_POA_OpenRTM_ExtTrigExecutionContextService *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_OpenRTM_ExtTrigExecutionContextService__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_OpenRTM_ExtTrigExecutionContextService__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_OpenRTM_ExtTrigExecutionContextService *newservant;

  newservant = (impl_POA_OpenRTM_ExtTrigExecutionContextService *)RtORB_calloc(1, sizeof(impl_POA_OpenRTM_ExtTrigExecutionContextService), "  create_servant");
  newservant->servant.vepv = &impl_OpenRTM_ExtTrigExecutionContextService_vepv;
  newservant->poa = poa;
  POA_OpenRTM_ExtTrigExecutionContextService__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */
   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

void
impl_OpenRTM_ExtTrigExecutionContextService_tick(
  impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
  CORBA_Environment *ev)
{
    /* ------   insert method code here  (4) ------ */
    /* ------ ---------- end ------------ ------ */
}




/**********************************************************************************/
/* Caution : Comment out unused functions by "#if 0". 
 * Ref : [OpenRTM-aist.h :: #define OpenRTM_ExtTrigExecutionContextService_Func RTC_RTC_ExecutionContext_Func ]  
 */
/**********************************************************************************/

#if 0 

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_stop(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_double
impl_OpenRTM_ExtTrigExecutionContextService_get_rate(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_double retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_set_rate(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_double rate,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionKind
impl_OpenRTM_ExtTrigExecutionContextService_get_kind(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionKind retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_add_component(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_remove_component(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_reset_component(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_OpenRTM_ExtTrigExecutionContextService_is_running(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_boolean retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_start(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_activate_component(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_OpenRTM_ExtTrigExecutionContextService_deactivate_component(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_LifeCycleState
impl_OpenRTM_ExtTrigExecutionContextService_get_component_state(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_LifeCycleState retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionContextProfile*
impl_OpenRTM_ExtTrigExecutionContextService_get_profile(
    impl_POA_OpenRTM_ExtTrigExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionContextProfile* retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

#endif

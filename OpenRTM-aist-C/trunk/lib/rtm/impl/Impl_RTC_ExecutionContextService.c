/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_ExecutionContextService.c
 * \brief <RTC::ExecutionContextServiceインタフェース> 主に、ExecutionContextServiceの生成と、get_profile()関数の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : ExecutionContextService              ***/
/***        Inheritance : RTC::ExecutionContext              ***/
/***        Inheritance : SDOPackage::SDOService  [Empty]    ***/
/***************************************************************/

CORBA_RTC_ExecutionContextService 
impl_RTC_ExecutionContextService__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_ExecutionContextService retval;
  impl_POA_RTC_ExecutionContextService *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_ExecutionContextService *)RtORB_calloc(1, sizeof(impl_POA_RTC_ExecutionContextService)," create...");
  newservant->servant.vepv = &impl_RTC_ExecutionContextService_vepv;
  newservant->poa = poa;
  POA_RTC_ExecutionContextService__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
  newservant->m_ecProfile.kind = RTC_PERIODIC;  /* fixed value */
  newservant->m_ecProfile.rate = 0;
  newservant->m_ecProfile.owner = CORBA_OBJECT_NIL;
  newservant->m_running = 0;  
  newservant->m_states = NULL;
  newservant->m_callback = NULL;
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTC_ExecutionContextService__destroy(impl_POA_RTC_ExecutionContextService *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_ExecutionContextService__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_ExecutionContextService__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_ExecutionContextService *newservant;

  newservant = (impl_POA_RTC_ExecutionContextService *)RtORB_calloc(1, sizeof(impl_POA_RTC_ExecutionContextService), "  create_servant");
  newservant->servant.vepv = &impl_RTC_ExecutionContextService_vepv;
  newservant->poa = poa;
  POA_RTC_ExecutionContextService__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief ExecutionContextService生成時の初期値を元に、ExecutionContextProfileを生成し返す。
 * 
 *        ("rate"はset_rate()により変更されてる場合あり、また、[participants][properties]は無しとする。)<BR>
 *        当関数は、[RtSystemEditor]にて、起動後に周期的にcallされる。
 * \return ECが保持するExecutionContextProfile型データ 
 */
RTC_ExecutionContextProfile*
impl_RTC_ExecutionContextService_get_profile(
  impl_POA_RTC_ExecutionContextService *servant,
  CORBA_Environment *ev)
{
  RTC_ExecutionContextProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  /* <ExecutionContextProfile> (kind/rate/owner/participants/properties) */
  retval = RTC_ExecutionContextProfile__alloc();
  retval->kind = servant->m_ecProfile.kind;
  retval->rate = servant->m_ecProfile.rate;
  retval->owner = CORBA_Object_dup(servant->m_ecProfile.owner);
  /* [participants] (NULL) */ 
  retval->participants._length = 0;
  retval->participants._maximum = 0;
  retval->participants._release = 0;
  retval->participants._buffer = NULL;
  /* [properties] (NULL) */ 
  retval->properties._length = 0;
  retval->properties._maximum = 0;
  retval->properties._release = 0;
  retval->properties._buffer = NULL;

    /* ------ ---------- end ------------ ------ */

  return retval;
}




/**********************************************************************************/
/* Caution : Comment out unused functions by "#if 0". 
 * Ref : [OpenRTM-aist.h :: #define RTC_ExecutionContextService_Func RTC_ExecutionContext_Func ]  
 */
/**********************************************************************************/

#if 0

RTC_ReturnCode_t
impl_RTC_ExecutionContextService_stop(
    impl_POA_RTC_ExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_double
impl_RTC_ExecutionContextService_get_rate(
    impl_POA_RTC_ExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_double retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_ExecutionContextService_set_rate(
    impl_POA_RTC_ExecutionContextService *servant,
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
impl_RTC_ExecutionContextService_get_kind(
    impl_POA_RTC_ExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ExecutionKind retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_ExecutionContextService_add_component(
    impl_POA_RTC_ExecutionContextService *servant,
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
impl_RTC_ExecutionContextService_remove_component(
    impl_POA_RTC_ExecutionContextService *servant,
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
impl_RTC_ExecutionContextService_reset_component(
    impl_POA_RTC_ExecutionContextService *servant,
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
impl_RTC_ExecutionContextService_is_running(
    impl_POA_RTC_ExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  CORBA_boolean retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_ExecutionContextService_start(
    impl_POA_RTC_ExecutionContextService *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_ExecutionContextService_activate_component(
    impl_POA_RTC_ExecutionContextService *servant,
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
impl_RTC_ExecutionContextService_deactivate_component(
    impl_POA_RTC_ExecutionContextService *servant,
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
impl_RTC_ExecutionContextService_get_component_state(
    impl_POA_RTC_ExecutionContextService *servant,
    RTC_LightweightRTObject comp,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_LifeCycleState retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

#endif

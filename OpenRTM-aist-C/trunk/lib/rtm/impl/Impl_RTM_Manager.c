/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTM_Manager.c
 * \brief (未使用) (ManagerServantの生成の場合には使用)
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTM                                    ***/
/***      Interface   : Manager                              ***/
/***************************************************************/


CORBA_RTM_Manager 
impl_RTM_Manager__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTM_Manager retval;
  impl_POA_RTM_Manager *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTM_Manager *)RtORB_calloc(1, sizeof(impl_POA_RTM_Manager)," create...");
  newservant->servant.vepv = &impl_RTM_Manager_vepv;
  newservant->poa = poa;
  POA_RTM_Manager__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTM_Manager__destroy(impl_POA_RTM_Manager *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTM_Manager__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTM_Manager__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTM_Manager *newservant;

  newservant = (impl_POA_RTM_Manager *)RtORB_calloc(1, sizeof(impl_POA_RTM_Manager), "  create_servant");
  newservant->servant.vepv = &impl_RTM_Manager_vepv;
  newservant->poa = poa;
  POA_RTM_Manager__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

RTC_ReturnCode_t
impl_RTM_Manager_load_module(
  impl_POA_RTM_Manager *servant,
  const CORBA_char * pathname,
  const CORBA_char * initfunc,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_unload_module(
  impl_POA_RTM_Manager *servant,
  const CORBA_char * pathname,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_ModuleProfileList*
impl_RTM_Manager_get_loadable_modules(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_ModuleProfileList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_ModuleProfileList*
impl_RTM_Manager_get_loaded_modules(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_ModuleProfileList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_ModuleProfileList*
impl_RTM_Manager_get_factory_profiles(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_ModuleProfileList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_RTObject
impl_RTM_Manager_create_component(
  impl_POA_RTM_Manager *servant,
  const CORBA_char * module_name,
  CORBA_Environment *ev)
{
  RTC_RTObject retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_delete_component(
  impl_POA_RTM_Manager *servant,
  const CORBA_char * instance_name,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_RTCList*
impl_RTM_Manager_get_components(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTC_RTCList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ComponentProfileList*
impl_RTM_Manager_get_component_profiles(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTC_ComponentProfileList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_ManagerProfile*
impl_RTM_Manager_get_profile(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_ManagerProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_NVList*
impl_RTM_Manager_get_configuration(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_NVList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_set_configuration(
  impl_POA_RTM_Manager *servant,
  const CORBA_char * name,
  const CORBA_char * value,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_RTM_Manager_is_master(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_ManagerList*
impl_RTM_Manager_get_master_managers(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_ManagerList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_add_master_manager(
  impl_POA_RTM_Manager *servant,
  RTM_Manager mgr,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_remove_master_manager(
  impl_POA_RTM_Manager *servant,
  RTM_Manager mgr,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTM_ManagerList*
impl_RTM_Manager_get_slave_managers(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTM_ManagerList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_add_slave_manager(
  impl_POA_RTM_Manager *servant,
  RTM_Manager mgr,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_remove_slave_manager(
  impl_POA_RTM_Manager *servant,
  RTM_Manager mgr,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_fork(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_shutdown(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTM_Manager_restart(
  impl_POA_RTM_Manager *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_Object
impl_RTM_Manager_get_service(
  impl_POA_RTM_Manager *servant,
  const CORBA_char * name,
  CORBA_Environment *ev)
{
  CORBA_Object retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}



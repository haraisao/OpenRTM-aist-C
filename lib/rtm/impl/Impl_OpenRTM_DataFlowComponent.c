/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_OpenRTM_DataFlowComponent.c
 * \brief (未使用)
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : OpenRTM                                ***/
/***      Interface   : DataFlowComponent                    ***/
/***        Inheritance : RTC::DataFlowComponent             ***/
/***          Inheritance : RTC::DataFlowComponentAction     ***/
/***  --[Delete bellow]--                                    ***/
/***        Inheritance : RTC::RTObject                      ***/
/***          Inheritance : RTC::LightweightRTObject         ***/
/***            Inheritance : RTC::ComponentAction           ***/
/***          Inheritance : SDOPackage::SDO                  ***/
/***            Inheritance : SDOPackage::SDOSystemElement   ***/
/***************************************************************/



CORBA_OpenRTM_DataFlowComponent 
impl_OpenRTM_DataFlowComponent__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_OpenRTM_DataFlowComponent retval;
  impl_POA_OpenRTM_DataFlowComponent *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_OpenRTM_DataFlowComponent *)RtORB_calloc(1, sizeof(impl_POA_OpenRTM_DataFlowComponent)," create...");
  newservant->servant.vepv = &impl_OpenRTM_DataFlowComponent_vepv;
  newservant->poa = poa;
  POA_OpenRTM_DataFlowComponent__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */
   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_OpenRTM_DataFlowComponent__destroy(impl_POA_OpenRTM_DataFlowComponent *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_OpenRTM_DataFlowComponent__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_OpenRTM_DataFlowComponent__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_OpenRTM_DataFlowComponent *newservant;

  newservant = (impl_POA_OpenRTM_DataFlowComponent *)RtORB_calloc(1, sizeof(impl_POA_OpenRTM_DataFlowComponent), "  create_servant");
  newservant->servant.vepv = &impl_OpenRTM_DataFlowComponent_vepv;
  newservant->poa = poa;
  POA_OpenRTM_DataFlowComponent__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */
   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}


/**********************************************************************************/
/* Caution : Comment out unused functions by "#if 0". 
 * Ref : [OpenRTM-aist.h :: #define OpenRTM_DataFlowComponent_Func ANY_OTHER-INTERFACE_Func ]  
 */
/**********************************************************************************/

#if 0

RTC_ReturnCode_t
impl_OpenRTM_DataFlowComponent_on_execute(
    impl_POA_OpenRTM_DataFlowComponent *servant,
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
impl_OpenRTM_DataFlowComponent_on_state_update(
    impl_POA_OpenRTM_DataFlowComponent *servant,
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
impl_OpenRTM_DataFlowComponent_on_rate_changed(
    impl_POA_OpenRTM_DataFlowComponent *servant,
    RTC_ExecutionContextHandle_t exec_handle,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

#endif 


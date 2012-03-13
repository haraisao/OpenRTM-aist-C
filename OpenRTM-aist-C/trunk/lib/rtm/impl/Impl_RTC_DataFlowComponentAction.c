/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_DataFlowComponentAction.c
 * \brief <RTC::DataFlowComponentActionインタフェース> 各種RTCのactivityに該当する関数の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : DataFlowComponentAction              ***/
/***************************************************************/

CORBA_RTC_DataFlowComponentAction 
impl_RTC_DataFlowComponentAction__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_DataFlowComponentAction retval;
  impl_POA_RTC_DataFlowComponentAction *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_DataFlowComponentAction *)RtORB_calloc(1, sizeof(impl_POA_RTC_DataFlowComponentAction)," create...");
  newservant->servant.vepv = &impl_RTC_DataFlowComponentAction_vepv;
  newservant->poa = poa;
  POA_RTC_DataFlowComponentAction__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */

  newservant->m_rtobjRef = CORBA_OBJECT_NIL; 

   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTC_DataFlowComponentAction__destroy(impl_POA_RTC_DataFlowComponentAction *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_DataFlowComponentAction__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_DataFlowComponentAction__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_DataFlowComponentAction *newservant;

  newservant = (impl_POA_RTC_DataFlowComponentAction *)RtORB_calloc(1, sizeof(impl_POA_RTC_DataFlowComponentAction), "  create_servant");
  newservant->servant.vepv = &impl_RTC_DataFlowComponentAction_vepv;
  newservant->poa = poa;
  POA_RTC_DataFlowComponentAction__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief 当関数は、RTCがACTIVE状態にある期間の間は、第2周期関数として周期的にcallされる。 ユーザRTC内でCallback関数が設定されていればcallする。
 *
 * 以下の状態が保持されている場合に、設定された周期で定期的に呼び出される。
 * - RTC は Alive 状態である。
 * - 指定された ExecutionContext が Running 状態である。
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_DataFlowComponentAction_on_execute(
  impl_POA_RTC_DataFlowComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_RTObject objref = servant->m_rtobjRef;  

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onExecute)
  {
    retval = (comp->onExecute)(comp, exec_handle); 
  }

   /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 当関数は、on_execute()実行の直後に第2周期関数としてcallされる。 ユーザRTC内でCallback関数が設定されていればcallする。
 *
 * 以下の状態が保持されている場合に、設定された周期で定期的に呼び出される。
 * - RTC は Alive 状態である。
 * - 指定された ExecutionContext が Running 状態である。
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_DataFlowComponentAction_on_state_update(
  impl_POA_RTC_DataFlowComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_RTObject objref = servant->m_rtobjRef;  

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onStateUpDate)
  {
    retval = (comp->onStateUpDate)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ExecutionContext の実行周期が変更されたことを通知する。ユーザRTC内でCallback関数が設定されていればcallする。 
 *
 *        当関数は、impl_RTC_ExecutionContext_set_rate()内からcallされる。
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_DataFlowComponentAction_on_rate_changed(
  impl_POA_RTC_DataFlowComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_RTObject objref = servant->m_rtobjRef;  

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onRateChanged)
  {
    retval = (comp->onRateChanged)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}



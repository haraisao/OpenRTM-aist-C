/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_ComponentAction.c
 * \brief <RTC::ComponentActionインタフェース> 各種RTCのactivityに該当する関数の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : ComponentAction                      ***/
/***************************************************************/

CORBA_RTC_ComponentAction 
impl_RTC_ComponentAction__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_ComponentAction retval;
  impl_POA_RTC_ComponentAction *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_ComponentAction *)RtORB_calloc(1, sizeof(impl_POA_RTC_ComponentAction)," create...");
  newservant->servant.vepv = &impl_RTC_ComponentAction_vepv;
  newservant->poa = poa;
  POA_RTC_ComponentAction__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTC_ComponentAction__destroy(impl_POA_RTC_ComponentAction *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_ComponentAction__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_ComponentAction__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_ComponentAction *newservant;

  newservant = (impl_POA_RTC_ComponentAction *)RtORB_calloc(1, sizeof(impl_POA_RTC_ComponentAction), "  create_servant");
  newservant->servant.vepv = &impl_RTC_ComponentAction_vepv;
  newservant->poa = poa;
  POA_RTC_ComponentAction__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief RTC が初期化され、Alive 状態に遷移する。RTC 固有の初期化処理はここで実行する。 ユーザRTC内でCallback関数(onInitialize())が必ず設定されていなければならない。 
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_initialize(
  impl_POA_RTC_ComponentAction *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onInitialize)
  {
    retval = (comp->onInitialize)(comp); 
  } else {
    /* Because [onInitialize()] needs to be implemented. */
    fprintf(stderr, " [ERROR] Can't call onInitialize().\n");
    retval = RTC_RTC_ERROR;
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTC が破棄される。RTC固有の終了処理はここで実行する。 ユーザRTC内でCallback関数が設定されていればcallする。 
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_finalize(
  impl_POA_RTC_ComponentAction *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onFinalize)
  {
    retval = (comp->onFinalize)(comp);  
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ExecutionContextを開始(Stop状態からRunning状態へ遷移)する際に、当関数が実行される。 ユーザRTC内でCallback関数が設定されていればcallする。 
 *
 *        RtSystemEditorの[Start]選択時にもcallされる。 
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_startup(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onStartup)
  {
    retval = (comp->onStartup)(comp, exec_handle);  
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ExecutionContextを停止(Running状態からStop状態へ遷移)する際に、当関数が実行される。 ユーザRTC内でCallback関数が設定されていればcallする。 
 *
 *        RtSystemEditorの[Stop]選択時にもcallされる。 
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_shutdown(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onShutdown)
  {
    retval = (comp->onShutdown)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCがACTIVE状態に遷移する際に、一度だけ当関数が実行される。その後は、on_execute()が周期的に実行される。 ユーザRTC内でCallback関数が設定されていればcallする。 
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_activated(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onActivated)
  {
    retval = (comp->onActivated)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCがINACTIVE状態に遷移する際に、一度だけ当関数が実行される。 ユーザRTC内でCallback関数が設定されていればcallする。
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_deactivated(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onDeactivated)
  {
    retval = (comp->onDeactivated)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCがACTIVE状態からERROR状態に遷移した際に、一度だけ当関数が実行される。その後は、on_error()が周期的に実行される。 ユーザRTC内でCallback関数が設定されていればcallする。 
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_aborting(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onAborting)
  {
    retval = (comp->onAborting)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief on_abort()実行後、RTCがERROR状態の間、周期的に実行される。 ユーザRTC内でCallback関数が設定されていればcallする。 
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_error(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onError)
  {
    retval = (comp->onError)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ERROR状態にあるRTCが復帰可能となった場合に、ERROR状態に復帰させる場合callされる。外部から実行指令がくることを想定。 ユーザRTC内でCallback関数が設定されていればcallする。
 *
 *        RtSystemEditorの[Reset]選択時にcallされる。<BR>
 *        RTC のリカバリ処理が成功した場合は Inactive 状態に復帰するが、それ以外の場合には Error 状態に留まる。 
 * \param exec_handle ECのID
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_ComponentAction_on_reset(
  impl_POA_RTC_ComponentAction *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_RTC_OK;

  CORBA_RTC_ComponentAction objref;   
  objref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  RTComp *comp = (RTComp*)objref->impl_obj;
  if (comp->onReset)
  {
    retval = (comp->onReset)(comp, exec_handle); 
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}



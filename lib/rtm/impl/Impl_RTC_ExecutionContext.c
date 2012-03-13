/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_ExecutionContext.c
 * \brief <RTC::ExecutionContextインタフェース> 各種RTCのExecutionContext(EC)の処理に該当する関数の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : ExecutionContext                     ***/
/***************************************************************/

CORBA_RTC_ExecutionContext 
impl_RTC_ExecutionContext__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_ExecutionContext retval;
  impl_POA_RTC_ExecutionContext *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_ExecutionContext *)RtORB_calloc(1, sizeof(impl_POA_RTC_ExecutionContext)," create...");
  newservant->servant.vepv = &impl_RTC_ExecutionContext_vepv;
  newservant->poa = poa;
  POA_RTC_ExecutionContext__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTC_ExecutionContext__destroy(impl_POA_RTC_ExecutionContext *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_ExecutionContext__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_ExecutionContext__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_ExecutionContext *newservant;

  newservant = (impl_POA_RTC_ExecutionContext *)RtORB_calloc(1, sizeof(impl_POA_RTC_ExecutionContext), "  create_servant");
  newservant->servant.vepv = &impl_RTC_ExecutionContext_vepv;
  newservant->poa = poa;
  POA_RTC_ExecutionContext__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief ECの現在のStatus(Running状態 or Stop状態)を[isRunning]フラグとして返す。<BR>
 *        当関数は、[RtSystemEditor]にて、起動後に周期的にcallされる。
 * \return ECの現在のStatusフラグ([1]:Running / [0]:Stop)
 */
CORBA_boolean
impl_RTC_ExecutionContext_is_running(
  impl_POA_RTC_ExecutionContext *servant,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant; 
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  retval = ecs_servant->m_running; /* [1]:Start / [0]:Stop */

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ExecutionContextの実行を開始する。 ECの状態[m_running]をTRUEに変更し、内部で、RTC_ComponentAction_on_startupをcallする。 
 *
 *        指定したECの状態が[Stop]以外の場合は、 PRECONDITION_NOT_MET が返される。<BR>
 *        当関数は、[RtSystemEditor]にて、[start]を選択した時にcallされる。 また、RTC_LightweightRTObject_initialize()時にもcallされる。
 *
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR]/前提のStop状態にない:[RTC_PRECONDITION_NOT_MET])
 */
RTC_ReturnCode_t
impl_RTC_ExecutionContext_start(
  impl_POA_RTC_ExecutionContext *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  if (ecs_servant->m_running) {
    retval = RTC_PRECONDITION_NOT_MET;
  } else {  
    ecs_servant->m_running = 1;
    retval = RTC_ComponentAction_on_startup(ecs_servant->m_ecProfile.owner, 0, ev);
  }
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ExecutionContextの実行を停止する。 ECの状態[m_running]をFALSEに変更し、内部で、RTC_ComponentAction_on_shutdownをcallする。 
 *
 *        指定したECの状態が[Running]以外の場合は、 PRECONDITION_NOT_MET が返される。<BR>
 *        当関数は、[RtSystemEditor]にて、[stop]を選択した時にcallされる。また、RTC_LightweightRTObject_finalize()時にもcallされる。
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR]/前提のRunning状態にない:[RTC_PRECONDITION_NOT_MET])
 */
RTC_ReturnCode_t
impl_RTC_ExecutionContext_stop(
  impl_POA_RTC_ExecutionContext *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  if (!ecs_servant->m_running) {
    retval = RTC_PRECONDITION_NOT_MET;
  } else {  
    ecs_servant->m_running = 0;
    retval = RTC_ComponentAction_on_shutdown(ecs_servant->m_ecProfile.owner, 0, ev);
  }
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 内部保持しているECの実行周期用の周波数[Hz]を返すのみ。
 * \return 内部保持しているECの実行周期用の周波数[Hz]
 */
CORBA_double
impl_RTC_ExecutionContext_get_rate(
  impl_POA_RTC_ExecutionContext *servant,
  CORBA_Environment *ev)
{
  CORBA_double retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  retval = ecs_servant->m_ecProfile.rate;
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 引数の実行周波数[Hz]([rate])を内部セットする。さらに、変更後の処理として、RTC_DataFlowComponentAction_on_rate_changed()をcallし、RTC側へ変更を通知する。
 *
 *        引数の[rate]に設定可能な値は、[rate > 0.0]とする。違反した場合は、retvalに[RTC_BAD_PARAMETER]をセットする。
 * \param rate 設定する実行周波数[Hz]
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/エラー:[RTC_BAD_PARAMETER])
 */
RTC_ReturnCode_t
impl_RTC_ExecutionContext_set_rate(
  impl_POA_RTC_ExecutionContext *servant,
  CORBA_double rate,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  impl_POA_RTC_RTObject *rtobj_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;
  rtobj_servant = (impl_POA_RTC_RTObject *)ecs_servant->m_ecProfile.owner->servant;

  if (rate > 0.0) {
    ecs_servant->m_ecProfile.rate = rate;
    /* Call on_rate_changed() */
    retval = RTC_DataFlowComponentAction_on_rate_changed(rtobj_servant->m_dfcompRef, 0, ev);
  }else{
    retval = RTC_BAD_PARAMETER;
  }

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ECの親となるRTCをINACTIVE状態からACTIVE状態へ遷移させる。(RTCの活性化)
 *
 *        指定したRTCの状態が[INACTIVE]以外の場合は、 PRECONDITION_NOT_MET が返される。<BR>
 *        当関数は、[RtSystemEditor]にて、[Activate]を選択した時にcallされる。
 * \param comp Activate対象となるRTCのオブジェクトリファレンス
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/前提のINACTIVE状態にない:[RTC_PRECONDITION_NOT_MET])
 */
RTC_ReturnCode_t
impl_RTC_ExecutionContext_activate_component(
  impl_POA_RTC_ExecutionContext *servant,
  RTC_LightweightRTObject comp,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  if(ecs_servant->m_states->curr == RTC_INACTIVE_STATE){ 
    ecs_servant->m_states->next = RTC_ACTIVE_STATE;
    retval = RTC_RTC_OK;
  }else{
    retval = RTC_PRECONDITION_NOT_MET;
  }
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ECの親となるRTCをACTIVE状態からINACTIVE状態へ遷移させる。(RTCの非活性化)
 *
 *        指定したRTCの状態が[ACTIVE]以外の場合は、 PRECONDITION_NOT_MET が返される。<BR>
 *        当関数は、[RtSystemEditor]にて、[Deactivate]を選択した時にcallされる。また、RTC_LightweightRTObject_exit()時にもcallされる。
 * \param comp Deactivate対象となるRTCのオブジェクトリファレンス
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/前提のACTIVE状態にない:[RTC_PRECONDITION_NOT_MET])
 */
RTC_ReturnCode_t
impl_RTC_ExecutionContext_deactivate_component(
  impl_POA_RTC_ExecutionContext *servant,
  RTC_LightweightRTObject comp,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  if(ecs_servant->m_states->curr == RTC_ACTIVE_STATE){
    ecs_servant->m_states->next = RTC_INACTIVE_STATE;
    retval = RTC_RTC_OK;
  }else{
    retval = RTC_PRECONDITION_NOT_MET;
  }
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief ECの親となるRTCをERROR状態からINACTIVE状態へ遷移させる。(RTCのエラーからの復帰)
 *
 *        指定したRTCの状態が[ERROR]以外の場合は、 PRECONDITION_NOT_MET が返される。<BR>
 *        当関数は、[RtSystemEditor]にて、[Reset]を選択した時にcallされる。
 * \param comp Reset対象となるRTCのオブジェクトリファレンス
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/前提のERROR状態にない:[RTC_PRECONDITION_NOT_MET])
 */
RTC_ReturnCode_t
impl_RTC_ExecutionContext_reset_component(
  impl_POA_RTC_ExecutionContext *servant,
  RTC_LightweightRTObject comp,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  if(ecs_servant->m_states->curr == RTC_ERROR_STATE){
    ecs_servant->m_states->next = RTC_INACTIVE_STATE;
    retval = RTC_RTC_OK;
  }else{
    retval = RTC_PRECONDITION_NOT_MET;
  }
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 現在のRTCの状態(CREATED/INACTIVE/ACTIVE/ERROR)を返すのみ。
 *
 *        当関数は、[RtSystemEditor]にて、起動後に周期的にcallされる。
 * \param comp 対象となるRTCのオブジェクトリファレンス
 * \return 現在のRTCの状態(CREATED/INACTIVE/ACTIVE/ERROR)
 */
RTC_LifeCycleState
impl_RTC_ExecutionContext_get_component_state(
  impl_POA_RTC_ExecutionContext *servant,
  RTC_LightweightRTObject comp,
  CORBA_Environment *ev)
{
  RTC_LifeCycleState retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  retval = ecs_servant->m_states->curr; 
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 内部保持しているECの種類(通常は[PERIDIC])を返すのみ。
 * \return 内部保持しているECの種類(通常は[PERIDIC])
 */
RTC_ExecutionKind
impl_RTC_ExecutionContext_get_kind(
  impl_POA_RTC_ExecutionContext *servant,
  CORBA_Environment *ev)
{
  RTC_ExecutionKind retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)servant;

  retval = ecs_servant->m_ecProfile.kind;
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*
 RTCオブジェクトとExecutionContextは1対1対応とするため、この処理は不要として未実装。
*/
RTC_ReturnCode_t
impl_RTC_ExecutionContext_add_component(
  impl_POA_RTC_ExecutionContext *servant,
  RTC_LightweightRTObject comp,
  CORBA_Environment *ev)
{

  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*
 RTCオブジェクトとExecutionContextは1対1対応とするため、この処理は不要として未実装。
*/
RTC_ReturnCode_t
impl_RTC_ExecutionContext_remove_component(
  impl_POA_RTC_ExecutionContext *servant,
  RTC_LightweightRTObject comp,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}


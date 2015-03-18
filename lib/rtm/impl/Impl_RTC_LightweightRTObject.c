/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_RTC_LightweightRTObject.c
 * \brief <RTC::LightweightRTObjectインタフェース> 主に、LightweightRTObjectの主要関数[initialize()/finalize()/exit()]と、その他の実装がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : RTC                                    ***/
/***      Interface   : LightweightRTObject                  ***/
/***        Inheritance : RTC::ComponentAction               ***/
/***************************************************************/

CORBA_RTC_LightweightRTObject 
impl_RTC_LightweightRTObject__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_RTC_LightweightRTObject retval;
  impl_POA_RTC_LightweightRTObject *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_RTC_LightweightRTObject *)RtORB_calloc(1, sizeof(impl_POA_RTC_LightweightRTObject)," create...");
  newservant->servant.vepv = &impl_RTC_LightweightRTObject_vepv;
  newservant->poa = poa;
  POA_RTC_LightweightRTObject__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_RTC_LightweightRTObject__destroy(impl_POA_RTC_LightweightRTObject *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_RTC_LightweightRTObject__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_RTC_LightweightRTObject__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_RTC_LightweightRTObject *newservant;

  newservant = (impl_POA_RTC_LightweightRTObject *)RtORB_calloc(1, sizeof(impl_POA_RTC_LightweightRTObject), "  create_servant");
  newservant->servant.vepv = &impl_RTC_LightweightRTObject_vepv;
  newservant->poa = poa;
  POA_RTC_LightweightRTObject__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief RTCの初期化処理。RTCを生成した場合には必ず当関数がcallされる。RTCに関連するECも生成する。
 *
 *        [RTC_Manager_createComponent()]からcallされる。RTCのミドルウエアからのみ呼ばれることを想定しており、アプリケーション開発者は直接このオペレーションを呼ぶことは想定されていない。
 *
 *        (1) [RTC_ExecutionContextService]型オブジェクトを生成し、さらにスレッドを生成し、関連付ける。<BR>
 *        (2) [ExecutionContext_bindObject()]をcallし、[RTObject]と[ExecutionContext]のオブジェクトリファレンスを相互リンクさせる。<BR>
 *        (3) [ExecutionContext_initStateMachine()]をcallし、ECの状態遷移用の各種パラメータを初期化する。<BR>
 *        (4) [RTObject]が持つ[m_properties]よりコンフィグ値として、登録されているECの[rate]を取得し、[set_rate()]を実行し、初期値としてセットする。<BR>
 *        (5) [RTC_ComponentAction_on_initialize()]をcallし、初期化を行う。ユーザRTCのCallback関数[onInitialize()]もここからcallされる。<BR>
 *        (6) [RTC_ExecutionContextService_start()]をcallし、ECをStartさせる。内部で、[RTC_ComponentAction_on_startup()]がcallされる。
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_LightweightRTObject_initialize(
  impl_POA_RTC_LightweightRTObject *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  /*=== create ExecutionContext ===*/
  CORBA_RTC_ExecutionContextService ecs_ref; 
  CORBA_RTC_RTObject rtobj_ref; 
  CORBA_RTC_LightweightRTObject lwobj_ref;
  impl_POA_RTC_RTObject *rtobj_servant;
  impl_POA_RTC_ExecutionContextService *ecs_servant;
  CORBA_double rate;

  double RTObject_getExecutionContextRate();
  
  rtobj_servant = (impl_POA_RTC_RTObject *)servant;
  rtobj_ref = PortableServer_POA_servant_to_reference(rtobj_servant->poa, rtobj_servant, ev); 
  lwobj_ref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  /* Create Execution Context Service (PeriodicExecutionContext) */
  ecs_ref = impl_RTC_ExecutionContextService__create(servant->poa, ev);
  if (ecs_ref == NULL) {
    fprintf(stderr, "ERROR: Can't create ExecutionContext.\n");
    return RTC_RTC_ERROR;
  } else {
    /* Create Thread and bind to ExecutionContextService */
    if (ExecutionContext_createThread(ecs_ref) == 0) {
      fprintf(stderr, "ERROR: Can't create Thread for ExecutionContext.\n");
      return RTC_RTC_ERROR;
    }
  }

  /* Set RTObject object and ExecutionContext object each other. */
  ExecutionContext_bindObject(ecs_ref, rtobj_ref);

  /* Get and Set EC rate (from configuration ["exec_cxt.periodic.rate"]) */
  ecs_servant = ecs_ref->servant;
  rate = (CORBA_double)RTObject_getExecutionContextRate(rtobj_ref);

  clearEnvironment(ev);
  retval = RTC_ExecutionContext_set_rate(ecs_ref, rate, ev);
  if (retval != RTC_RTC_OK) { 
    fprintf(stderr, "ERROR: Can't set ExecutionContext rate.\n");
    return retval;
  }

  /* Init StateMachine parameters of EC */
  ExecutionContext_initStateMachine(ecs_ref);

  /* Initialize RTC [call on_Initialize()] */
  clearEnvironment(ev);
  retval = RTC_ComponentAction_on_initialize(lwobj_ref,ev); 
  if (retval != RTC_RTC_OK)    return retval;

  /* Start ExecutionContext [call start()] */
  clearEnvironment(ev);
  retval = RTC_ExecutionContextService_start(ecs_ref, ev);

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCの終了処理。
 *
 *        [RTC_LightweightRTObject_exit()]からcallされる。RTCのミドルウエアからのみ呼ばれることを想定しており、アプリケーション開発者は直接このオペレーションを呼ぶことは想定されていない。
 *
 *        (1) [RTC_ExecutionContext_stop()]をcallし、ECを停止させる。 さらに、[ExecutionContext_deleteStateMachine()]により、StateMachineを削除する。<BR>
 *        (2) [RTC_ComponentAction_on_finalize()]をcallし、RTC終了用のCallback関数を実行する。
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_LightweightRTObject_finalize(
  impl_POA_RTC_LightweightRTObject *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  impl_POA_RTC_RTObject *rtobj_servant;
  CORBA_RTC_ComponentAction caobj_ref;   

  rtobj_servant = (impl_POA_RTC_RTObject *)servant;
  caobj_ref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev); 

  /* Delete Port (disconnect) */

  /* Stop EC (call [RTC_ExecutionContext_stop()]) */
  retval = RTC_ExecutionContext_stop(rtobj_servant->m_ecRef, ev);
  ExecutionContext_deleteStateMachine(rtobj_servant->m_ecRef);

  /* Finalize RTC [call RTC_ComponentAction_on_finalize()] */
  clearEnvironment(ev);
  retval = RTC_ComponentAction_on_finalize(caobj_ref, ev);

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCの終了処理。内部で、RTCをINACTIVE状態に遷移させた後、[finalize()]をcallし、詳細な終了処理を行う。 
 *
 *        RTCを終了させる場合の外部からの通知は、このオペレーションを呼ぶことになる。[RtSystemEditor]では[Exit]を選択した場合にcallされる。
 *
 *        (1) 現在RTCがACTIVE状態にあれば、[RTC_ExecutionContext_deactivate_component()]をcallし、強制的にINACTIVE状態に遷移させる。ECのWorker経由で実際に[RTC_ComponentAction_on_deactivated]がcallされるまでには、タイムラグがあるため、状態が[ACTIVE]以外に遷移するまで、whileループでwaitする。<BR>
 *        (2) [RTC_LightweightRTObject_finalize()]をcallし、RTCの詳細な終了処理を行う。<BR>
 *        (3) [RTC_Manager_unregisterComponent()]をcallして、NameServerから、登録済みのRTCを解除する。<BR>
 *        (4) (T.B.D) RTObjectの削除を行う。<BR>
 *        (5) (T.B.D) Managerの削除を行う。<BR> 
 *        (6) [CORBA_ORB_shutdown()][CORBA_ORB_destroy()]をcallして、CORBA_ORBを終了する。
 * \return RTC_ReturnCode_t型リターンコード。(成功:[RTC_RTC_OK]/失敗:[RTC_RTC_ERROR])
 */
RTC_ReturnCode_t
impl_RTC_LightweightRTObject_exit(
  impl_POA_RTC_LightweightRTObject *servant,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  CORBA_RTC_LightweightRTObject lwobj_ref;
  CORBA_RTC_ExecutionContextService ecs_ref;
  CORBA_RTC_RTObject rtobj_ref; 
  impl_POA_RTC_RTObject *rtobj_servant;
  impl_POA_RTC_ExecutionContextService *ecs_servant;
  RTComp *rtcomp;

  lwobj_ref = PortableServer_POA_servant_to_reference(servant->poa, servant, ev);  
  rtobj_servant = (impl_POA_RTC_RTObject *)servant;
  rtobj_ref = PortableServer_POA_servant_to_reference(rtobj_servant->poa, rtobj_servant, ev); 
  ecs_ref = rtobj_servant->m_ecRef;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)ecs_ref->servant;
  rtcomp = (RTComp*)rtobj_ref->impl_obj;

  /* Deactivate RTC and call on_deactivated() if state is [ACTIVE]. */
  if (ecs_servant->m_states->curr == RTC_ACTIVE_STATE) {
    RTC_ExecutionContext_deactivate_component(ecs_ref, lwobj_ref, ev);
    /* Wait for end of action by Worker. */
    fprintf(stderr, "Now wait for completion of on_deactivated() action...   ");
    while (ecs_servant->m_states->curr == RTC_ACTIVE_STATE) continue;  
    fprintf(stderr, " Done.\n");
  }

  /* Finalize RTC [call RTC_LightweightRTObject_finalize()] */
  clearEnvironment(ev);
  retval = RTC_LightweightRTObject_finalize(lwobj_ref, ev);  

  /* Unbind RTC from NameServer */ 
  RTC_Manager_unregisterComponent(rtcomp->m_manager, rtobj_ref);

  /* Delete RTObject */
  /* Delete Manager */

  /* Exit CORBA_ORB */
  CORBA_ORB_shutdown(The_ORB, 1, ev);
  CORBA_ORB_destroy(The_ORB, ev);

#if 1
  fprintf(stderr, "[Exit] is done.\n");
#endif
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCに対して、ECは１つを想定(1対1)しているので、唯一起動されているECのIDを返す。 
 * 
 *        RTCに対して、ECは１つ(Owner)を想定しており、ECのIDも固定として、["0"]を返す。<BR>
 *        なお、[ec_id]は、[owned context]ならば、[0]固定で、[participating context]ならば、[1/2/3/...]と"1"以上の整数が割り当てられる仕様である。<BR>
 *        当関数は、[RtSystemEditor]にて、RTC起動後に周期的にcallされる。
 * \return RTC_ExecutionContextHandle_t型データ[ECのID] ("0"で固定とする)
 */
RTC_ExecutionContextHandle_t
impl_RTC_LightweightRTObject_get_context_handle(
  impl_POA_RTC_LightweightRTObject *servant,
  RTC_ExecutionContext cxt,
  CORBA_Environment *ev)
{
  RTC_ExecutionContextHandle_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = 0;  /* Only Owner context's [EC_ID] */

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCに対して、ECは１つを想定(1対1)しているので、唯一起動されているEC情報を返す。 <BR>
 *        当関数は、[RtSystemEditor]にて、RTC起動後に周期的にcallされる。
 * \return 唯一起動されているEC情報(RTC_ExecutionContext型オブジェクト)
 */
RTC_ExecutionContextList*
impl_RTC_LightweightRTObject_get_owned_contexts(
  impl_POA_RTC_LightweightRTObject *servant,
  CORBA_Environment *ev)
{
  RTC_ExecutionContextList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_ExecutionContextList__alloc();
  RTObject_get_owned_contexts(servant, retval);
 
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief RTCに対して、ECは１つを想定(1対1)しているので、唯一起動されているEC情報を返す。 <BR>
 *        当関数は、[RtSystemEditor]にて、RTC起動後に周期的にcallされる。
 * \return 唯一起動されているEC情報(RTC_ExecutionContext型オブジェクト)
 */
RTC_ExecutionContextList*
impl_RTC_LightweightRTObject_get_participating_contexts(
  impl_POA_RTC_LightweightRTObject *servant,
  CORBA_Environment *ev)
{
  RTC_ExecutionContextList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval = RTC_ExecutionContextList__alloc();
  RTObject_get_participating_contexts(servant, retval);

    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*
 RTCオブジェクトとExecutionContextは1対1対応とするため、この処理は不要として未実装。
*/
RTC_ExecutionContextHandle_t
impl_RTC_LightweightRTObject_attach_context(
  impl_POA_RTC_LightweightRTObject *servant,
  RTC_ExecutionContext exec_context,
  CORBA_Environment *ev)
{
  RTC_ExecutionContextHandle_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*
 RTCオブジェクトとExecutionContextは1対1対応とするため、この処理は不要として未実装。
*/
RTC_ReturnCode_t
impl_RTC_LightweightRTObject_detach_context(
  impl_POA_RTC_LightweightRTObject *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ReturnCode_t retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_RTC_LightweightRTObject_is_alive(
  impl_POA_RTC_LightweightRTObject *servant,
  RTC_ExecutionContext exec_context,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ExecutionContext
impl_RTC_LightweightRTObject_get_context(
  impl_POA_RTC_LightweightRTObject *servant,
  RTC_ExecutionContextHandle_t exec_handle,
  CORBA_Environment *ev)
{
  RTC_ExecutionContext retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}


/**********************************************************************************/
/* Caution : Comment out unused functions by "#if 0". 
 * Ref : [OpenRTM-aist.h :: #define RTC_LightweightRTObject_Func RTC_ComponentAction_Func ]  
 */
/**********************************************************************************/

#if 0

RTC_ReturnCode_t
impl_RTC_LightweightRTObject_on_initialize(
    impl_POA_RTC_LightweightRTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_LightweightRTObject_on_finalize(
    impl_POA_RTC_LightweightRTObject *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  RTC_ReturnCode_t retval;
    /* ------   insert method code here  (6) ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

RTC_ReturnCode_t
impl_RTC_LightweightRTObject_on_startup(
    impl_POA_RTC_LightweightRTObject *servant,
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
impl_RTC_LightweightRTObject_on_shutdown(
    impl_POA_RTC_LightweightRTObject *servant,
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
impl_RTC_LightweightRTObject_on_activated(
    impl_POA_RTC_LightweightRTObject *servant,
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
impl_RTC_LightweightRTObject_on_deactivated(
    impl_POA_RTC_LightweightRTObject *servant,
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
impl_RTC_LightweightRTObject_on_aborting(
    impl_POA_RTC_LightweightRTObject *servant,
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
impl_RTC_LightweightRTObject_on_error(
    impl_POA_RTC_LightweightRTObject *servant,
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
impl_RTC_LightweightRTObject_on_reset(
    impl_POA_RTC_LightweightRTObject *servant,
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

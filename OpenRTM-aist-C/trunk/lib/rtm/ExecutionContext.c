/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file ExecutionContext.c
 * \brief Execution Context 全般の処理。主にStateMachine(状態遷移)を[worker]が別スレッドで担当する機能の実装。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/OpenRTM.h>

/*!
  \def STATES_NUM
       ExecutionContextが扱う[State(LifeCycleState)]の数
*/
#define STATES_NUM (4)

/*********************** [ Prototype (static) ] ******************************/
static void ExecutionContext_transitState(CORBA_RTC_ExecutionContextService obj, RTC_LifeCycleState state);
static void invoke_on_activated(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
static void invoke_on_deactivated(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
static void invoke_on_aborting(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev); 
static void invoke_on_error(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
static void invoke_on_reset(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
static void invoke_on_execute(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
static void invoke_on_state_update(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);

/*****************************************************************************/
/**************************** [ Functions ] **********************************/
/*****************************************************************************/

/*!
 * \brief (中身は未実装) RTC_Manager_initExecContext()からcallされるが、何もしない。
 */
void
RTC_PeriodicExecutionContextInit(RTC_Manager *mgr)
{
  return;
}


/*!
 * \brief (中身は未実装) RTC_Manager_initExecContext()からcallされるが、何もしない。
 */
void
RTC_ExtTrigExecutionContextInit(RTC_Manager *mgr)
{
  return;
}


/*!
 * \brief (中身は未実装) RTC_Manager_initExecContext()からcallされるが、何もしない。
 */
void
RTC_OpenHRPExecutionContextInit(RTC_Manager *mgr)
{
  return;
}


/*!
 * \brief (中身は未実装) RTC_Manager_initComposite()からcallされるが、何もしない。
 */
void
RTC_PeriodicECSharedCompositeInit(RTC_Manager *mgr)
{
  return;
}

/* ======================================================================== */

/* 
 Create Thread and bind to ExecutionContextService.
 Called from [impl_RTC_LightweightRTObject_initialize()].
*/
int ExecutionContext_createThread(CORBA_RTC_ExecutionContextService obj)
{
  pthread_t thr;

  /* Create Thread, and set worker for StateMachine. */
  if (pthread_create(&thr, NULL, ExecutionContext_StateMachineWorker, (void*)obj)) {
    fprintf(stderr, " [ERROR] Can't create THERAD for EC.\n");
    return 0;
  } else {
    pthread_detach(thr);
  }

  return 1;
}


/*
 Set RTObject object and ExecutionContext object each other.
 Called from [impl_RTC_LightweightRTObject_initialize()].
*/
int ExecutionContext_bindObject(CORBA_RTC_ExecutionContextService ec_obj, CORBA_RTC_RTObject rt_obj)
{
  impl_POA_RTC_ExecutionContextService *ecs_servant = (impl_POA_RTC_ExecutionContextService *)ec_obj->servant;
  impl_POA_RTC_RTObject* rtobj_servant = (impl_POA_RTC_RTObject *)rt_obj->servant;

  /* Set RTObject object */
  ecs_servant->m_ecProfile.owner = rt_obj; 

  /* Set ExecutionContextService object */
  rtobj_servant->m_ecRef = ec_obj;

  return 1; 
}


/*
 Initialize StateMachine parameters. State is [INACTIVE].
 Called from [impl_RTC_LightweightRTObject_initialize()].
*/
void ExecutionContext_initStateMachine(CORBA_RTC_ExecutionContextService obj)
{
  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)obj->servant;

  /* Initialize State data (LifeCycleData) */
  ecs_servant->m_states = (EC_State *)calloc(1, sizeof(EC_State));
  ecs_servant->m_states->curr = RTC_INACTIVE_STATE;
  ecs_servant->m_states->prev = RTC_INACTIVE_STATE;
  ecs_servant->m_states->next = RTC_INACTIVE_STATE;

  /* Initialize Callback functions pointer */
  ecs_servant->m_callback = (EC_Callback *)calloc(1, (sizeof(EC_Callback) * STATES_NUM) );
    /* CREATED state (Unused) */
  ecs_servant->m_callback[RTC_CREATED_STATE].entry_func = NULL;
  ecs_servant->m_callback[RTC_CREATED_STATE].predo_func = NULL;
  ecs_servant->m_callback[RTC_CREATED_STATE].do_func = NULL;
  ecs_servant->m_callback[RTC_CREATED_STATE].postdo_func = NULL;
  ecs_servant->m_callback[RTC_CREATED_STATE].exit_func = NULL;
    /* INACTIVE state */
  ecs_servant->m_callback[RTC_INACTIVE_STATE].entry_func = NULL;
  ecs_servant->m_callback[RTC_INACTIVE_STATE].predo_func = NULL;
  ecs_servant->m_callback[RTC_INACTIVE_STATE].do_func = NULL;
  ecs_servant->m_callback[RTC_INACTIVE_STATE].postdo_func = NULL;
  ecs_servant->m_callback[RTC_INACTIVE_STATE].exit_func = NULL;
    /* ACTIVE state */
  ecs_servant->m_callback[RTC_ACTIVE_STATE].entry_func = invoke_on_activated;
  ecs_servant->m_callback[RTC_ACTIVE_STATE].predo_func = NULL;
  ecs_servant->m_callback[RTC_ACTIVE_STATE].do_func = invoke_on_execute;
  ecs_servant->m_callback[RTC_ACTIVE_STATE].postdo_func = invoke_on_state_update;
  ecs_servant->m_callback[RTC_ACTIVE_STATE].exit_func = invoke_on_deactivated;
    /* ERROR state */
  ecs_servant->m_callback[RTC_ERROR_STATE].entry_func = invoke_on_aborting;
  ecs_servant->m_callback[RTC_ERROR_STATE].predo_func = NULL;
  ecs_servant->m_callback[RTC_ERROR_STATE].do_func = invoke_on_error;
  ecs_servant->m_callback[RTC_ERROR_STATE].postdo_func = NULL;
  ecs_servant->m_callback[RTC_ERROR_STATE].exit_func = invoke_on_reset;

  return;
}


/*
 Delete StateMachine parameters. 
 Called from [impl_RTC_LightweightRTObject_finalize()].
*/
void ExecutionContext_deleteStateMachine(CORBA_RTC_ExecutionContextService obj)
{
  int i;
  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)obj->servant;

  /* State */
  free(ecs_servant->m_states);
  ecs_servant->m_states = NULL;

  /* Callback */
  for(i = 0; i < STATES_NUM; i++) {
    ecs_servant->m_callback[i].entry_func = NULL;
    ecs_servant->m_callback[i].predo_func = NULL;
    ecs_servant->m_callback[i].do_func = NULL;
    ecs_servant->m_callback[i].postdo_func = NULL;
    ecs_servant->m_callback[i].exit_func = NULL;
  }
  free(ecs_servant->m_callback);
  ecs_servant->m_callback = NULL;

  return;
}


/*
 StateMachines worker.
 Called from [ExecutionContext_createThread()].
*/
void* ExecutionContext_StateMachineWorker(void *arg)
{
  CORBA_Environment ev; 
  CORBA_RTC_ExecutionContextService ecs_obj;
  impl_POA_RTC_ExecutionContextService *ecs_servant;
  CORBA_RTC_RTObject rtobj;
  EC_State state;
  RTC_ExecutionContextHandle_t ec_id = 0; /* Only Owner context's [EC_ID] (fixed value) */
  unsigned int sleep_time;

  memset (&ev, 0, sizeof (CORBA_Environment));

  ecs_obj = (CORBA_RTC_ExecutionContextService)arg;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)ecs_obj->servant;
  rtobj = ecs_servant->m_ecProfile.owner; 

  while (ecs_obj != CORBA_OBJECT_NIL) {
    if ( (ecs_servant->m_states == NULL) || (ecs_servant->m_callback == NULL) ) break;

    /* Check that EC is started or stopped. (Started => [m_running : true]) */
    if (ecs_servant->m_running) {
      /* Copy state */
      state.curr = ecs_servant->m_states->curr;
      state.next = ecs_servant->m_states->next;
      state.prev = ecs_servant->m_states->prev;

      /* Periodic actions (CurrentState == NextState) */
      if (state.curr == state.next) {
        /* [PreDo] action */
        if (ecs_servant->m_callback[state.curr].predo_func != NULL) {
          clearEnvironment(&ev);
          ecs_servant->m_callback[state.curr].predo_func(rtobj, ec_id, &ev);
        } 
    
        if (ecs_servant->m_states->curr == ecs_servant->m_states->next) { /* If State changed...*/
          /* [Do] action */
          if (ecs_servant->m_callback[state.curr].do_func != NULL) {
            clearEnvironment(&ev);
            ecs_servant->m_callback[state.curr].do_func(rtobj, ec_id, &ev);
          } 

          if (ecs_servant->m_states->curr == ecs_servant->m_states->next) { /* If State changed...*/
            /* [PostDo] action */
            if (ecs_servant->m_callback[state.curr].postdo_func != NULL) {
              clearEnvironment(&ev);
              ecs_servant->m_callback[state.curr].postdo_func(rtobj, ec_id, &ev);
            } 
          }
        }

        /* Change previous status */
        if (ecs_servant->m_states->prev != ecs_servant->m_states->curr) {
          ecs_servant->m_states->prev = ecs_servant->m_states->curr;
        }

      /* State Transit actions (CurrentState != NextState) */
      } else {
        /* [Exit] action */
        if (ecs_servant->m_callback[state.curr].exit_func != NULL) {
          clearEnvironment(&ev);
          ecs_servant->m_callback[state.curr].exit_func(rtobj, ec_id, &ev);
        } 

        /* [Entry] action */
        if (ecs_servant->m_callback[state.next].entry_func != NULL) {
          clearEnvironment(&ev);
          ecs_servant->m_callback[state.next].entry_func(rtobj, ec_id, &ev);
        } 

        /* Change current status */
        ecs_servant->m_states->prev = ecs_servant->m_states->curr;
        ecs_servant->m_states->curr = ecs_servant->m_states->next;
      }

      /* Sleep */
      //TODO: 設定された周期に応じて、残時間をsleepするように変更する。
      sleep_time = (unsigned int)(100000/ecs_servant->m_ecProfile.rate); /* (1/rate)*(10e6) */
      usleep(sleep_time);

    } /* end of if (m_running) */
  } /* end of While */

  return;
}


/*****************************************************************************/
/********************* [ static functions ] **********************************/
/*****************************************************************************/

/*
 Transit RTC's next state.
 Called from [invoke_on_activated(), invoke_on_deactivated(), 
              invoke_on_reset(), invoke_on_execute(), invoke_on_state_update()].
*/
/*!
 * \brief RTCの状態を遷移させる(次の状態値を変更する)。(主に、[ERROR状態]に遷移させる時に使用している。)
 * \param obj RTC_ExecutionContextServiceオブジェクト
 * \param state 遷移後のRTCの状態(LifeCycleStateデータ)
 * \return void:
 */
static void ExecutionContext_transitState(CORBA_RTC_ExecutionContextService obj, RTC_LifeCycleState state)
{
  impl_POA_RTC_ExecutionContextService *ecs_servant;
  ecs_servant = (impl_POA_RTC_ExecutionContextService *)obj->servant;

  ecs_servant->m_states->next = state;

  return;
}


/*!
 * \brief [RTC_ComponentAction_on_activated()]関数をcallする。返り値が正常値で無ければ、RTCをエラー状態に遷移させる。
 */
static void invoke_on_activated(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{
  impl_POA_RTC_RTObject *rtobj_servant;
  rtobj_servant = (impl_POA_RTC_RTObject*)obj->servant;

  if (RTC_ComponentAction_on_activated(obj, id, ev) != RTC_RTC_OK) {
    ExecutionContext_transitState(rtobj_servant->m_ecRef, RTC_ERROR_STATE);
  }
  return;
}


/*!
 * \brief [RTC_ComponentAction_on_deactivated()]関数をcallする。返り値が正常値で無ければ、RTCをエラー状態に遷移させる。
 */
static void invoke_on_deactivated(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{
  impl_POA_RTC_RTObject *rtobj_servant;
  rtobj_servant = (impl_POA_RTC_RTObject*)obj->servant;

  if (RTC_ComponentAction_on_deactivated(obj, id, ev) != RTC_RTC_OK) {
    ExecutionContext_transitState(rtobj_servant->m_ecRef, RTC_ERROR_STATE);
  }
  return;
}


/*!
 * \brief [RTC_ComponentAction_on_aborting()]関数をcallする。
 */
static void invoke_on_aborting(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{

  RTC_ComponentAction_on_aborting(obj, id, ev);
  return;
}


/*!
 * \brief [RTC_ComponentAction_on_error()]関数をcallする。
 */
static void invoke_on_error(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{

  RTC_ComponentAction_on_error(obj, id, ev);
  return;
}


/*!
 * \brief [RTC_ComponentAction_on_reset()]関数をcallする。返り値が正常値で無ければ、RTCをエラー状態に遷移させる。
 */
static void invoke_on_reset(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{
  impl_POA_RTC_RTObject *rtobj_servant;
  rtobj_servant = (impl_POA_RTC_RTObject*)obj->servant;

  if (RTC_ComponentAction_on_reset(obj, id, ev) != RTC_RTC_OK) {
    ExecutionContext_transitState(rtobj_servant->m_ecRef, RTC_ERROR_STATE);
  }
  return;
}


/*!
 * \brief [RTC_DataFlowComponentAction_on_execute()]関数をcallする。返り値が正常値で無ければ、RTCをエラー状態に遷移させる。
 */
static void invoke_on_execute(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{
  RTC_DataFlowComponentAction dfc_obj;
  impl_POA_RTC_RTObject *rtobj_servant;
  rtobj_servant = (impl_POA_RTC_RTObject*)obj->servant;
  dfc_obj = rtobj_servant->m_dfcompRef;

  if (RTC_DataFlowComponentAction_on_execute(dfc_obj, id, ev) != RTC_RTC_OK) {
    ExecutionContext_transitState(rtobj_servant->m_ecRef, RTC_ERROR_STATE);
  }
  return;
}


/*!
 * \brief [RTC_DataFlowComponentAction_on_state_update()]関数をcallする。返り値が正常値で無ければ、RTCをエラー状態に遷移させる。
 */
static void invoke_on_state_update(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev) 
{
  RTC_DataFlowComponentAction dfc_obj;
  impl_POA_RTC_RTObject *rtobj_servant;
  rtobj_servant = (impl_POA_RTC_RTObject*)obj->servant;
  dfc_obj = rtobj_servant->m_dfcompRef;

  if (RTC_DataFlowComponentAction_on_state_update(dfc_obj, id, ev) != RTC_RTC_OK) {
    ExecutionContext_transitState(rtobj_servant->m_ecRef, RTC_ERROR_STATE);
  }
  return;
}

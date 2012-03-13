/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file ExecutionContext.h
 * \brief Execution Context 全般の処理。主にStateMachine(状態遷移)を[worker]が別スレッドで担当する機能の実装。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
#ifndef EXECUTIONCONTEXT_H
#define EXECUTIONCONTEXT_H

#include <rtm/OpenRTM-aist.h>
#include <pthread.h>   

/*!
 * \struct State_struct
 * \brief 現在のRTCの状態を表すRTC_LifeCycleState型enumデータ(CREATED/INACTIVE/ACTIVE/ERROR)。
 *
 *        RTCはECにより、周期的に決められたActivityを内部処理として行うが、この[状態]により、実行する処理が異なる。<BR>
 *        状態は外部からの指令により変更が行われるが、指令がなければ現在の[状態]をキープする。その際、定義されたActivityを実行し続けることになる。<BR>
 *        ３つのパラメータの内、主に、状態の変更が行われた時に、[next]の値が変更されるため、[curr]と[next]で値が異なり、これをトリガとして、状態遷移時のActivityが実行されることになる。<BR>
 *        (*)なお、現在は、[CREATED]状態は使用しないことにする。<BR>
 *        (*)現状、[OpenRTM-aist-C++-1.0.0]の仕様に合わせたものにしている。
 * \param curr 現在の状態
 * \param prev 前回の状態
 * \param next 次回の状態
 */
typedef struct State_struct
{
  /* <enum>[RTC_CREATED_STATE/RTC_INACTIVE_STATE/RTC_ACTIVE_STATE/RTC_ERROR_STATE] */
  RTC_LifeCycleState curr;
  RTC_LifeCycleState prev;
  RTC_LifeCycleState next;
}EC_State;

/*!
 * \struct Callback_struct
 * \brief RTCがいずれかの状態にある時のAction用の関数ポインタ群データ(entry/predo/do/postdo/exit)。
 *
 *        (1)[entry]は、RTCがある状態に遷移した最初の1回だけ実行されるActionである。<BR>
 *        (2)[predo/do/postdo]は、RTCがその状態をキープしている間中、実行され続けるActionである。<BR>
 *        (3)[exit]は、RTCがある状態へ遷移する前に、最後に1回だけ実行されるActionである。<BR>
 *        (*)全ての状態に対して、上記のActionを割り当てる必要はなく、代わりに[NULL]ポインタを割り当てることで、何も処理しないことも可能である。<BR>
 *        (*)現状、[OpenRTM-aist-C++-1.0.0]の仕様に合わせたものにしている。
 * \param entry_func ある状態に入る時に、最初に実行されるAction用ポインタ
 * \param predo_func ある状態に居る間中、周期的に実行(1番目)されるAction用ポインタ
 * \param do_func ある状態に居る間中、周期的に実行(2番目)されるAction用ポインタ
 * \param postdo_func ある状態に居る間中、周期的に実行(3番目)されるAction用ポインタ
 * \param exit_func ある状態から抜ける前に、最後に実行されるAction用ポインタ
 */
typedef struct Callback_struct
{
  /* Calback function pointer (entry/predo/do/postdo/exit) */
  void (*entry_func)(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
  void (*predo_func)(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
  void (*do_func)(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
  void (*postdo_func)(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
  void (*exit_func)(RTC_RTObject obj, RTC_ExecutionContextHandle_t id, CORBA_Environment *ev);
}EC_Callback;

/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/*!
 * \brief EC用のスレッドを生成しセットする。(pthread使用)
 * \param obj RTC_ExecutionContextServiceオブジェクト
 * \return 成功:"1"/失敗:"0"
 */
int ExecutionContext_createThread(CORBA_RTC_ExecutionContextService obj);

/*!
 * \brief 関連するRTObject/ExecutionContextServiceの各CORBAオブジェクトリファレンスを相互セットする。
 *
 *        (1) RTC_ExecutionContextServiceオブジェクトの[servant]内の要素[ExecutionContextProfileの成分"owner"(RTC_RTObjectのオブジェクトリファレンス)]に、引数[rt_obj]をセット。<BR>
 *        (2) RTC_RTObjectオブジェクトの[servant]内の要素[m_ecRef(RTC_ExecutionContextServiceのオブジェクトリファレンス)]に、引数[ec_obj]をセット。
 * \param ec_obj RTC_ExecutionContextServiceオブジェクト
 * \param rt_obj RTC_RTObjectオブジェクト
 * \return 固定値["1"]
 */
int ExecutionContext_bindObject(CORBA_RTC_ExecutionContextService ec_obj, CORBA_RTC_RTObject rt_obj);

/*!
 * \brief RTCの状態遷移を管理するECのStateMachineデータの生成と初期値のセットを行う。
 *
 *        <State(LifeCycleData)>について <BR>
 *           生成時は、[curr/prev/next]それぞれの状態を[INACTIVE]とする。
 *
 *        <Callback関数>について <BR>
 *           RTCの各状態に応じて、割り当てるActivity用の関数ポインタをセットしている。<BR>
 *             - [CREATED/INACTIVE状態]  <BR>
 *                -# {entry関数}  :無し  <BR>
 *                -# {predo関数}  :無し  <BR>
 *                -# {do関数}     :無し  <BR>
 *                -# {postdo関数} :無し  <BR>
 *                -# {exit関数}   :無し  <BR>
 *             - [ACTIVE状態]  <BR>
 *                -# {entry関数}  :on_activated()  <BR>
 *                -# {predo関数}  :無し  <BR>
 *                -# {do関数}     :on_execute()  <BR>
 *                -# {postdo関数} :on_state_update()  <BR>
 *                -# {exit関数}   :on_deactivated()  <BR>
 *             - [ERROR状態]  <BR>
 *                -# {entry関数}  :on_aborting()  <BR>
 *                -# {predo関数}  :無し  <BR>
 *                -# {do関数}     :on_error()  <BR>
 *                -# {postdo関数} :無し  <BR>
 *                -# {exit関数}   :on_reset()  <BR>
 *           (*)現状、[OpenRTM-aist-C++-1.0.0]の仕様に合わせたものにしている。
 * \param obj RTC_ExecutionContextServiceオブジェクト
 * \return void:
 */
void ExecutionContext_initStateMachine(CORBA_RTC_ExecutionContextService obj);

/*!
 * \brief RTCの状態遷移を管理するECのStateMachineデータの削除を行う。
 * \param obj RTC_ExecutionContextServiceオブジェクト
 * \return void:
 */
void ExecutionContext_deleteStateMachine(CORBA_RTC_ExecutionContextService obj);

/*!
 * \brief RTCの状態遷移を管理するECのStateMachineの駆動関数。実際の状態遷移および状態遷移発生時の各アクションの呼びだしを実行する。(通常、別スレッドで実行される)
 *
 *        (1)まず、ECの対象となる[CORBA_RTC_ExecutionContextService]型オブジェクトが存在しているか確認する。さらに、必須パラメータの[m_states(RTCの状態)][m_callback(Activity用関数群)]が存在するか確認する。最後に、ECの起動/停止フラグの[m_running]をチェックし、起動中(start()関数により起動されている)であれば、以降の処理を行う。<BR>
 *        (2)現在の[m_states(RTCの状態)]を別パラメータ[state]に退避する。<BR>
 *        (3)現在[curr]と次[next]の状態を比較し、一致するかどうかで、状態遷移の有無を判断する。<BR>
 *        (4-1)<状態遷移なし>各RTCの状態に応じて、割り当てられた周期的Activityを[invoke_???()]関数経由でcallする。この時、実行中に状態遷移が無いかを確認し、あれば即座に処理を中断する。<BR>
 *        (4-2)<状態遷移あり>状態遷移前の最後のActivity(exit)を実行し、その後、状態遷移後のentry用のActivityを実行する。現在の状態[curr]に遷移後の状態[next]の値をセットする。<BR>
 *        (5)設定されたECのrateに従い、1周期の残時間をsleepする。<BR>
 *        (6)whileループで(2)-(5)の処理を繰り返す。
 * \param arg RTC_ExecutionContextServiceオブジェクトが入ることになる。
 * \return voidポインタ:
 */
void* ExecutionContext_StateMachineWorker(void *arg);

#endif // EXECUTIONCONTEXT_H

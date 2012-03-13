/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file RTComp.h
 * \brief ユーザ生成RTCの雛形となる構造体。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTCOMP_H
#define RTCOMP_H


typedef RTC_ExecutionContextHandle_t RTC_UniqueId; /* long */

/*!
 * \struct RTComponent_Object
 * \brief ユーザ生成RTCの雛形となる構造体。RTC生成時には、create()にて、
 *        この構造体の変数をメモリ確保して、中身のポインタのセットを行う。
 *        唯一のCORBAオブジェクト、メンバ変数群、状態遷移のCallback関数群が
 *        用意されており、これらをユーザ側でセットすることになる。
 * \param m_rtobjRef CORBA_RTC_RTObject型のCORBAオブジェクトのポインタ
 * \param onInitialize ユーザRTCのActivity用callback関数
 * \param onFinalize ユーザRTCのActivity用callback関数
 * \param onStartup ユーザRTCのActivity用callback関数
 * \param onShutdown ユーザRTCのActivity用callback関数
 * \param onActivated ユーザRTCのActivity用callback関数
 * \param onDeactivated ユーザRTCのActivity用callback関数
 * \param onExecute ユーザRTCのActivity用callback関数
 * \param onError ユーザRTCのActivity用callback関数
 * \param onReset ユーザRTCのActivity用callback関数
 * \param onStateUpDate ユーザRTCのActivity用callback関数
 * \param onRateChanged ユーザRTCのActivity用callback関数
 * \param m_private ユーザ生成のRTCの[.h]にて定義する、Member変数用構造体のセット用ポインタ
 * \param m_manager 自RTCを管理しているManagerへのポインタ(unregisterComponent()処理で使用)
 */
typedef struct RTComponent_Object
{
  /* Object Reference of "RtcBase" */
  CORBA_RTC_RTObject  m_rtobjRef;

  /* Function pointers of RTC activity (ComponentAction/DataFlowComponentAction) */
  RTC_ReturnCode_t (*onInitialize)(struct RTComponent_Object * obj);

  RTC_ReturnCode_t (*onFinalize)(struct RTComponent_Object * obj);

  RTC_ReturnCode_t (*onStartup)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onShutdown)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onActivated)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onDeactivated)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onExecute)(struct RTComponent_Object *obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onAborting)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onError)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onReset)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);
 
  RTC_ReturnCode_t (*onStateUpDate)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  RTC_ReturnCode_t (*onRateChanged)(struct RTComponent_Object * obj, RTC_UniqueId ec_id);

  /* Linked to "UserRTC_Member" structure */
  void *m_private;  
  
#if 1 
  /* RTC_Manager pointer */
  struct RTC_Manager_struct *m_manager;
#endif

} RTComp;

#endif // RTCOMP_H

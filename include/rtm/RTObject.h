/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file RTObject.h
 * \brief RTCの基底となるRTObjectに関する関数群のファイル。主に、RTObjectの生成、コンフィグレーション情報の取得、DataPortを使用した操作などの目的で使用される。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_RTOBJECT_H
#define RTM_RTOBJECT_H

#include <rtm/OpenRTM-aist.h>
#include <rtm/OpenRTM-aist-decls.h>
#include <rtm/OpenRTM-aist-skelimpl.h>
#include <rtm/Manager.h>

/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/*!
 * \brief RTC_RTObjectオブジェクトを生成する。
 * \param manager RTCを管理しているManagerのポインタ
 * \return 生成されたRTC_RTObjectオブジェクト
 */
CORBA_RTC_RTObject RTC_DataFlowComponentBase_create(RTC_Manager *manager);

/*!
 * \brief OutPortオブジェクトを生成する。内部で[Port_createPort()]をcallするのみ。
 * \param rtobj DataPortを保持する親のRTC_RTObjectオブジェクト
 * \param port_name 生成するOutPortの名前
 * \param type_name 生成するOutPortで扱うデータのデータ型名称(モジュール名_変数名の必要あり。例として、[RTC_TimedLong]など)
 * \return 生成されたOutPortの情報を管理する[RTC_OutPort]型データのポインタ
 */
RTC_OutPort* RTC_OutPort_create(CORBA_RTC_RTObject rtobj, const char *port_name, const char *type_name);

/*!
 * \brief InPortオブジェクトを生成する。内部で[Port_createPort()]をcallするのみ。
 * \param rtobj DataPortを保持する親のRTC_RTObjectオブジェクト
 * \param port_name 生成するInPortの名前
 * \param type_name 生成するInPortで扱うデータのデータ型名称(モジュール名_変数名の必要あり。例として、[RTC_TimedLong]など)
 * \return 生成されたInPortの情報を管理する[RTC_InPort]型データのポインタ
 */
RTC_InPort* RTC_InPort_create(CORBA_RTC_RTObject rtobj, const char *port_name, const char *type_name);

/*!
 * \brief OutPortにて、扱うデータの型が可変長(sequence型)の場合に、その長さを指定(メモリの確保)する。Portが生成されていれば、RTCがどの状態遷移にいても指定可能である。なお、サイズ「0」を指定すれば、既に確保したメモリを解放する。内部で[Port_setSequenceLength()]をcallするのみ。
 * \param out_port 生成済みのOutPortの情報を管理する[RTC_OutPort]型データのポインタ
 * \param length 扱うデータの可変長サイズ指定用の長さ("0"を指定すれば、既に確保したメモリ解放)
 * \param val 可変長(sequence型)で定義された変数自体(sequence型/struct型が入れ子になり深い階層の場合にも、全てを記述)
 * \param val_name 可変長(sequence型)で定義された変数の名前("data" or "parent.child.data")
 * \return 成功:[1], 失敗[-1]
 */
int RTC_OutPort_setSeqLength(RTC_OutPort *out_port, CORBA_unsigned_long length, void* val, const char* val_name);

/*!
 * \brief データの型が可変長(sequence型)のOutPortにおいて、その長さを取得する。内部で[Port_getSequenceLength()]をcallするのみ。
 * \param out_port 生成済みのOutPortの情報を管理する[RTC_OutPort]型データのポインタ
 * \param val 可変長(sequence型)で定義された変数自体(sequence型/struct型が入れ子になり深い階層の場合にも、全てを記述)
 * \param val_name 可変長(sequence型)で定義された変数の名前("data" or "parent.child.data")
 * \return 成功:[現在の可変長(sequence型)の長さ], 失敗:[-1]
 */
uint32_t RTC_OutPort_getSeqLength(RTC_OutPort *out_port, void* val, const char* val_name);

/*!
 * \brief データの型が可変長(sequence型)のInPortにおいて、その長さを取得する。内部で[Port_getSequenceLength()]をcallするのみ。
 * \param in_port 生成済みのInPortの情報を管理する[RTC_InPort]型データのポインタ
 * \param val 可変長(sequence型)で定義された変数自体(sequence型/struct型が入れ子になり深い階層の場合にも、全てを記述)
 * \param val_name 可変長(sequence型)で定義された変数の名前("data" or "parent.child.data")
 * \return 成功:[現在の可変長(sequence型)の長さ], 失敗:[-1]
 */
uint32_t RTC_InPort_getSeqLength(RTC_InPort *in_port, void* val, const char* val_name);

/*!
 * \brief 自InPortにOutPort側からデータが送信されたかをチェックする。新規データがあれば、[1]を、無ければ[-1]を返す。
 *
 * 内部では、[OpenRTM_InPortCdr]servantが持つ[m_isNew]をチェックし、[1]であれば、新規データありと判断し、[m_isNew]を[0]に変更する。<BR>
 * また、OutPortに未接続の状態で当関数をcallした場合[-1]を返す。
 * \param in_port データ取得対象となるInPortの情報を管理する[RTC_InPort]型データのポインタ
 * \return 新規データあり:[1]/なし[-1]、未接続状態:[-1]
 */
int RTC_InPort_isNew(RTC_InPort* in_port);

/*!
 * \brief 既にInPortのバッファに保持された、OutPort側からのデータを読み込む。
 *
 * (1)[Port_UnMarshal_by_TypeCode()]をcallし、受信したCDR形式のデータをアンマーシャルする。<BR>
 * (2)アンマーシャル後のデータを[in_port]内の[m_value]にセットする。<BR>
 * (3)アンマーシャル前のバッファ領域を解放する。
 * \param in_port データ取得対象となるInPortの情報を管理する[RTC_InPort]型データのポインタ
 * \return データ取得成功:[1], 失敗[-1]
 */
int RTC_InPort_read(RTC_InPort* in_port);

/*!
 * \brief ユーザRTCのOutPort側のデータを接続先のInPort側へ送信する。
 *
 * (1)[Port_Marshal_by_TypeCode()]をcallし、送信対象データをCDR形式にマーシャリングする。<BR>
 * (2)[OpenRTM_InPortCdr_put()]をcallし、データの送信が行われる。<BR>
 * (3)データ送信後、送信用のバッファ領域を解放する。
 * \param out_port データ送信対象となるOutPortの情報を管理する[RTC_OutPort]型データのポインタ
 * \return 書き込み成功:[1], 失敗:[-1], InPortと未接続:[0]
 */
int RTC_OutPort_write(RTC_OutPort* out_port);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データを取得する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \return [RTC_Properties]型データのポインタ
 */
RTC_Properties *RTC_RTObject_getProperties(CORBA_RTC_RTObject obj);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データから、"category"に対応したデータを取得する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \return "category"に対応したデータ
 */
char * RTC_RTObject_getCategory(CORBA_RTC_RTObject obj);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データから、"type_name"に対応したデータを取得する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \return "type_name"に対応したデータ
 */
char * RTC_RTObject_getTypeName(CORBA_RTC_RTObject obj);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データから、"instance_name"に対応したデータを取得する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \return "instance_name"に対応したデータ
 */
char * RTC_RTObject_getInstanceName(CORBA_RTC_RTObject obj);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データに、"instance_name"をkeyとし、引数の[name]をvalueとしてデータセットする。
 * \param obj 自RTC_RTObjectオブジェクト
 * \param name 登録予定の"instance_name"に対応したvalue部データ
 * \return 固定値[1]
 */
int RTC_RTObject_setInstanceName(CORBA_RTC_RTObject obj, char *name);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データに、引数の[name]/[value]をデータセットする。
 * \param obj 自RTC_RTObjectオブジェクト
 * \param name 登録予定の[name]部データ
 * \param value 登録予定の[value]部データ
 * \return 固定値[1]
 */
int RTC_RTObject_setProperty(CORBA_RTC_RTObject obj, char *name, char *value);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データから、引数[name]をkeyとして検索した時の対応する[value]値を取得する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \param name 検索予定の[name]部データ
 * \return 引数[name]に対応した[value]値
 */
char * RTC_RTObject_getProperty(CORBA_RTC_RTObject obj, char *name);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データに、引数の[prop]をセットする。 (未使用)
 * \param obj 自RTC_RTObjectオブジェクト
 * \param prop 設定予定の[RTC_Properties]型データ
 * \return 固定値[1]
 */
int RTC_RTObject_registerProperty(CORBA_RTC_RTObject obj, RTC_Properties *prop);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データに、引数の[prop]を追加する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \param prop 追加予定の[RTC_Properties]型データ
 * \return 引数のRTCが持つ、[RTC_Properties]型データ([m_properties])
 */
RTC_Properties * RTC_RTObject_appendProperties(CORBA_RTC_RTObject obj, RTC_Properties *prop);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データから、"naming.names"に対応した[value]を抽出し、その[value]をさらに区切り文字","で分割した、文字列リストを返す。引数の[len]にはその分割数をセットする。
 * \param obj 自RTC_RTObjectオブジェクト
 * \param len 分割数
 * \return 分割後の文字列リスト
 */
char ** RTC_RTObject_getNamingNames(CORBA_RTC_RTObject obj, int *len);

/*!
 * \brief 引数[servant]のRTCに関連した、ExecutionContextの情報を引数の[ec]にセットし、その数を返す。
 * \param servant RTC_RTObjectのサーバント
 * \param ec セット予定のExecutionContextList型ポインタ
 * \return RTCが関連するExecutionContextの数
 */
int RTObject_get_owned_contexts(impl_POA_RTC_RTObject *servant, RTC_ExecutionContextList *ec);

/*!
 * \brief 引数[servant]のRTCに関連した、ExecutionContextの情報を引数の[ec]にセットし、その数を返す。
 * \param servant RTC_RTObjectのサーバント
 * \param ec セット予定のExecutionContextList型ポインタ
 * \return RTCが関連するExecutionContextの数
 */
int RTObject_get_participating_contexts(impl_POA_RTC_RTObject *servant, RTC_ExecutionContextList *ec);

/*!
 * \brief 引数のRTCが持つ、[RTC_Properties]型データから、"exec_cxt.periodic.rate"に対応したデータを取得する。
 * \param obj 自RTC_RTObjectオブジェクト
 * \return "exec_cxt.periodic.rate"に対応した、ExecutionContextのrate値
 */
double RTObject_getExecutionContextRate(CORBA_RTC_RTObject obj);

#endif /* RTM_RTOBJECT_H */

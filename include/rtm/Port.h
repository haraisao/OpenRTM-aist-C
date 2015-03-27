/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Port.h
 * \brief RTCが保持するDataPortの管理全般と各種操作を行う。
 *
 * 「OpenRTM-aist-C++」の「PortAdmin」「PortBase」の必要機能を統合し、C言語版用に整備したもの。
 *
 *「PortServiceList」を管理するPortAdmin構造体の生成と、それらの取得処理機能や、DataPort全般の操作に関わるファイルDataPort管理用構造体と、DataPort(PortService)の生成+削除/可変長データ型処理/CDRデータMarshal+Unmarshal/PortProfileの生成+取得などの操作を行う関数群からなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_PORT_H
#define RTM_PORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************/
/*************************** [ Parameters ] **********************************/
/*****************************************************************************/

/*!
 * \struct PortAdmin_struct
 * \brief RTCが持つ[DataPort]のオブジェクト(PortService)リストの管理データ
 * \param m_pORB CORBA ORB
 * \param m_pPOA CORBA POA
 * \param m_portRefs RTCが持つ[DataPort]のオブジェクト(PortService)リスト
 */
typedef struct PortAdmin_struct {
  CORBA_ORB *m_pORB;
  PortableServer_POA  *m_pPOA;
  RTC_PortServiceList *m_portRefs;
} RTC_PortAdmin;

#if 1 //TODO: [要改良] テスト用として、TypeCodeポインタ一覧用のテーブルを用意。動的にTypeCodeを登録する機能を追加の必要あり。
/*!
 * \brief (TEST) TypeCode Table 
 */
static CORBA_TypeCode TypeCodeTbl[] = {
  TC_RTC_Time,             /* 0 */
  TC_RTC_TimedState,       /* 1 */
  TC_RTC_TimedShort,       /* 2 */
  TC_RTC_TimedLong,        /* 3 */
  TC_RTC_TimedUShort,      /* 4 */
  TC_RTC_TimedULong,       /* 5 */
  TC_RTC_TimedFloat,       /* 6 */
  TC_RTC_TimedDouble,      /* 7 */
  TC_RTC_TimedChar,        /* 8 */
  TC_RTC_TimedBoolean,     /* 9 */
  TC_RTC_TimedOctet,       /* 10 */
  TC_RTC_TimedString,      /* 11 */
  TC_RTC_TimedShortSeq,    /* 12 */
  TC_RTC_TimedLongSeq,     /* 13 */
  TC_RTC_TimedUShortSeq,   /* 14 */
  TC_RTC_TimedULongSeq,    /* 15 */
  TC_RTC_TimedFloatSeq,    /* 16 */
  TC_RTC_TimedDoubleSeq,   /* 17 */
  TC_RTC_TimedCharSeq,     /* 18 */
  TC_RTC_TimedBooleanSeq,  /* 19 */
  TC_RTC_TimedOctetSeq,    /* 20 */
  TC_RTC_TimedStringSeq    /* 21 */
};
#endif


/*!
 * \enum DataPortType
 * \brief DataPortの種別(InPort/OutPort)
 */
typedef enum {
  INPORT_TYPE,
  OUTPORT_TYPE
} DataPortType;

/*!
 * \struct DataPort_struct
 * \brief DataPortの基本情報。OutPort/InPort共通とし、[RTC_OutPort][RTC_InPort]にtypedefしている。
 * \param m_objref RTC_PortServiceのオブジェクトリファレンス (Portは1対1接続を想定)
 * \param m_portType DataPortの種別(InPort/OutPort)
 * \param m_typecode CORBA_TypeCode構造体へのポインタ
 * \param m_value Portに関連付く送受信データを内部割り当て用のvoidポインタ
 */
typedef struct DataPort_struct {
    RTC_PortService m_objref;  /* ObjRef of PortService (One-on-One)*/  
    DataPortType m_portType;  /* (IN/Out) */
    CORBA_TypeCode m_typecode; /* Pointer of TypeCode_Struct */
    void *m_value; /* DataType's data */
} RTC_DataPortBase;  

/*** DataPortBase --> InPort/OutPort (common) ***/
typedef RTC_DataPortBase RTC_OutPort;
typedef RTC_DataPortBase RTC_InPort;


/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/*!
 * \brief Portオブジェクトを生成する。
 *
 *        (1)Portで扱うデータの型名に応じて、[RepositryID]を生成する。 <BR>
 *        (2)[RepositryID]に対応した、[TypeCode]を取得する。<BR>
 *        (3)引数[type_name]のデータ型名(モジュール名など含む階層を"_"で付与した状態)から、最終的なデータ型名を取得する。<BR>
 *        (4)「Port_create_PortService()」により、[PortService]オブジェクトを生成する。これは、RTObject型オブジェクトが持つ[m_portAdmin]内にセットされる。さらに、[RTC_PortProfile]データも生成する。<BR>
 *        (5)「Port_create_DataPortBase()」により、[DataPortBase]型データを生成する。これは、PortService型オブジェクトが持つ[m_portProfile]内にセットされる。<BR>
 *        (6)(5)で生成されたデータのポインタを返す。
 * \param rtobj DataPortを保持する親のRTC_RTObjectオブジェクト
 * \param port_name 生成するPortの名前
 * \param type_name 生成するPortで扱うデータのデータ型名称(モジュール名_変数名の必要あり。例として、[RTC_TimedLong]など)
 * \param port_type 生成するPortの種別(INPORT_TYPE/OUTPORT_TYPE)
 * \return 生成されたPortの情報を管理する[RTC_DataPortBas]型データのポインタ
 */
RTC_DataPortBase* Port_createPort(CORBA_RTC_RTObject rtobj, const char *port_name, const char *type_name, DataPortType port_type);

RTC_DataPortBase* Port_createPort2(CORBA_RTC_RTObject rtobj, const char *port_name, CORBA_TypeCode typecode, DataPortType port_type);

/*!
 * \brief 未実装(T.B.D)
 * \return 未実装(T.B.D)
 */
void Port_deletePort();

/*!
 * \brief OutPortにて、扱うデータの型が可変長(sequence型)の場合に、その長さを指定(メモリの確保)する。Portが生成されていれば、RTCがどの状態遷移にいても指定可能である。なお、サイズ「0」を指定すれば、既に確保したメモリを解放する。
 *
 *        (1) [Port_getIndexOfTypeCode()]により、深い階層も想定の複合型のデータ型の中から、引数の[value_name]で指定した、可変長サイズ指定対象の変数名に該当する、要素の部分を見つけだし、その[TypeCode]と[index]を取得する。<BR>
 *        (2) (1)上書きされた[tc]のメンバ要素[index]のTypeCodeデータを[tc_member]とする。[tk_alias]タイプの場合はさらに要素[0]のTypeCodeデータを[tc_member]とする。<BR>
 *        (3) 該当変数は必ず、sequence型で定義しているはずなので、TypeCodeはCORBA_Sequence型のため、さらに要素[0]のTypeCodeデータを[tc_base]とする。<BR>
 *        (4) [tc_base]を元に、RtORB_alloc_by_typecode()をcallし、TypeCodeに応じたメモリ確保を行う。<BR>
          (5) 成功すれば[1]を失敗すれば[-1]を返す。<BR>
 *        (*) TypeCodeは、[tc(複合型データ部)] [tc_member([sequence<???> value]の部分)] [tc_base(CORBA_Sequence型部)]をそれぞれ表す。
 * \param out_port 生成済みのOutPortの情報を管理する[RTC_OutPort]型データのポインタ
 * \param length 扱うデータの可変長サイズ指定用の長さ("0"を指定すれば、既に確保したメモリ解放)
 * \param val 可変長(sequence型)で定義された変数自体(sequence型/struct型が入れ子になり深い階層の場合にも、全てを記述)
 * \param val_name 可変長(sequence型)で定義された変数の名前("data" or "parent.child.data")
 * \return 成功:[1], 失敗[-1]
 */
int Port_setSequenceLength(RTC_OutPort *out_port, CORBA_unsigned_long length, void* val, const char* val_name);

/*!
 * \brief データの型が可変長(sequence型)のDataPortにおいて、その長さを取得する。
 *
 *        (1) [Port_getIndexOfTypeCode()]により、深い階層も想定の複合型のデータ型の中から、引数の[value_name]で指定した、可変長サイズ指定対象の変数名に該当する、要素の部分を見つけだし、その[TypeCode]と[index]を取得する。<BR>
 *        (2) (1)上書きされた[tc]のメンバ要素[index]のTypeCodeデータを[tc_member]とする。[tk_alias]タイプの場合はさらに要素[0]のTypeCodeデータを[tc_member]とする。<BR>
 *        (3) CORBA_sequence型データを保持しているので、[_length]データから、サイズ長を取得する。<BR>
 *        (4)成功すれば[現在の可変長(sequence型)の長さ]を、失敗すれば[-1]を返す。
 * \param port 生成済みのDataPortの情報を管理する[RTC_DataPortBase]型データのポインタ
 * \param val 可変長(sequence型)で定義された変数自体(sequence型/struct型が入れ子になり深い階層の場合にも、全てを記述)
 * \param val_name 可変長(sequence型)で定義された変数の名前("data" or "parent.child.data")
 * \return 成功:[現在の可変長(sequence型)の長さ], 失敗:[-1]
 */
uint32_t Port_getSequenceLength(RTC_DataPortBase *port, void* val, const char* val_name);

/*!
 * \brief 引数[out_port]内の[m_value]にセット済みの送信用データを、CDR形式にマーシャリングして、引数[cdr_data]のメモリを確保して、そこにセットする。
 *
 *        (1)バッファに固定の最大サイズでメモリ確保する。 <BR>
 *        (2)引数[out_port]内の[m_value]にセット済みの送信用データと、TypeCodeデータを用いて、[()]をcallし、CDR形式へマーシャリングし、(1)で確保したバッファにセットする。この時、その時の合計サイズ[data_size]を算出する。<BR>
 *        (3)引数の[cdr_data]に関して、サイズ[data_size]でメモリ確保する。<BR>
 *        (4)バッファから[cdr_data]へデータをコピーし、バッファ部をfreeする。<BR>
 *        (5)成功すれば[1]を、メモリ確保などで失敗すれば[-1]を返す。
 * \param cdr_data 送信用CDR形式データ格納用ポインタ
 * \param out_port 送信対象OutPortの[RTC_OutPort]型データポインタ
 * \return 成功:[1]、失敗(メモリ確保失敗):[-1]
 */
int Port_Marshal_by_TypeCode(OpenRTM_CdrData *cdr_data,  RTC_OutPort *out_port);

/*!
 * \brief 引数[cdr_data]に受信時に格納された、CDR形式データをアンマーシャリングして、引数[in_port]内の[m_value]にセットする。
 *
 *        内部で、RtORBの[demarshal_by_typecode()]をcallするのみ。
 * \param cdr_data 受信したCDR形式データ格納用ポインタ
 * \param in_port 受信対象InPortの[RTC_InPort]型データポインタ
 * \return void
 */
void Port_UnMarshal_by_TypeCode(OpenRTM_CdrData *cdr_data,  RTC_InPort *in_port);

/*!
 * \brief 引数の[RTC_PortAdmin]型データ[admin]に既にセットされた、PortServiceに関する情報を取得する。
 *
 *        (1)引数の[admin]がNULLの場合は、返り値にNULLをセットする。<BR>
 *        (2)引数[admin]の要素[m_portRefs]の情報を返り値にコピーする。
 * \param admin [RTC_PortAdmin]型データ
 * \return 取得したRTC_PortServiceList型データ(PortServiceオブジェクトのリストデータ)
 */
RTC_PortServiceList * Port_getPortServiceList(RTC_PortAdmin *admin);

/*!
 * \brief 引数[admin]の要素[m_portRefs]に格納されたPortServiceオブジェクトの数の分だけの、PortProfile情報のリストを取得する。
 *
 *        (1)[admin]、もしくは[m_portRefs]が空の場合は、引数[ppl]にNULLをセットする。<BR>
 *        (2)引数[ppl]にPortProfileの個数分のサイズをメモリ確保し、[Port_getPortProf()]をcallし、取得したPortProfileデータを引数[ppl]にセットする。
 * \param admin [RTC_PortAdmin]型データ
 * \param ppl 取得したRTC_PortProfileList型データ
 * \return void
 */
void Port_getPortProfileList(RTC_PortAdmin *admin, RTC_PortProfileList *ppl);

/*!
 * \brief 引数[obj]が保持している[RTC_PortProfile]型データをコピーして返す。
 *
 *        (1)[RTC_PortProfile]型データを保持していない場合、NULLをセットする。<BR>
 *        (2)PortProfileデータをコピーする。この時、[connector_profiles]に関しては、[Port_dupConnProfList()]関数でセット、[properties]に関しては、[NVUtil_dupNVList()]でセットする。
 * \param obj PortProfile取得対象のRTC_PortServiceオブジェクト
 * \param prof データセット用の、RTC_PortServiceオブジェクト[obj]が持つ[RTC_PortProfile]型データポインタ
 * \return void
 */
void Port_getPortProf(CORBA_RTC_PortService obj, RTC_PortProfile *prof);

/*!
 * \brief 引数[src]の[RTC_ConnectorProfileList]型データを、引数[dest]にコピーする。<BR>
 *        内部で[Port_dupConnProf()]をcallする。
 * \param dest コピー先の[RTC_ConnectorProfileList]型データ
 * \param src コピー元の[RTC_ConnectorProfileList]型データ
 * \return void
 */
void Port_dupConnProfList(RTC_ConnectorProfileList* dest, RTC_ConnectorProfileList src);

/*!
 * \brief 引数[src]の[RTC_ConnectorProfile]型データを、引数[dest]にコピーする。
 * \param dest コピー先の[RTC_ConnectorProfile]型データ
 * \param src コピー元の[RTC_ConnectorProfile]型データ
 * \return void
 */
void Port_dupConnProf(RTC_ConnectorProfile* dest, RTC_ConnectorProfile src);

#endif /* RTM_PORT_H */


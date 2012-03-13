/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Manager.h
 * \brief RTC管理用Managerファイルで、Manager構造体と各種処理関数の実装。
 *
 *        (OpenRTM-aist-C++では、[Manager][ManagerConfig][ManagerServant]部に該当する。)
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_MANAGER_H
#define RTM_MANAGER_H

#include <rtm/OpenRTM-aist.h>
#include <rtm/OpenRTM-aist-decls.h>
#include <rtm/Properties.h>
#include <rtm/NamingManager.h>
#include <rtm/RTComp.h>

#define RTC_CREATED	0
#define RTC_INACTIVE	1
#define RTC_ACTIVE	2
#define RTC_RUNNING	3
#define RTC_ERROR	-1

/*!
 * \struct RTC_Manager_struct
 * \brief Managerの基本情報。
 * \param argc ユーザRTC起動時のManagerオプション用引数(未使用)
 * \param argv ユーザRTC起動時のManagerオプション用引数(未使用)
 * \param mode CORBA_ORB実行時用のECモード
 * \param m_counter Managerが管理するRTCのインスタンス数
 * \param status Managerの状態(RTC_INACTIVE/RTC_ACTIVE/RTC_RUNNING/RTC_ERROR)
 * \param m_config Managerが持つ、各種コンフィグ情報データ
 * \param m_pORB CORBA_ORBポインタ
 * \param m_pPOA RootPOAポインタ
 * \param m_pPOAManager POAManagerポインタ
 * \param m_namingManager [RTC_NamingManager]型データ(NameServer登録用情報格納データ)のポインタ
 * \param m_mgrservant ManagerServant([RTM_Manager]型オブジェクト)のリファレンス
 * \param ModuleInitProc ユーザRTCInit用プロシージャ
 * \param ModuleCreateProc ユーザRTC生成用プロシージャ
 * \param ModuleDeleteProc ユーザRTC削除用プロシージャ
 * \param ModuleProfile RTCのコンポーネントProfileデータ
 * \param m_pComp ユーザ生成RTCの雛形となる構造体へのポインタ
 */
typedef struct RTC_Manager_struct{
  int argc;
  char **argv;
  ECMode_t mode;
  int32_t m_counter;
  int32_t status;
  RTC_Properties *m_config;
  CORBA_ORB m_pORB;
  PortableServer_POA m_pPOA; 
  PortableServer_POAManager m_pPOAManager;
  RTC_NamingManager *m_namingManager;
  RTM_Manager m_mgrservant;
  RTC_ReturnCode_t (*ModuleInitProc)(struct RTC_Manager_struct *);
//  void *(*ModuleCreateProc)(struct RTC_Manager_struct *manager);
//  void (*ModuleDeleteProc)(void **obj);
  RTComp* (*ModuleCreateProc)(struct RTC_Manager_struct *manager);
  void (*ModuleDeleteProc)(RTComp *obj);
  char **ModuleProfile;
  RTComp* m_pComp;
}RTC_Manager;


/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/
/*!
 * \brief [RTC_Manager]型データのManagerを生成する。詳細は、以下を参照。なお、当関数はユーザRTCソース[Comp.c]内の[main()]からcallされる。
 *
 *        (1)[RTC_Manager]型データ[res]を生成しメモリ確保する。
 *        (2)[RTC_Manager_initManager()]をcallし、[res]の要素に引数の初期値をセット、デフォルトPropertiesデータをセットする。 <BR>
 *        (3)[RTC_Manager_initLogger()]をcallする。(未実装) <BR>
 *        (4)[RTC_Manager_initORB()]をcallし、[CORBA_ORB/POA/POAManager]をそれぞれ生成する。 <BR>
 *        (5)[RTC_Manager_initNaming()]をcallし、 NameServer情報の生成を行う。  <BR>
 *        (6)[RTC_Manager_initFactories()]をcallする。(未実装) <BR>
 *        (7)[RTC_Manager_initExecContext()]をcallする。(現在、未使用) <BR>
 *        (8)[RTC_Manager_initComposite()]をcallする。(現在、未使用) <BR>
 *        (9)[RTC_Manager_initTimer()]をcallする。(未実装) <BR>
 *        (10)[RTC_Manager_initManagerServant()]をcallし、ManagerServantを生成する。（現在、未使用） <BR>
 *        (11)[manager]が持つ[status]を[RTC_INACTIVE]にセットする。 <BR>
 *        (12)生成したManagerを返す。
 * \param argc ユーザRTC起動時のManagerオプション用引数(未使用)
 * \param argv ユーザRTC起動時のManagerオプション用引数(未使用)
 * \return 生成した[RTC_Manager]型データ
 */
RTC_Manager * RTC_Manager_init(int argc, char **argv);

/*!
 * \brief 引数[manager]が持つ[ModuleInitProc]プロシージャに、引数[init_func]にセットされたユーザRTCの[MyModuleInit()]関数ポインタをセットする。当関数はユーザRTCソース[Comp.c]内の[main()]からcallされる。
 * \param manager [RTC_Manager]型データ
 * \param init_func ユーザRTCの[MyModuleInit()]関数ポインタ
 * \return void
 */
void RTC_Manager_setModuleInitProc(RTC_Manager *manager, 
                                   RTC_ReturnCode_t (*init_func)(RTC_Manager *manager));

/*!
 * \brief ManagerをACTIVE状態にし、ユーザRTCを生成する。詳細は、以下を参照。なお、当関数はユーザRTCソース[Comp.c]内の[main()]からcallされる。
 *
 *        (1) [RTC_Manager_setModuleInitProc()]でセットされた、ユーザRTCの[MyModuleInit()]関数がcallされる。以降、[MyModuleInit()]内の処理を説明する。<BR>
 *        (1-A) ["ユーザRTコンポーネント名"Init()]をcallする。内部で[RTC_Manager_registerFactory()]がcallされ、引数[manager]の要素に、RTC固有のプロシージャやプロファイルがセットされる。<BR>
 *        (1-B) [RTC_Manager_createComponent()]をcallし、RTC用のRTC_RTOBject型オブジェクトを生成する。生成に失敗した場合には、[abort()]が実行され、RTCの生成処理は終了される。(詳細は、[RTC_Manager_createComponent()]の項を参照のこと。)<BR>
 *        (1-C) 以降、デバッグ出力用の処理がある。RTCのプロファイル情報の取得とそれの出力処理、DataPortの有無情報の取得、DataPortのPortProfile情報の取得と出力などを行う。詳細説明は割愛する。<BR>
 *        (2) (1)の処理が成功(返り値が"RTC_OK")ならば、[manager]が持つ[status]を[RTC_ACTIVE]にセットする。<BR>
 *        (3) 返り値として、内部処理に成功すれば[1]を、失敗すれば[0]を返す。
 * \param manager [RTC_Manager]型データ
 * \return 成功:[1]、失敗:[0]
 */
int RTC_Manager_activateManager(RTC_Manager *manager);

/*!
 * \brief Managerを実行状態にし、CORBA_ORBを実行する(実行ループ状態)。 当関数はユーザRTCソース[Comp.c]内の[main()]からcallされる。
 *
 *        (1) [manager]が持つ[status]を[RTC_RUNNING]にセットする。<BR>
 *        (2) [CORBA_ORB_run()]をcallし、CORBA_ORBを実行する。(未使用)
 * \param manager [RTC_Manager]型データ
 * \param mode CORBA_ORB running Mode(ExecutionContext)
 * \return void
 */
void RTC_Manager_runManager(RTC_Manager *manager, ECMode_t mode);

/*!
 * \brief   (Uncalled.) (T.B.D)
 * \param manager [RTC_Manager]型データ
 * \return void
 */
void RTC_Manager_stopManager(RTC_Manager *manager);

/*!
 * \brief   (Uncalled.) (T.B.D)
 * \param manager [RTC_Manager]型データ
 * \return void
 */
void RTC_Manager_delete(RTC_Manager *manager);

/*!
 * \brief ユーザRTCを生成する。詳細は、以下を参照。なお、当関数はユーザRTCソース[Comp.c]内の[MyModuleInit()]からcallされる。
 *
 *        (1) [RTC_Manager_procComponentArgs()]をcallし、引数[comp_args]内で記述された、RTC固有の[ID][Configuration]情報を抽出し、RTC_Properties型データ[id][conf]にセットする。 <BR>
 *        (2) 新規に[RTC_Properties]型データ[prop]を作成し、(1)でセットした[conf]を追加する。さらに、[RTC_Manager_setSystemInformation()]をcallし、内部取得したOSのシステム情報やプロセスIDなどをセットする。<BR>
 *        (3) [prop]追加用に、[inherit_prop]を"name"として用意し、[prop]内に該当するvalueがなければ、[manager]の[m_config]からそれらのvalueを取得し、[prop]に追加する。  <BR>
 *        (4) [ModuleCreateProc]にセットされた、ユーザRTCのcreate()関数をcallし、RTC_RTObject型のオブジェクトを生成する。<BR>
 *         (*) create()関数の内部では、「RTC_RTObjectオブジェクトの生成」「RTComp型構造体のメモリ確保とユーザ定義変数m_private領域用のメモリ確保」「各種ActivityのCallback関数ポインタのセット」「各種ポインタの相互セット」などの処理が行われる。<BR>
 *        (5) [RTC_RTObject_appendProperties()]をcallし、(4)で生成したRTObjectが持つ、Propertiesデータ[m_properties]に[prop]を追加セットする。<BR>
 *        (6) RTCのインスタンス名を生成し、インスタンス個数の[m_counter]をインクリメントする。さらに、[RTC_RTObject_setInstanceName()]をcallし、RTCのプロパティ"instance_name"のvalueとしてセットする。<BR>
 *        (7) [RTC_Manager_configureComponent()]をcallし、RTC固有のConfigファイルがある場合は、その中身のプロパティ情報を、内部生成したNameServer登録用に使用するプロパティを、それぞれ(4)で生成したRTObjectが持つ、Propertiesデータ[m_properties]に追加セットする。<BR>
 *        (8) [RTC_RTObject_initialize()]をcallし、RTCの初期化処理を行う。処理に失敗した場合は、[RTC_RTObject_exit]をcallし、RTC生成処理を終了する。<BR>
 *        (9) [RTC_Manager_registerComponent()]をcallし、RTCのNameServerへの登録処理を行う。 <BR>
 *        (10) 正常生成された、ユーザRTC用の[RTC_RTObject]型オブジェクトリファレンスを返す。
 * 
 * \param manager [RTC_Manager]型データ
 * \param comp_args 生成するRTCの[ID]や[Configuration]を指定format([id]?[configuration])で記述したもの。
 * \return 生成した、ユーザRTC用の[RTC_RTObject]型オブジェクトリファレンス
 */
CORBA_RTC_RTObject RTC_Manager_createComponent(RTC_Manager *manager, const char *comp_args);

/*!
 * \brief 引数[manager]が持つ各種プロシージャ要素に、引数の[profile][creat_func][delete_func]をそれぞれセットする。当関数はユーザRTCソース内のInit()からcallされる。
 * \param manager [RTC_Manager]型データ
 * \param profile ユーザRTCのコンポーネントプロファイル情報(spec[])
 * \param create_func ユーザRTC生成用関数ポインタ
 * \param delete_func ユーザRTC削除用関数ポインタ
 * \return void
 */
void RTC_Manager_registerFactory(RTC_Manager *manager, const char **profile,
      RTComp* (*create_func)(RTC_Manager *manager), void (*delete_func)(RTComp *obj));

/*!
 * \brief NameServerへ引数の[RTC_RTObject]型オブジェクト[comp]の登録を行う。
 *
 *        (1)[RTC_RTObject_getNamingNames()]をcallして、[comp]が持つproperty情報から["naming.names"]にマッチした名前リストを取得する。<BR>
 *        (2)[RTC_NamingManager_bindObject()]をcallして、NameServer(複数可)に登録処理を行う。<BR>
 *        (*)当処理は、[RTC_Manager_createComponent()]内でcallされる。
 * \param mgr [RTC_Manager]型データ
 * \param comp NameServerに登録する[RTC_RTObject]型オブジェクト
 * \return void
 */
void RTC_Manager_registerComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp);

/*!
 * \brief NameServerから引数の[RTC_RTObject]型オブジェクト[comp]の解除を行う。
 *
 *        (1)[RTC_RTObject_getNamingNames()]をcallして、[comp]が持つproperty情報から["naming.names"]にマッチした名前リストを取得する。<BR>
 *        (2)[RTC_NamingManager_unbindObject()]をcallして、NameServer(複数可)からの解除処理を行う。
 * \param mgr [RTC_Manager]型データ
 * \param comp NameServerから解除する[RTC_RTObject]型オブジェクト
 * \return void
 */
void RTC_Manager_unregisterComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp);

/*!
 * \brief [NamingManager]型変数用にメモリ確保し、そのポインタを返す。引数の[Manager]ポインタを[*m_manager]にセットする(相互セット)。 RTC_Manager_initNaming()関数よりcallされる。
 * \param mgr 呼び出し元の[RTC_Manager]型ポインタ
 * \return メモリ確保済みの[RTC_NamingManager]型のポインタ、失敗時はNULL。
 */
RTC_NamingManager *RTC_NamingManager__new(RTC_Manager *mgr);


#endif /* RTM_MANAGER_H */


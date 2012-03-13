/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file NamingManager.h
 * \brief Naming Manager (NameServer情報の取得、NameServer登録用RTC情報の生成、NameServerへのRTC登録/解除処理)
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
  [RTC_NamingManager]
    |_[RTC_Name]
    |     |_[RTC_NamingBase]
    |            |_[NamingContext/NameServer/ORB]
    |_[RTC_Comp]
          |_[RTC_RTObject]

 <0>RTC_NamingManager__new() <== [<Manager> RTC_Manager_initNaming()]

 <1>RTC_NamingManager_registerNameServer()
     ==> RTC_NamingBase_createNamingObj()
          ==> NamingOnCorba__new()
          ==> NamingOnCorba__resolve()
          ==> NamingOnCorba__delete()
     ==> RTC_Name__new()
     ==> RTC_NamingManager_appendNamingBase()
 
 <2>RTC_NamingManager_bindObject()
     ==> RTC_NamingBase_bindObject()
*/

#ifndef RTC_NAMING_MANAGER_H
#define RTC_NAMING_MANAGER_H
#include <RtORB/corba.h>
#include <CosName/CosNaming.h>

/*****************************************************************************/
/************************** [ Parameters ] ***********************************/
/*****************************************************************************/

/*!
 * \struct RTC_NamingBase
 * \brief RTCを登録する、NameServiceの基本情報。
 * \param name_server NameServer名
 * \param orb CORBA_ORB
 * \param rootContext CosNaming_NamingContextオブジェクト(NameServerへRTCのbind/unbind、context管理を行うインタフェース)
 * \param env CORBA_Environment (RtORB例外情報) 
 */
typedef struct {
  char *name_server;
  CORBA_ORB orb;
  CosNaming_NamingContext rootContext;
  CORBA_Environment env;
} RTC_NamingBase;

/*!
 * \struct RTC_Name
 * \brief RTCを登録する、NameServiceの基本情報。
 * \param methods NameServerへの通信手段(デフォルトは"naming.type"の["corba"])
 * \param nsname NameServer名
 * \param name RTC_NamingBase(NameServiceの基本情報)へのポインタ
 */
typedef struct {
  char *methods;
  char *nsname;
  RTC_NamingBase *name;
} RTC_Name;

/*!
 * \struct RTC_Comp
 * \brief 登録予定のRTCの基本情報
 * \param name RTC名
 * \param rtobj RTC_RTObjectオブジェクト(RTCの最上位のCORBAオブジェクト)
 */
typedef struct {
  char *name;
  RTC_RTObject rtobj;
} RTC_Comp;

/*!
 * \struct RTC_NamingManager
 * \brief NameServiceへ登録処理用の各種情報を格納したもの
 * \param m_names RTCを登録予定の複数のNameServerのポインタを羅列したもの
 * \param n_name RTCを登録予定のNameServerの個数
 * \param m_compNames 登録予定の複数のRTCポインタを羅列したもの (未使用)
 * \param n_comp 登録予定のRTCの個数 (未使用)
 * \param m_manager RTC_Managerへのポインタ(相互リンク用)
 */
typedef struct {
  RTC_Name **m_names;
  int n_name;
  RTC_Comp **m_compNames;
  int n_comp;
  struct RTC_Manager_struct *m_manager;
} RTC_NamingManager;


/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/
/* [Prototype is in Manager.h]
RTC_NamingManager *RTC_NamingManager__new(RTC_Manager *mgr);
*/

/*!
 * \brief 内部のconfiguration値より、NameServer情報の生成(未接続)が主目的。
 *
 *      引数の[method][name_server][orb(mgr->m_manager->orb)]から、RTC_NamingManager__new()で事前生成済みの[RTC_NamingManager]型データの中身の情報をセットする。詳細は各種内部関数にて実行。<BR>
 *       最終的に、[RTC_NamingManager]内の[RTC_Comp]に関する情報以外がセットされる。<BR>
 *       Managerファイルの[RTC_Manager_initNaming()]よりcallされ、内部で、[RTC_NamingBase_createNamingObj()],[RTC_Name__new()], [RTC_NamingManager_appendNamingBase()]の3関数をcallする。
 * \param mgr RTC_NamingManager__new()で生成された、[RTC_NamingManager]型データ
 * \param method 通信メソッド(デフォルト:"corba")
 * \param name_server NameServer名
 * \return void
 */
void RTC_NamingManager_registerNameServer(RTC_NamingManager *mgr, const char *method, const char *name_server);

/*!
 * \brief [RTC_NamingBase]型データに格納されているNameServer情報と、引数の[name][rtobj]より、登録するRTC情報を用いて、NameServerへの登録(bind)を行う。(複数のNameServerに１つのRTCを登録出来るような仕様。) 
 *
 *        Managerファイルの[RTC_Manager_registerComponent()]/[RTC_Manager_initManagerServant()]よりcallされる。<BR>
 *        内部で、[RTC_NamingBase_bindObject()]関数をcallする。
 * \param mgr 生成済みの[RTC_NamingManager]データ(NameServer情報が使用される)
 * \param name 登録するRTCの名前("naming.formats"で指定された形式の文字列)
 * \param rtobj 登録するRTCのCORBAオブジェクト
 * \return void
 */
void RTC_NamingManager_bindObject(RTC_NamingManager *mgr, const char *name, const RTC_RTObject rtobj);

/*!
 * \brief (未実装)
 */
void RTC_NamingManager_update(RTC_NamingManager *mgr);

/*!
 * \brief [RTC_NamingBase]型データに格納されているNameServer情報と、引数の[name]より、複数のNameServerから、登録されているRTCを消去する。
 * \param mgr 生成済みの[RTC_NamingManager]データ(NameServer情報が使用される)
 * \param name 登録されているRTCの名前("naming.formats"で指定された形式の文字列)
 * \return void
 */
void RTC_NamingManager_unbindObject(RTC_NamingManager *mgr, const char *name);

/*!
 * \brief (未実装)
 */
void RTC_NamingManager_unbindAll(RTC_NamingManager *mgr);

#endif /* RTC_NAMING_MANAGER_H */

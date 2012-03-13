/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file NVUtil.h
 * \brief NameValue型データの処理を扱うUtilityファイル。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_NVUTIL_H
#define RTM_NVUTIL_H
#include <rtm/OpenRTM-aist.h>

/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/
/*!
 * \brief SDOPackage_NVList型データ用のメモリを確保し、そのポインタを返す。
 * \return メモリ確保済みのSDOPackage_NVList型データを返す
 */
SDOPackage_NVList * NVUtil_new();

/*!
 * \brief 引数のNVList型データの中身(NameValue型[name/value(string型のみ)])をダンプする。
 * \param nv SDOPackage_NVList型データ
 * \return void
 */
void NVUtil_dump(SDOPackage_NVList nv);

/*!
 * \brief 引数のNameValue型データ[nv]に引数の[name][value]をセットする。この時、[value]部はCORBA_Any型として、メモリ確保する。
 * \param nv SDOPackage_NameValue型データ
 * \param name 登録する[name]値
 * \param value 登録する[value]値
 * \return void
 */
void NVUtil_setNV(SDOPackage_NameValue *nv, char *name, char *value);

/*!
 * \brief 引数のSDOPackage_NameValue型データをコピー(duplicate)する。この時、[value]部はCORBA_Any型の[string型]のみ可能とする。
 * \param dest コピー先のSDOPackage_NameValue型データ
 * \param src コピー元のSDOPackage_NameValue型データ
 * \return void
 */
void NVUtil_dupNV(SDOPackage_NameValue *dest, SDOPackage_NameValue *src);

/*!
 * \brief 引数のSDOPackage_NameValue型データ[nv]を削除する。内部でCORBA_Any型データのメモリ解放処理。
 * \param nv 削除対象のSDOPackage_NameValue型データ
 * \return void
 */
void NVUtil_freeNV(SDOPackage_NameValue *nv);

/*!
 * \brief 引数のRTC_NVList型データをコピー(duplicate)する。内部で、[NVUtil_dupNV()]をcallする。
 * \param dest コピー先のRTC_NVList型データ
 * \param src コピー元のRTC_NVList型データ
 * \return void
 */
void NVUtil_dupNVList(RTC_NVList* dest, RTC_NVList src);

/*!
 * \brief 引数のRTC_NVList型データ[nvlist]を削除する。内部で、[NVUtil_freeNV()]をcallする。
 * \param nvlist 削除対象のRTC_NVList型データ
 * \return void
 */
void NVUtil_freeNVList(RTC_NVList* nvlist);

/*!
 * \brief 引数のRTC_NVList型データ[nvlist]の末尾に、引数の[name][value]をSDOPackage_NameValue型データとして追加セットする。<BR> 
 *        内部では、一旦退避し、新たに、lengthを増やしてメモリ確保し、古い領域はfreeして、再度、新データも含めセットする。
 * \param nvlist 追加先のRTC_NVList型データ
 * \param name 登録する[name]値
 * \param value 登録する[value]値
 * \return void
 */
void NVUtil_appendNVList(RTC_NVList* nvlist, char *name, char *value);


#endif /* RTM_NVUTIL_H */

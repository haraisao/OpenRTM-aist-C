/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Utils.h
 * \brief 各種文字列操作用Utilityファイル。主に、Properties操作において使用される。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_UTILS_H
#define RTM_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1

#ifndef MAX_STRBUF
#define MAX_STRBUF		256
#endif

#ifndef MIN
#define MIN(a,b)		((a) < (b) ? (a) : (b))
#endif

#ifndef MAX_MARSHALBUF
#define MAX_MARSHALBUF 2097152  /* 2MB */
#endif

#endif

/*!
 * \struct string_sequence
 * \brief 複数の[string]データをポインタで繋ぎ、[string]のListとして保持する構造体
 * \param maximum 複数の[string]データを保持するMAX値
 * \param length 保持している複数の[string]データの個数
 * \param buffer 複数の[string]データ保持用のポインタのポインタ
 */
typedef struct{
  int maximum;
  int length;
  char **buffer;
}string_sequence;


/*************************** [ Functions ] ***********************************/

/*!
 * \brief 引数[len]の数の長さ分の[string_sequence]型データ用にメモリ確保し、そのポインタを返す。
 * \param len string_sequence型の[length]相当
 * \return メモリ確保された[string_sequence]型データのポインタ
 */
string_sequence * new_string_sequence(int len);

/*!
 * \brief 引数で指定した[string_sequence]型データを削除する。
 * \param seq 削除する[string_sequence]型データのポインタ
 * \return void
 */
void free_string_sequence(string_sequence *seq);

/*!
 * \brief 引数の検索対象の文字列[str]の中に、区切り文字[delim]が含まれている個数を返す。
 * \param str 検索対象の文字列
 * \param delim 区切り文字
 * \return 検索対象の文字列内に区切り文字[delim]が含まれている個数
 */
int count_delim(char *str, const char delim);

/*!
 * \brief 引数の文字列[str]のトリミングを行う。具体的には、文字列[str]を一文字目から調査し、スペースや改行コードが含まれて入れば、その時点までの文字列に、終端コードを付与して返す。
 * \param str 対象の文字列
 * \return トリミング後の文字列
 */
char * trim_string(char *str);
/*!
 * \brief 引数の文字列[str]に対し、引数[delim]を区切り文字として、[str]を分割し、[string_sequence]型の文字列群データにセットし、そのポインタを返す。
 * \param str 元の文字列
 * \param delim 区切り文字
 * \param max 区切り個数のMAX値
 * \return 区切り文字で分割された、[string_sequence]型の文字列群データ
 */
string_sequence *split_string(char *str, const char delim, int max);

#endif /* RTM_UTILS_H */

/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Properties.h
 * \brief RTCのコンフィグレーションなどを保持する、[RTC_Properties]型構造体データと、各種操作(挿入/取り出し/検索/...)用の関数などのUtilityファイル。
 *
 *        主に、RTCが持つ、設定用パラメータ群を登録するのに使われ、CORBAインタフェースの
関数で必要とされるパラメータは適宜、このデータから取り出すことを目的とする。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_PROPERTIES_H
#define RTM_PROPERTIES_H

#include <rtm/Utils.h>

/*!
 * \struct RTC_Properties
 * \brief RTCのコンフィグレーション保持用構造体。[name/value/default_value]をペアとして、親や子を持つツリー構成をとる。
 * \param name ノード内に登録する[name]値
 * \param value ノード内に登録する[value]値
 * \param default_value ノード内に登録する[value]の初期値
 * \param n_leaf 当ノードが持つ、子ノード(leaf)の数
 * \param root 親ノードへのポインタ
 * \param leaf 子ノード(leaf)へのポインタ
 */
typedef struct Properties_struct {
  char * name;
  char * value;
  char * default_value;
  int n_leaf;
  struct Properties_struct *root;
  struct Properties_struct **leaf;
} RTC_Properties;


/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/*!
 * \brief [RTC_Properties]型のメモリをcallocし、「res」として生成。引数の「name」を「res->name」にセットし、「res」を返す。
 * \param name [RTC_Properties]の[name]にセットする値
 * \return 生成された[RTC_Properties]型データのポインタ
 */
RTC_Properties *Properties__new(char *name);

/*!
 * \brief Global変数[Default_Config]に、「DefaultConfig.h」で用意された「default_config[]」のデフォルト値をセットし、返す。
 *
 *        RTC_Manager_configure()からのみcallされる。<BR>
 *        Properties_createDefaultProperties()関数と中身の処理は同じようなもので、引数の[spec]か[default_config]かの違い。<BR>
 * (1)まず、Global変数の[Default_Config]がNullか確認し、Nullでなければ、Propertie_delete()関数にて、Null化する。<BR>
 * (2)Properties_new("root")より、[Default_Config]に「name="root"」として、メモリ確保する。<BR>
 * (3)Properties_setDefault( Default_Config, key, value )の形式で、[default_config[]]の中身を key/valueに分割し、[Default_Config]の中身にRTC_Propertiesの形式で[root][leaf]を持つツリー状態でセットし、返り値として返す。<BR>
 * \return 初期セットされた[RTC_Properties]型データのポインタ
 */
RTC_Properties * Properties_make_system_default();

/*!
 * \brief 新規生成のRTC_Propertiesデータ内に、引数の[spec]の中身の[key/value]をセットし、返す。 
 *
 *        RTC_Manager_procComponentArgs()からのみcallされる。<BR>
 *        Properties_make_system_default()関数と中身の処理は同じようなもので、引数の[spec]か[default_config]かの違い。<BR>
 *        refister_Factory()により、「Componentのspec[]情報」がprofileとして、「manager->ModuleProfile」にセットされて、当関数の引数specになる。<BR>
 * (1)Properties_new("root")より、[res]に「name="root"」として、メモリ確保する。<BR>
 * (2)Properties_setDefault( res, key, value )の形式で、引数[spec]の中身を key/valueに分割し、RTC_Propertiesの形式で[root][leaf]を持つツリー状態でセットし、[res]の中身にセットする。  [res]を返り値として返す。
 * \param spec ユーザ作成RTCが持つコンフィグレーションデータ
 * \return [spec]内のデータがセットされた[RTC_Properties]型データのポインタ
 */
RTC_Properties * Properties_createDefaultProperties(const char **spec);

/*!
 * \brief 引数で指定された[RTC_Properties]型データの中身の削除、メモリ解放の実施。
 * \param prop 削除対象の[RTC_Properties]データ
 *
 * (1)まず、[leaf]を持っていれば、先に削除すべきなので、再帰的に当関数をcallする。<BR>
 * (2)free(prop->leaf)でメモリ解放、[leaf]をNULL、[n_leaf=0]、[name/value/default_value]を全てfree()実施し、最後に[prop]自体をfree()する。
 * \return void
 */
void Properties_delete(RTC_Properties *prop);

/*!
 * \brief RTC_Propertiesデータの[leaf]部分の中身だけ削除、メモリ解放の実施。　(rootに当たる最上位のみ残る） [未使用状態]
 *
 * (1)まず、[leaf]を持っていれば、先に削除すべきなので、Properties_delete()関数をcallする。 <BR>
 * (2)free(prop->leaf)でメモリ解放し、[leaf]をNULL、[n_leaf=0]とする。
 * \param prop 削除対象の[RTC_Properties]データの子ノード[leaf]部分
 * \return void
 */
void Properties_clearLeaf(RTC_Properties *prop);

/*!
 * \brief 引数[next]を[leaf]として、[crr->leaf]に追加セットする。その際、メモリもalocate/reallocする。 最後に、追加後の[n_leaf]を返す。
 *
 * (1)すでに追加先の[crr]が[leaf]を持ってなければ、新規メモリcallocし、持っていれば、[leaf]の数に応じたサイズのreallocをする。 <BR>
 * (2)[crr->leaf]の最後の配列に、[next]をセットする。[n_leaf]をインクリメントする。　最後に、[n_leaf]を返り値として返す。
 * \param crr 現在の[RTC_Properties]型データ(ここの子ノードに[next]が追加される)
 * \param next 追加する[RTC_Properties]型データ(子ノード[leaf]として)
 * \return 追加処理後の合計子ノード数[n_leaf]
 */
int Properties_leaf_append(RTC_Properties *crr, RTC_Properties *next);

/*!
 * \brief 引数のRTC_Properties型の[crr]の[leaf]から、[key]と同じ名前の[name]を持つものを
サーチし、見つかれば、その時の[leaf]を[res]として返す。
 * \param crr 検索対象側の現在の[RTC_Properties]型データ
 * \param key 検索用のKeyとなる、RTC_Properties型ノードの[name]
 * \return 検索で見つかった[RTC_Properties]型データ(子ノード[leaf])
 */
RTC_Properties *Properties_has_key(RTC_Properties *crr, char *key);

/*!
 * \brief 引数の[key]より、現在の[RTC_Properties]型データの階層の適切な位置に、[name/value]をセット(or新規追加)する。
 *
 * (1)引数の[prop]がNullの場合は、Properties_new("root")より、[prop]に「name="root"」として、メモリ確保する。<BR>
 * (2)引数の[key]をデリミタ"."で分割し、[keys]内にそれぞれ格納する。<BR>
 * (3)Properties_has_key()により、[keys]内の各要素を"name"とし、現在のPropertiesの[leaf]内に同一の"name"を持つものがあるかどうかサーチする。<BR>
 * 無ければ、[leaf]として新規作成し、名前は"name"をセットする。さらに、親ポインタ[root]もセットする。<BR>
 * これを、[keys]内の個数(階層の数)だけloopして[leaf]を生成する。<BR>
 * (4)最後に、最後尾の[leaf]の部分には、引数の[value]もセットする。
 * \param prop データセット対象の現在の[RTC_Properties]型データ
 * \param key 登録予定の[name]が階層的に含まれた文字列 (例: "root.leaf.name")
 * \param value 登録予定の[value]
 * \return データセット後の[RTC_Properties]型データ
 */
RTC_Properties * Properties_setDefault(RTC_Properties *prop, char *key,  char *value);

/*!
 * \brief (未実装)
 */
RTC_Properties * Properties_setDefaults(RTC_Properties *prop, char **str, int n);

/*!
 * \brief 引数[key(="root.leaf.name")]をキーとして、引数の[RTC_Properties]型データの[prop]の中から階層的に[leaf]部を探し出し、返す。 [leaf]が無ければ、一つ上の[親の][RTC_Properties]型データを返す。
 *
 *(1)まず、[key]が例として、"exec_cxt.periodic.type"などを想定しているので、"."をデリミタとして、[names]配列にそれぞれ分割する。<BR>
 *(2)上記の[names]の数の分だけforループで、Properties_has_key(prop,names->buffer[]) により、[names]に該当する[leaf]を抽出し、[leaf]を返す。ただし、途中の[leaf]より下の階層の[leaf]に[names]に該当するものが無ければ、一つ上の親の部分を返す。
 * \param prop 検索対象の現在の[RTC_Properties]型データ
 * \param key 検索予定の[name]が階層的に含まれた文字列 (例: "root.leaf.name")
 * \return 検索された[RTC_Properties]型データ
 */
RTC_Properties * Properties_findProperties(RTC_Properties *prop, char *key);

/*!
 * \brief 引数[key(="root.leaf.name")]をキーとして、引数の[RTC_Properties]型データの[prop]の中から、該当する[value]を探し出す。
 *
 * (1)内部で、Properties_findProperties(prop, key)をcallし、分割抽出された[name]から[leaf]を探し出す。 <BR>
 * (2)[leaf]から、[name]に該当する、[value]or[default_value]を[res]にセットし、[res]を返り値として返す。無ければ、「NULL」を返す。
 * \param prop 検索対象の現在の[RTC_Properties]型データ
 * \param key 検索予定の[name]が階層的に含まれた文字列 (例: "root.leaf.name")
 * \return 検索された[RTC_Properties]型データ内の[value]
 */
char * Properties_getProperty(RTC_Properties *prop, char *key);

/*!
 * \brief 引数の[RTC_Properties]型データ[prop]に、引数の[name][value]をセットする
 *
 * (1)find_Properties()関数にて、[prop]内から[name]に該当する[leaf]を探しだす。<BR>
 * (2)[leaf]が無ければ、Properties_setDefault( prop, name, value )の形式で新規に[leaf]を作成し、[name/value]をセットする。[leaf]があれば、[value]の部分だけ上書きする。　最後に、[prop]を返り値として返す。
 * \param prop 登録対象の現在の[RTC_Properties]型データ
 * \param name 登録予定の[name]
 * \param value 登録予定の[value]
 * \return 登録後の[RTC_Properties]型データ
 */
RTC_Properties * Properties_setProperty(RTC_Properties *prop, char *name, char *value);

/*!
 * \brief 引数[key(="root.leaf.name")]をキーとして、引数の[RTC_Properties]型データの[prop]の中から階層的に[leaf]部を探し出し、返す。 [leaf]が無ければ、一つ上の[親の][RTC_Properties]型データを返す。
 * 
 * 内部で、Properties_findProperties(prop, name)をcallするのみ。
 * \param prop 検索対象の現在の[RTC_Properties]型データ
 * \param key 検索予定の[name]が階層的に含まれた文字列 (例: "root.leaf.name")
 * \return 検索された[RTC_Properties]型データ
 */
RTC_Properties * Properties_getNode(RTC_Properties *prop, char *key);

/*!
 * \brief 引数の[format]で指定された文字列フォーマットに従い、引数の[RTC_Properties]型データ[prop]から該当する項目[value]を抽出し、出力用文字列に埋めていき、作成されたものを返す。(NameServer登録用などに使用) 
 *
 * [% : コンテキストの区切り] [n : インスタンス名称] [t : 型名] [m : 型名] [v : バージョン] <BR>
 * [V : ベンダー] [c : カテゴリ] [h : ホスト名] [M : マネージャ名] [p : プロセスID]
 * \param format 作成する文字列のフォーマット (例: "%h.host_cxt/%n.rtc") この「%h,%n」などに該当する値を、引数[prop]から抽出する。
 * \param prop 現在の[RTC_Properties]型データ
 * \return 作成後の文字列
 */
char * Properties_formatString(char *format, RTC_Properties *prop);

/*!
 * \brief 引数の[fname]に指定されたファイル([rtc.conf][RTC名.conf]など)の中身に記述された、プロパティ情報を読み込み、引数の[RTC_Properties]型データ[prop]にセットして返す。
 *
 * (1)fopenで引数[fname]のファイルを開き、１行ずつ読み込み、デリミタ「:」で分割する。<BR>
 * (2)Properties_setDefault( prop, name, value )の形式でセットする。最後に、[prop]を返り値として返す。
 * \param prop 現在の[RTC_Properties]型データ
 * \param fname プロパティ情報読み込み用のファイルのファイル名
 * \return データセット後の[RTC_Properties]型データ
 */
RTC_Properties * Properties_load(RTC_Properties *prop, char *fname);

/*!
 * \brief 引数の[RTC_Properties]型データ[aprop]を[prop]の中に追加する。
 *
 * (*)ごっそり追加でなく、既存のProperties[prop]に足りないものだけ、[aprop]から追加セットされる。<BR>
 * (1)findProperties(prop, aprop->leaf->name)にて、同一[name]のleafが既に存在しているかを確認する。 <BR>
 * (2)[leaf]が無ければ、leaf_append()により、追加する。既に存在していた場合は、[value]のみを上書きし、再帰的に当関数をcallする。 <BR>
 * (3)[prop]を返り値として返す。
 * \param prop 現在の[RTC_Properties]型データ
 * \param aprop 追加対象の[RTC_Properties]型データ
 * \return 追加後の[RTC_Properties]型データ
 */
RTC_Properties * Properties_appendProperties(RTC_Properties *prop, RTC_Properties *aprop);

/*!
 * \brief RTC_Propertiesデータの中身の[name][value]をダンプする。  引数の[idx]はleafの階層の深さを示し、初期call時は"0"。
 *
 * (1)fprintf()にて、[name][value]をダンプする。<BR>
 * (2)leafを複数持つ場合、forループにより、print_index()をcall後に、[leaf]を引数に当関数を再帰的にcallする。
 * \param prop デバッグ対象の[RTC_Properties]型データ
 * \param idx leafの階層の深さ
 * \return void
 */
void Properties_dumpProperties(RTC_Properties *prop, int idx);

#endif /* RTM_PROPERTIES_H */


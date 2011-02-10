/**




*/
#ifndef __FUNCTION_CORBA_ANY_H__
#define __FUNCTION_CORBA_ANY_H__


/*!
 * @if jp
 * @brief CORBA_any型データ用にメモリを確保し、TypeCodeとreleaseフラグをセットする。
 * @else
 * @brief allocate memory for CORBA_any data, and set TypeCode data and Release_Flag.
 * @endif
 * @param clear clear Flag
 * @return void
 */
void 	CORBA_any_alloc(CORBA_any *, struct CORBA_TypeCode_struct *, int32_t clear);

/*!
 * @if jp
 * @brief CORBA_any型データ内のコンテンツを全てクリアする。
 * @else
 * @brief clear all contents in CORBA_any data array.
 * @endif
 * @param any CORBA_any data
 * @return void
 */
void 	CORBA_any_clear(CORBA_any *any);

/*!
 * @if jp
 * @brief CORBA_any型データ内に、引数のコンテンツデータをセットする。
 * @else
 * @brief set contents data to CORBA_any data array.
 * @endif
 * @param data contents data
 * @param len length of array
 * @return void
 */
void    CORBA_any_set_value(CORBA_any*, struct CORBA_TypeCode_struct *, char *data, int32_t len);

/*!
 * @if jp
 * @brief TypeCodeに応じた、CORBA_any型データ内のコンテンツデータを返す。
 * @else
 * @brief return contents data releated with TypeCode from CORBA_any data array. 
 * @endif
 * @return reference of contents data
 */
void * 	CORBA_any_get_value(CORBA_any*);
	
/*!
 * @if jp
 * @brief CORBA_any型データ内のエンコード済みのCORBA_any_val型コンテンツデータを返す。また、その配列長をセットする。
 * @else
 * @brief return encoded contents data in CORBA_any data array.
 * @endif
 * @param any CORBA_any data
 * @param len length of CORBA_any_val data array
 * @return encoded data
 */
char * 	CORBA_any_get_encoded(CORBA_any *any, int32_t *len);

/*!
 * @if jp
 * @brief CORBA_any型データ内のコンテンツに例外情報のデータをセットする。
 * @else
 * @brief set contents exception data to CORBA_any data array.
 * @endif
 * @param any CORBA_any data
 * @param tc CORBA_TypeCode data
 * @param value contents exception data
 * @param release release Flag
 * @return void
 */
void 	CORBA_any_set_exception_value(CORBA_any *any, struct CORBA_TypeCode_struct * tc, void *value, CORBA_boolean release);

/*!
 * @if jp
 * @brief CORBA_any型データ内のコンテンツに例外情報のデータをセットする。
 * @else
 * @brief set contents exception data to CORBA_any data array.
 * @endif
 * @param any target of CORBA_any data
 * @param src buffer of CORBA_any data
 * @return void
 */
void 	CORBA_any_set_exception(CORBA_any *any, CORBA_any *src);


#endif

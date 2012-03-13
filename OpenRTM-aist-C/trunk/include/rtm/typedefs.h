/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file typedefs.h
 * \brief 各種データ型を環境依存対応のためtypedefしているファイル
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_TYPEDEFS_H
#define RTM_TYPEDEFS_H

typedef char 		RTC_Char;
typedef double		RTC_Double;
typedef float 		RTC_Float;
typedef int32_t 	RTC_Long;
typedef long double 	RTC_LongDouble;
typedef int64_t 	RTC_LongLong;
typedef int8_t 		RTC_Octet;
typedef int16_t 	RTC_Short;
typedef uint32_t 	RTC_ULong;
typedef uint64_t 	RTC_ULongLong;
typedef uint16_t 	RTC_UShort;
#if 0
typedef wchar_t 	RTC_WChar;
typedef wchar_t *	RTC_WString;
#endif

typedef int8_t 		RTC_Boolean;
typedef char * 		RTC_String;



#endif /* RTM_TYPEDEFS_H */

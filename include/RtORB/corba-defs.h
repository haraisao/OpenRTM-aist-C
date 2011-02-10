/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*

 Simple CORBA Implementation for x86 (Big Endian)
  
*/

/*!
 * @file corba-defs.h
 * @if jp
 * @brief CORBA definition.
 * @else
 * @brief CORBA definition.
 * @endif
 * @author National Institute of Advanced Industrial Science and Technology (AIST)
*/

#ifndef __CORBA_DEFS_H__
#define __CORBA_DEFS_H__

#include <stdint.h>

#if USE_THREAD
#include <pthread.h>
#endif
#include <RtORB/list.h>
#include <RtORB/array.h>
#include <RtORB/hashtable.h>
#include <RtORB/typecode.h>

#ifdef __cplusplus
extern "C"
{
#endif 

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* for experimental use */
#ifndef CORBA_VPVID
#define CORBA_VPVID	0xfffff
#endif

#define CORBA_I_ARG_IN		0
#define CORBA_I_ARG_OUT		1
#define CORBA_I_ARG_INOUT	2

#define CORBA_OBJECT_NIL	NULL


/*! enum IOP_ServiceId (正常終了/ユーザ例外/システム例外) */
enum CORBA_ReplyStatusType{
   CORBA_NO_EXCEPTION, CORBA_USER_EXCEPTION, CORBA_SYSTEM_EXCEPTION, 
   CORBA_LOCATION_FORWARD,CORBA_LOCATION_FORWARD_PERM, NEEDS_ADDRESSING_MODE
};

/***  Basic Data Type **/
typedef char   CORBA_char;
typedef int16_t  CORBA_short;
typedef int32_t  CORBA_long;
typedef int64_t  CORBA_long_long;
typedef unsigned char  CORBA_unsigned_char;
typedef uint16_t CORBA_unsigned_short;
typedef uint32_t CORBA_unsigned_long;
typedef uint64_t CORBA_unsigned_long_long;
typedef float    CORBA_float;
typedef double   CORBA_double;
typedef long double CORBA_long_double;
typedef char     CORBA_octet;
typedef short    CORBA_wchar;
typedef unsigned char CORBA_boolean;
typedef char *   CORBA_string;
typedef short *  CORBA_wstring;

typedef unsigned char boolean;

extern const uint32_t RTORB_ORB_TYPE;

#define CORBA_ANY_MAXBUF MaxMessageSize  

struct CORBA_Object_struct;

/*!
 * @union CORBA_any_val
 * @brief CORBA_any_val (TODO)
 * @param val_bool (TODO)
 * @param val_octet (TODO)
 * @param val_char (TODO)
 * @param val_ulong (TODO)
 * @param val_str (TODO)
 * @param val_obj (TODO)
 * @param val_except (TODO)
 * @param val_encoded (TODO)
 */
typedef union
{
  CORBA_boolean val_bool;
  CORBA_octet val_octet;
  CORBA_char  val_char;
  CORBA_unsigned_long val_ulong;

  char * val_str;
  struct CORBA_Object_struct * val_obj;
  void * val_except;

  /* tk_struct */
  struct val_t {
    int32_t   len;
    char * data;
  } val_encoded;
} CORBA_any_val;

/*!
 * @struct CORBA_any
 * @brief CORBA_any CORBA Any type data
 * @param _type Identified ID (CORBA_Type_Code)
 * @param _val adress of data
 * @param _release data release flag (TRUE:release)
 */
typedef struct CORBA_any {
  struct CORBA_TypeCode_struct *_type;
  CORBA_any_val *_val;
  CORBA_unsigned_long _release;
} CORBA_any ;


/*  Sequence */
/*!
 * @struct CORBA_SequenceBase
 * @brief CORBA_SequenceBase structure
 * @param _maximum max count of sequence array
 * @param _length count of sequence array
 * @param _buffer address of data
 * @param _release data release flag (TRUE:release)
 */
typedef struct{
  uint32_t _maximum;
  uint32_t _length;
  void  **_buffer;
  uint32_t  _release;
} CORBA_SequenceBase;

/*!
 * @struct CORBA_Sequence_Octet
 * @brief CORBA_Sequence_Octet structure
 * @param _length count of sequence array
 * @param _maximum max count of sequence array
 * @param _buffer address of data
 * @param _release data release flag (TRUE:release)
 */
typedef struct {
  uint32_t _length;
  uint32_t _maximum;
  unsigned char *_buffer;
  uint32_t  _release;
} CORBA_Sequence_Octet;

typedef CORBA_Sequence_Octet CORBA_String;

/*!
 * @struct CORBA_Environment
 * @brief CORBA_Environment (Exception Information)
 * @param _major Exception type (ex: CORBA_NO_EXCEPTION, CORBA_USER_EXCEPTION, CORBA_SYSTEM_EXCEPTIO ...)
 * @param _repo_id Exception Report ID
 * @param _params Exception parameter
 * @param _cpp_flag flag for C++ Interface
 */
typedef struct CORBA_Environment{
  uint32_t _major; /* Exception type */
  unsigned char *_repo_id;
  CORBA_any _params; 
  uint32_t _cpp_flag; /* flag for C++ Interface */
} CORBA_Environment;

/*-----------------------------------------------------------------*/
/*!
 * @struct CORBA_Ref
 * @brief CORBA reference
 * @param key object key
 * @param url CORBA url
 */
typedef struct CORBA_Ref{
  char *key;
  char *url;
} CORBA_Ref;

/*!
 * @struct CORBA_Config
 * @brief CORBA_Config (TODO)
 * @param server_id (TODO)
 * @param orb_id (TODO)
 * @param listenEndpoints (TODO)
 * @param flag_propietary_activation (TODO)
 * @param init_ref (TODO)
 * @param default_init_ref (TODO)
 * @param port (TODO)
 */
typedef struct CORBA_Config {
   char *server_id;
   char *orb_id;
   char *listenEndpoints;
   uint32_t flag_propietary_activation;
   PtrList  *init_ref;
   char *default_init_ref;
   uint16_t port;
}CORBA_Config;

/*-----------------------------------------------------------------*/
/*   ORB  */
/*!
 * @struct CORBA_ORB_struct
 * @brief ORB structure in RtORB
 * @param _id (Unused)
 * @param hostname ORBを起動したホスト名(IP address)
 * @param cfg 初期設定のコマンド引数などの処理用
 */
typedef struct CORBA_ORB_struct{
  unsigned char *_id;

  char *hostname;
  CORBA_Config cfg;

} CORBA_ORB_struct;

typedef CORBA_ORB_struct * CORBA_ORB;

typedef  int32_t  CORBA_TCKind;
typedef  char *CORBA_RepositoryId;
typedef  char *CORBA_Identifier;
typedef  char *CORBA_Visibility;
typedef  char *CORBA_ValueModifier;

/*!
 * @struct CORBA_TypeCode_struct
 * @brief CORBA_TypeCode_struct (TODO)
 * @param parents (TODO)
 * @param kind (TODO)
 * @param repository_id (TODO)
 * @param identifier (TODO)
 * @param member_count (TODO)
 * @param member_name (TODO)
 * @param member_type (TODO)
 * @param member_label (TODO)
 * @param discriminator (TODO)
 * @param default_index (TODO)
 * @param length the number of elements count
 * @param content_type (TODO)
 * @param fixed_digits (TODO)
 * @param fixed_scale (TODO)
 * @param member_visibility (TODO)
 * @param type_modifier (TODO)
 * @param concrete_base_type (TODO)
 * @param size (TODO)
 * @param alignment (TODO)
 */
typedef struct CORBA_TypeCode_struct{
  void *			parents;
  CORBA_TCKind			kind;
  CORBA_RepositoryId		repository_id;
  CORBA_Identifier		identifier; 
  uint32_t		member_count; 	/* struct, union, enum, value, exception, event */
  CORBA_Identifier  		*member_name; 	/* struct, union, enum, value, exception, event */
  struct CORBA_TypeCode_struct 	**member_type; 	/* struct, union, value, exception, event */
  int32_t 			*member_label; 	/* union */
  struct CORBA_TypeCode_struct 	*discriminator; /* union */
  int32_t   			default_index;  /* union */
  uint32_t   		length; 	/* string, wstring, sequence, array */ 
  struct CORBA_TypeCode_struct 	*content_type;  /* sequence, array, value_box, alias */ 
  uint16_t		fixed_digits;   /* fixed */
  int16_t				fixed_scale;    /* fixed */
  CORBA_Visibility		*member_visibility;  	/* value, event */
  CORBA_ValueModifier		type_modifier;  	/* value, event */
  struct CORBA_TypeCode_struct 	*concrete_base_type;  	/* value, event */
  int16_t 			size;
  int16_t				alignment;

}CORBA_TypeCode_struct;

typedef CORBA_TypeCode_struct *CORBA_TypeCode ;

/*!
 * @struct CORBA_IArg
 * @brief CORBA_IArg structure
 * @param tc CORBA Type Code
 * @param io flag (IN/OUT/INOUT)
 * @param name 
 */
typedef struct CORBA_IArg {
  CORBA_TypeCode tc;
  unsigned char  io;
  char *name;
}CORBA_IArg;

/*!
 * @struct CORBA_Class_Method
 * @brief CORBA_Class_Method (TODO)
 * @param name (TODO)
 * @param retval (TODO)
 * @param in_argc (TODO)
 * @param in_argv (TODO)
 * @param n_exceptinfo (TODO)
 * @param exceptinfo (TODO)
 */
typedef struct CORBA_Class_Method{
  char *name;
  CORBA_TypeCode retval;
  int32_t in_argc;
  CORBA_IArg *in_argv;
  int32_t n_exceptinfo;
  CORBA_TypeCode *exceptinfo;
}CORBA_Class_Method;

/*!
 * @struct CORBA_Class_Impl
 * @brief CORBA_Class_Impl (TODO)
 * @param tc (TODO)
 * @param name (TODO)
 * @param n_methods (TODO)
 * @param methods (TODO)
 * @param n_base_types (TODO)
 * @param base_types (TODO)
 */
typedef struct{
  CORBA_TypeCode tc;
  char *name;
  int32_t n_methods; 
  struct CORBA_Class_Method *methods;
  int32_t n_base_types;
  char **base_types;
} CORBA_Class_Impl;

extern const CORBA_TypeCode_struct TC_null_struct;
extern const CORBA_TypeCode_struct TC_void_struct;
extern const CORBA_TypeCode_struct TC_short_struct;
extern const CORBA_TypeCode_struct TC_long_struct;
extern const CORBA_TypeCode_struct TC_longlong_struct;
extern const CORBA_TypeCode_struct TC_ushort_struct;
extern const CORBA_TypeCode_struct TC_ulong_struct;
extern const CORBA_TypeCode_struct TC_ulonglong_struct;
extern const CORBA_TypeCode_struct TC_float_struct;
extern const CORBA_TypeCode_struct TC_double_struct;
extern const CORBA_TypeCode_struct TC_longdouble_struct;
extern const CORBA_TypeCode_struct TC_boolean_struct;
extern const CORBA_TypeCode_struct TC_char_struct;
extern const CORBA_TypeCode_struct TC_wchar_struct;
extern const CORBA_TypeCode_struct TC_octet_struct;
extern const CORBA_TypeCode_struct TC_any_struct;
extern const CORBA_TypeCode_struct TC_TypeCode_struct;
extern const CORBA_TypeCode_struct TC_Object_struct;
extern const CORBA_TypeCode_struct TC_string_struct;
extern const CORBA_TypeCode_struct TC_wstring_struct;
extern const CORBA_TypeCode_struct TC_ValueBase_struct;
extern const CORBA_TypeCode_struct TC_Component_struct;
extern const CORBA_TypeCode_struct TC_Home_struct;
extern const CORBA_TypeCode_struct TC_EventBase_struct;

#define TC_null		 ((CORBA_TypeCode)&TC_null_struct)
#define TC_void   	 ((CORBA_TypeCode)&TC_void_struct)
#define TC_CORBA_short	 ((CORBA_TypeCode)&TC_short_struct)
#define TC_CORBA_long		 ((CORBA_TypeCode)&TC_long_struct)
#define TC_CORBA_long_long	 ((CORBA_TypeCode)&TC_longlong_struct)
#define TC_CORBA_ushort	 ((CORBA_TypeCode)&TC_ushort_struct)
#define TC_CORBA_unsigned_short	 ((CORBA_TypeCode)&TC_ushort_struct)
#define TC_CORBA_ulong	 ((CORBA_TypeCode)&TC_ulong_struct)
#define TC_CORBA_unsigned_long	 ((CORBA_TypeCode)&TC_ulong_struct)
#define TC_CORBA_ulonglong	 ((CORBA_TypeCode)&TC_ulonglong_struct)
#define TC_CORBA_unsigned_long_long	 ((CORBA_TypeCode)&TC_ulonglong_struct)
#define TC_CORBA_float	 ((CORBA_TypeCode)&TC_float_struct)
#define TC_CORBA_double	 ((CORBA_TypeCode)&TC_double_struct)
#define TC_CORBA_long_double	 ((CORBA_TypeCode)&TC_longdouble_struct)
#define TC_CORBA_boolean	 ((CORBA_TypeCode)&TC_boolean_struct)
#define TC_CORBA_char		 ((CORBA_TypeCode)&TC_char_struct)
#define TC_CORBA_wchar	 ((CORBA_TypeCode)&TC_wchar_struct)
#define TC_CORBA_octet	 ((CORBA_TypeCode)&TC_octet_struct)
#define TC_CORBA_any		 ((CORBA_TypeCode)&TC_any_struct)
#define TC_CORBA_TypeCode	 ((CORBA_TypeCode)&TC_TypeCode_struct)
#define TC_CORBA_Object	 ((CORBA_TypeCode)&TC_Object_struct)
#define TC_CORBA_string	 ((CORBA_TypeCode)&TC_string_struct)
#define TC_CORBA_wstring	 ((CORBA_TypeCode)&TC_wstring_struct)
#define TC_CORBA_ValueBase	 ((CORBA_TypeCode)&TC_ValueBase_struct)
#define TC_CORBA_Component	 ((CORBA_TypeCode)&TC_Component_struct)
#define TC_CORBA_Home		 ((CORBA_TypeCode)&TC_Home_struct)
#define TC_CORBA_EventBase	 ((CORBA_TypeCode)&TC_EventBase_struct)

/*  For compatible to ORBit2 */
#define TC_CORBA_char_struct	 TC_char_struct
#define TC_CORBA_wchar_struct	 TC_wchar_struct
#define TC_CORBA_boolean_struct	 TC_boolean_struct
#define TC_CORBA_octet_struct	 TC_octet_struct
#define TC_CORBA_short_struct	 TC_short_struct
#define TC_CORBA_unsigned_short_struct	 TC_ushort_struct
#define TC_CORBA_long_struct	 TC_long_struct
#define TC_CORBA_unsigned_long_struct	 TC_ulong_struct
#define TC_CORBA_float_struct	 TC_float_struct
#define TC_CORBA_double_struct	 TC_double_struct
#define TC_CORBA_string_struct	 TC_string_struct
#define TC_CORBA_wstring_struct	 TC_wstring_struct
#define TC_CORBA_TypeCode_struct	 TC_TypeCode_struct
#define TC_CORBA_Object_struct	 TC_Object_struct
#define TC_CORBA_any_struct	 TC_any_struct

/*! enum IOP_ServiceId (SIMPLE:have only 1 param, COMLEX:have some params) */
enum { PLT_NOT_SUPPORTED = -1, PLT_NONE, PLT_SIMPLE, PLT_COMPLEX,};

int PARAM_LIST_TYPE(unsigned int kind);

#ifdef __cplusplus
}
#endif 


#endif

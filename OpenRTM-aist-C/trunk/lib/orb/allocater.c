/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *  RtORB Allocater
 *
 *
 */
/*!
 * @file allocater.c
 * @if jp
 * @brief RtORB Allocater functions.
 * @else
 * @brief RtORB Allocater functions.
 * @endif
 * @author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#define _GNU_SOURCE
#include <string.h>
#include <RtORB/corba.h>

#ifdef DEBUG_MALLOC
#define DEBUG_MALLOC_INFO 1
#endif
/********* allocater *******/
void *
RtORB__alloc(int32_t size, const char *info){
  void *retval = (void *)malloc(size * sizeof(char));
  memset(retval, 0, size);
#if DEBUG_MALLOC_INFO
  if(info) fprintf(stderr, "malloc in %s: (0x%x)\n", info, (int)retval);
#endif

  return retval;
}

void *
RtORB__calloc(int32_t size, int32_t n, const char *info){
  void *retval = (void *)calloc(size, n);
#if DEBUG_MALLOC_INFO
  if(info) fprintf(stderr, "calloc in %s: (0x%x)\n", info, (int)retval);
#endif

  return retval;
}

void *
RtORB__realloc(void *ptr, int32_t size, const char *info){
  void *retval = (void *)realloc(ptr, size);
#if DEBUG_MALLOC_INFO
  if(info) fprintf(stderr, "realloc in %s: (0x%x)\n", info, (int)retval);
#endif

  return retval;
}

void *
RtORB_alloc_by_typecode(CORBA_TypeCode tc, int32_t len, const char *info){
  SKIP_ALIAS(tc);
  switch(tc->kind){
    case tk_null:
    case tk_void:
      return NULL;
    default:
      return (void *)RtORB_alloc(size_of_typecode(tc, F_DEMARSHAL) * len, info);
  }
}

void 
RtORB__free(void *val, const char *info){
  if(!val) return;
#if DEBUG_MALLOC_INFO
  if(info) fprintf(stderr, "FREE in %s: (0x%x)\n", info, (int)val);
#endif
  free(val);
  return;
}

void 
RtORB_free_by_typecode(CORBA_TypeCode tc, void *val, int32_t flag, int32_t cpp_flag){
   if (!val) return;
   SKIP_ALIAS(tc);

   switch(tc->kind){
      case tk_null:
      case tk_void:
	 return;

      case tk_octet:
      case tk_char:
      case tk_boolean:
	 break;

      case tk_short:
      case tk_ushort:
	 break;
	
      case tk_long:
      case tk_ulong:
	 break;

      case tk_float:
	 break;

      case tk_double:
	 break;

      case tk_string:
         if(cpp_flag == 0){
           RtORB_free(*(char **)val, "RtORB_free_by_typecode(string)");
         }
	 break;

      case tk_sequence:
	 {
	   int32_t i;
	   int align=0;
           CORBA_SequenceBase *sb = (CORBA_SequenceBase *)val;

           if(val && sb->_length > 0){
	     char *buf = (char *)sb->_buffer;
             void **tmp=0;
	     CORBA_TypeCode _tc = tc->member_type[0];
	     int32_t len = size_of_typecode(_tc, F_DEMARSHAL);
	     int32_t base = align_of_typecode(_tc, F_DEMARSHAL);

	     for(i=0;i<sb->_length;i++){
	       Address_Alignment(&align, base);
               tmp = (void **)((long)buf + align); 
               RtORB_free_by_typecode(_tc, tmp, 0, cpp_flag);
	       align += len ;
	     }
             if(sb->_buffer){
               RtORB_free(sb->_buffer, "RtORB_free_by_typecode(sequence)");
             }
             sb->_buffer = NULL;
           }
	 }
	 break;

      case tk_except:
      case tk_struct:
	 {
	   int32_t i;
	   int align=0;
	   int32_t tc_size=0;
	   void *tmp;
	   CORBA_TypeCode _tc;

	   tmp = val;

	   for(i=0;i< tc->member_count;i++){
             _tc = tc->member_type[i];
	     tc_size = size_of_typecode(_tc, F_DEMARSHAL);
             Address_Alignment(&align, align_of_typecode(_tc, F_DEMARSHAL));
	     tmp = (char *)val + align;
             RtORB_free_by_typecode(_tc, tmp, 0, cpp_flag);
             align += tc_size;
	   }
	 }
	 break;
      case tk_objref:
	 {
	    CORBA_Object obj = *(CORBA_Object *)val;

	    if(!obj) { break;}
            if(cpp_flag == 0){
	      CORBA_Object_free(obj);
            }else{
#if 0
	      if(obj->release) CORBA_Object_free(obj);
#endif
            }
	 }
	 break;
      case tk_any:
	{
	  if (!val) { break; }
	  CORBA_any_clear((CORBA_any *)val);

	  break;
	}
      default: 
	 break;
  }
  if(flag) RtORB_free(val, "RtORB_free_by_typecode");
  return;
}

/*
 *  RtORB_Arguments_free:
 *
 *   See deMarshal_Arg function(giop-marshal.c)
 */
void 
RtORB_Arguments_free(void **argv, int32_t in_argc, CORBA_IArg *in_argv){
  int32_t i;

  for(i=0;i<in_argc;i++){
    if(in_argv[i].io == CORBA_I_ARG_IN ){
      RtORB_free_by_typecode(in_argv[i].tc, argv[i], 1, 0);
    }else{
      RtORB_free(argv[i], "RtORB_Arguments_free");
    }
  }
  return;
}

/*!
 * @if jp
 * @brief result値に対して、確保したメモリ領域を開放する
 * @else
 * @brief Release allocated memory releted to 'result'.
 * @endif
 * @param tc CORBA Type Code
 * @param result retval(CORBA_Class_Method)
 * @return void
 */
void
RtORB_Result__free(CORBA_TypeCode tc, void **result, int cpp_flag){
  SKIP_ALIAS(tc);

  switch(tc->kind){
  case tk_null:
  case tk_void:
    return;

  case tk_octet:
  case tk_short:
  case tk_ushort:
  case tk_long:
  case tk_ulong:
#if 0
  case tk_longlong:
  case tk_ulonglong:
#endif
  case tk_float:
  case tk_double:
    RtORB_free(result, "Result_free: simple");
    return;

  case tk_struct:
    RtORB_free_by_typecode(tc, (void*)(*result), 1, cpp_flag);
    return;
  case tk_sequence:
    RtORB_free_by_typecode(tc, (void*)(*result), 1, cpp_flag);
    return;

  case tk_string:
    RtORB_free_by_typecode(tc, (void*)result, 0, 0);
    return;

  case tk_objref:
    if(cpp_flag == 0){
      RtORB_free_by_typecode(tc, (void*)result, 0, cpp_flag);
    }
    return;

  default:
    break;
  }

  if ( !CORBA_TypeCode_is_fixed_size(tc) && cpp_flag == 0) {
    RtORB_free_by_typecode(tc, result[0], 1, cpp_flag);
    RtORB__free(result, "RtORB_Result_free");
  }
  return;
}

/********************************/
/*
 * void *
 * RtORB_typecode_alloc(CORBA_TypeCode)
 *
 */
void *
RtORB_typecode_alloc(CORBA_TypeCode tc){
  return (void *)RtORB_calloc(size_of_typecode(tc, F_DEMARSHAL), 1, "RtORB_typecode_alloc");
}

/*
 * void *
 * RtORB__allocbuf(CORBA_TypeCode, int32_t )
 *
 */
void *
RtORB__allocbuf(CORBA_TypeCode tc, int32_t length){
  return RtORB_alloc_by_typecode(tc->member_type[0], length, "RtORB__allocbuf");
}

/*
 * void *
 * RtORB_sequence_allocbuf(CORBA_TypeCode, int32_t )
 *
 */
void *
RtORB_sequence_allocbuf(CORBA_TypeCode tc, int32_t length){
  return RtORB_alloc_by_typecode(tc->member_type[0], length, "RtORB_sequence_allocbuf");
}


/*    Strdup  */

char * RtORB__strdup(const char *str, const char *info){
   char *retval;
   retval = strdup(str);
#if DEBUG_MALLOC_INFO
   if(info) fprintf(stderr, "strdup in %s: (0x%x) : %s\n", info, (int)retval, str);
#endif
   return retval;

}

/*!
 * @if jp
 * @brief strndupにより文字列strを最大文字数'n'個までメモリ領域に確保する(文字列のコピー)。デバッグモードの場合、infoをメッセージとして出力する
 * @else
 * @brief Allocate memory and set 'str' to it. If DEBUG mode, output messages. (strndup)
 * @endif
 * @param str Strings
 * @param n max character count
 * @param info message
 * @return memory address
 */
#if !defined(Darwin)

char * RtORB__strndup(const char *str, int32_t n, const char *info){
   char *retval;
   retval = strndup(str, n);
#if DEBUG_MALLOC_INFO
   if(info) fprintf(stderr, "strndup in %s: (0x%x)\n", info, (int)retval);
#endif
   return retval;
}

#else
char *strndup(const char *str, size_t n)
{
  char *retval;
  retval = malloc(sizeof(char) * (n+1));
  memset(retval, 0,  (n+1));
  strncpy(retval, str, n);
  return retval;
}

char * RtORB__strndup(const char *str, int32_t n, const char *info){
  char *retval;
  retval = malloc(sizeof(char) * (n+1));
  memset(retval, 0,  (n+1));
  strncpy(retval, str, n);
#if DEBUG_MALLOC_INFO
  if(info) fprintf(stderr, "strndup in %s: (0x%x)\n", info, (int)retval);
#endif
  return retval;
}

#endif

/*!
 * @if jp
 * @brief TypeCodeに応じたメモリ確保処理。
 * @else
 * @brief Allocate memory related with TypeCode.
 * @endif
 * @param tc CORBA_TypeCode data
 * @return allocated memory's address
 */

void ** 
Result_alloc(CORBA_TypeCode tc)
{
  void **buf = NULL;
  SKIP_ALIAS(tc);

  if (!tc) { return NULL; }

  switch(tc->kind) {
  case tk_null:
  case tk_void:
    return NULL;
  case tk_octet:
    buf = RtORB_alloc(sizeof(CORBA_octet), "Result_alloc:octet");;
    break;
  case tk_short:
  case tk_ushort:
    buf = RtORB_alloc(sizeof(CORBA_short), "Result_alloc:short");;
    break;
  case tk_long:
  case tk_ulong:
    buf = RtORB_alloc(sizeof(CORBA_long), "Result_alloc:long");;
    break;
#if 0
  case tk_longlong:
  case tk_ulonglong:
    buf = RtORB_alloc(sizeof(CORBA_longlong), "Result_alloc:longlong");;
    break;
#endif
  case tk_float:
    buf = RtORB_alloc(sizeof(CORBA_float), "Result_alloc:float");;
    break;
  case tk_double:
    buf = RtORB_alloc(sizeof(CORBA_double), "Result_alloc:double");;
    break;
  default:
    buf = (void**)RtORB_alloc(sizeof(void *), "Result_alloc(default)");
    break;
  }
  return buf;
}


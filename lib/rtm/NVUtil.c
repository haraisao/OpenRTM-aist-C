/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file NVUtil.c
 * \brief NameValue型データの処理を扱うUtilityファイル。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/OpenRTM.h>

/*
 (Uncalled).
*/
SDOPackage_NVList * 
NVUtil_new()
{
  SDOPackage_NVList * res;
  res = ( SDOPackage_NVList *)malloc(sizeof(SDOPackage_NVList));
  memset(res, 0, sizeof(SDOPackage_NVList));
  return res;
}


/*
 Called from [<Comp.c> MyModuleInit()].
*/
void 
NVUtil_dump(SDOPackage_NVList nv)
{
  int i;
  for(i = 0; i < nv._length; i++) 
  {
     fprintf(stderr, " \"%s\":\t\t%s\n"
                   ,nv._buffer[i].name,  nv._buffer[i].value._val->val_str);
  }
  return;
}


void NVUtil_setNV(SDOPackage_NameValue *nv, char *name, char *value)
{
  /*
    struct SDOPackage_NameValue_type {
      CORBA_string name;
      CORBA_any value;
    };
  */

  /* Only [tk_string] in OpenRTM-aist-C */
  CORBA_any_alloc(&nv->value, TC_CORBA_string, 1); /* CORBA_any */
  nv->name = strdup(name);
  nv->value._val->val_str = strdup(value);

  return;
}


void NVUtil_dupNV(SDOPackage_NameValue *dest, SDOPackage_NameValue *src)
{

  CORBA_any_alloc(&dest->value, src->value._type, 1);  

  /* Only [tk_string] in OpenRTM-aist-C */
  if(src->value._type->kind == tk_string){
    dest->name = strdup(src->name);
    dest->value._val->val_str = strdup(src->value._val->val_str);
  } else {
    dest->name = NULL;
    dest->value._val->val_str = NULL;
  }

  return;
}


void NVUtil_freeNV(SDOPackage_NameValue *nv)
{
  free(nv->name);
  CORBA_any_clear(&nv->value); /* CORBA_any */

  return;
}


void NVUtil_dupNVList(RTC_NVList* dest, RTC_NVList src)
{
  /*
    typedef struct CORBA_sequence_SDOPackage_NameValue_type {
      CORBA_unsigned_long _maximum;
      CORBA_unsigned_long _length;
      SDOPackage_NameValue* _buffer;
      CORBA_unsigned_long _release;
    } CORBA_sequence_SDOPackage_NameValue;
    typedef CORBA_sequence_SDOPackage_NameValue SDOPackage_NVList;
    typedef SDOPackage_NVList RTC_NVList;
  */

  int i;

  dest->_length = src._length;
  dest->_maximum = src._maximum;
  dest->_release = src._release;

  if(dest->_length > 0){
    dest->_buffer = RTC_NVList_allocbuf(dest->_length);
    for(i = 0; i < dest->_length; i++){
      NVUtil_dupNV(&dest->_buffer[i], &src._buffer[i]);
    }
  }

  return;
}


void NVUtil_freeNVList(RTC_NVList* nvlist)
{
  int i;
  for(i = 0; i < nvlist->_length; i++){
    NVUtil_freeNV(&nvlist->_buffer[i]);
  }

  nvlist->_length = nvlist->_maximum = 0;
  free(nvlist->_buffer);
  nvlist->_buffer = NULL;

  return;
}


void NVUtil_appendNVList(RTC_NVList* nvlist, char *name, char *value)
{
  int i;
  RTC_NVList temp;
  
  /* Duplicate to temporary and free original for reallocation */
  NVUtil_dupNVList(&temp, *nvlist);
  NVUtil_freeNVList(nvlist);

  /* Create new NVList */
  nvlist->_length = temp._length + 1;
  if (nvlist->_length < temp._maximum) nvlist->_maximum = temp._maximum;
  else nvlist->_maximum = nvlist->_length;
  nvlist->_release = temp._release;
    /* Reallocate and set data*/
  nvlist->_buffer = RTC_NVList_allocbuf(nvlist->_length);
  for(i = 0; i < (nvlist->_length - 1); i++){
    NVUtil_dupNV(&nvlist->_buffer[i], &temp._buffer[i]);
  }
    /* Append NameValue(arg) */
  NVUtil_setNV(&nvlist->_buffer[nvlist->_length - 1], name, value);
  
  /* Delete temporary */
  NVUtil_freeNVList(&temp);

  return;
}


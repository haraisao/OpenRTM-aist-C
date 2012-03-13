/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Utils.c
 * \brief 各種文字列操作用Utilityファイル。主に、Properties操作において使用される。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/Utils.h>


/*
 Called from [split_string()].
*/
string_sequence *
new_string_sequence(int len)
{
  string_sequence *res;
  res = (string_sequence *)malloc(sizeof(string_sequence));
  if(len > 0){
    res->buffer = (char **)malloc(sizeof(char *) * len);
    memset(res->buffer, 0, sizeof(char *) * len);
    res->length = len;
    res->maximum = len;
  }else{
    res->buffer = NULL;
    res->length = 0;
    res->maximum = 0;
  }
  return res;
}


/*
 Called from [RTC_Manager_procComponentArgs(), RTC_Manager_initNaming(),
              RTC_NamingBase_bindObject(), Properties_setDefault(), Properties_load()].
*/
void
free_string_sequence(string_sequence *seq)
{
  int i;

  if(seq != NULL){
    for(i=0;i<seq->length;i++){
      free(seq->buffer[i]);
    }
  }
  free(seq);
}


/*
  Count deliminators in 'str'.
 Called from [RTC_Manager_procComponentArgs(), RTC_NamingBase_bindObject(),
              Properties_load(), split_string()].
*/
int
count_delim(char *str, const char delim)
{
  int res=0;
  int i,len;

  if(str != NULL){
    len = strlen(str);
    for(i=0; i< len; i++){
      if(str[i] == delim) res += 1;
    }
  } 

  return res;
}


/*
  Trim String. (Check [space]['\n'], and append ['\0'] )
 Called from [split_string()].
*/
char *
trim_string(char *str)
{
  char *res = NULL;
  char *tmp = NULL;
  int i;
  int count = 0;;
  int len = strlen(str);

  /* Check whether [space]['\n'] */
  for(i = 0; i < len; i++) {
    if(tmp == NULL){
      if(isblank(str[i]) != 0) continue;  /* If str[i] == Blank, return TRUE(!0)  */
      tmp = &str[i];  /* set first character's pointer */
      count = 1;
    }else{
      if(isblank(str[i]) != 0 || str[i] == '\n'){  /* if Blank or '\n' ... */
        /* finish triming */
        res = (char *)malloc(count + 1);
        strncpy(res, tmp, count);
        res[count] = '\0'; /* '\0' : end_of_string_code */
        return res;
      }else{
        count += 1;
      }
    }
  }

  /* Copy buffer and append '\0' to [res] */
  if(count > 0) {
    res = (char *)malloc(count + 1);
    strncpy(res, tmp, count);
    res[count] = '\0'; /* '\0' : end_of_string_code */
  }

  return res;
}


/*
  split string.
 Called from [RTC_Manager_procComponentArgs(), RTC_Manager_initNaming(),
              RTC_Manager_initManagerServant(), RTC_RTObject_getNamingNames(),
              Properties_setDefault(), Properties_setDefaults(),
              Properties_findProperties(), Properties_load(), Port_createRepositryID()
              Port_splitDataTypeName(), Port_getIndexOfTypeCode()]. 
*/
string_sequence *
split_string(char *str, const char delim, int max)
{
  char new_str[MAX_STRBUF];
  int i;

  string_sequence *res = NULL;
  char *tmp_str = NULL;
  int len_tmp_str = 0;
  int str_len = strlen(str);
  int count = 0;
  int idx = 0;

  if(str != NULL) {

    /* Counts of split strings */
    if(max < 2){
      count = count_delim(str, delim);
    }else{
      count = max - 1;
    }
    /* alloc */
    res = new_string_sequence(count+1);

    /* Serach by delimiter */
    for(i = 0; i < str_len ;i++) {
      if( (idx < count) && (str[i] == delim) ) {
        /* Matched Delimiter[delim] */
        if(tmp_str != NULL) {
          memset(new_str, 0, MAX_STRBUF);
          strncpy(new_str, tmp_str, MIN(MAX_STRBUF, len_tmp_str));
          res->buffer[idx] = trim_string(new_str);  /* Remove [space]['\n'], append ['\0'] */
          /* increment counts of split string */
          idx += 1;
          /* init tmp , go next search */
          tmp_str = NULL; 
          len_tmp_str = 0;
        }
      } else {
        /* First set pointer, or go next search */
        if(tmp_str == NULL) {
          tmp_str = &str[i]; /* set first pointer */
          len_tmp_str = 1;
        } else {
          len_tmp_str += 1;
        }
      }
    } /* end of for */

    /* For last split string */
    if(len_tmp_str > 0) {
      memset(new_str, 0, MAX_STRBUF);
      strncpy(new_str, tmp_str, MIN(len_tmp_str, MAX_STRBUF));
      res->buffer[idx] = trim_string(new_str);  /* Remove [space]['\n'], append ['\0'] */
      idx += 1;
    }

    /* Set length(counts of split string) */
    res->length = idx;

  } /* end of if */

  return res;
}


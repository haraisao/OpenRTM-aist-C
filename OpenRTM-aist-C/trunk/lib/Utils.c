/*



*/

#include <rtm/Utils.h>
#define MAX_STRBUF		256
#define MIN(a,b)		((a) < (b) ? (a) : (b))


/*

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
  split string 
*/
string_sequence *
split_string(char *str, const char delim, int max)
{
  char new_str[MAX_STRBUF];
  int i;

  string_sequence *res = NULL;
  char *tmp_str = NULL;
  int len_tmp_str = 0;
  int len = 0;
  int count = 0;
  int idx;

  if(str != NULL) {
    if(max < 2){
      count = count_delim(str, delim);
    }else{
      count = max;
    }
    len = strlen(str);
    res = new_string_sequence(count+1);

    idx = 0;
    for(i=0; i<len;i++){
      if(idx < count && str[i] == delim){
        if(tmp_str != NULL){
          memset(new_str, 0, MAX_STRBUF);
          strncpy(new_str, tmp_str, MIN(MAX_STRBUF, len_tmp_str));
          res->buffer[idx] = trim_string(new_str);
          idx += 1;
          tmp_str = NULL;
          len_tmp_str = 0;
        }
      }else{
        if(tmp_str == NULL){
          tmp_str = &str[i];
          len_tmp_str = 1;
        }else{
          len_tmp_str += 1;
        }
      }
    }
    if(len_tmp_str > 0){
      memset(new_str, 0, MAX_STRBUF);
      strncpy(new_str, tmp_str, MIN(len_tmp_str, MAX_STRBUF));
      res->buffer[idx] = trim_string(new_str);
      idx += 1;
    }
    res->length = idx;
  }
  return res;
}

/*
  Trim String
*/
char *
trim_string(char *key)
{
  char *res=NULL;
  char *tmp=NULL;
  int len = strlen(key);
  int i, count;
   
  count = 0;
  for(i=0; i< len; i++){
    if(tmp == NULL){
      if(isblank(key[i]) != 0) continue;
      tmp = &key[i];
      count = 1;
    }else{
      if(isblank(key[i]) != 0){
        res = (char *)malloc(count + 1);
        strncpy(res,tmp, count);
        res[count] = '\0';
        return res;
      }else{
        count += 1;
      }
    }
  }
  if(count > 0){
    res = (char *)malloc(count + 1);
    strncpy(res,tmp, count);
    res[count] = '\0';
  }
  return res;
}


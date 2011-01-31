/*


*/

#include <rtm/Properties.h>

RTC_Properties *
Properties__new()
{
  RTC_Properties *res;
  res = (RTC_Properties *)calloc(1, sizeof(RTC_Properties));
  return res;
}

void
Properties_leaf_append(RTC_Properties *crr, RTC_Properties *next)
{
  if(crr->n_leaf == 0){
    crr->leaf = (RTC_Properties **)malloc(sizeof(RTC_Properties *));
    crr->leaf[0] = next;
  }else{
    void *res = realloc(crr->leaf,sizeof(RTC_Properties *));
    if(res == NULL){
      fprintf(stderr, "ERROR; Properties_leaf_append\n");
      return;
    }
    crr->leaf[crr->n_leaf] = next;
  }
  
  crr->n_leaf++;
  return;
}

RTC_Properties *
Properties_has_key(RTC_Properties *crr, char *key)
{
  RTC_Properties *res=NULL;
  int i;
  
  for(i=0; i< crr->n_leaf; i++){
    if(strcmp( crr->leaf[i]->name, key) == 0){
      res = crr->leaf[i];
      break;
    }
  }
  return res;
}

char *
Properties_setDefault(RTC_Properties *prop, char *key, char *value)
{
  RTC_Properties *crr, *next;
  char **keys;
  int i;
  int n_keys=0;

  if(key == NULL) return NULL;

  n_keys=1;
  keys = split_string(key, '.', &n_keys);

  if(n_keys > 0){

    if(prop == NULL){
       prop = Properties__new();
    }

    crr = prop;
    for(i=0; i<n_keys;i++){
      next = Properties_has_key(crr, keys[i]);
      if(next == NULL){
        next = Properties__new();
        next->root = crr;
        Properties_leaf_append(crr, next);
      }
      crr = next;
    }
    crr->default_value = value;
  }else{
    fprintf(stderr, "!!!!Invalid key found: key = %s\n", key);
  }
  return value;
}

void
free_string_array(char **str, int n)
{
  int i;
  for(i=0;i<n;i++){
    free(str[i]);
  }
  free(str);
}

int
Properties_setDefaults(RTC_Properties *prop, char **str, int n)
{
  int i, j,n_prop;
  int count=0;


  for(j=1;j<n;j++){

  char **vals = split_string(str[j], ':', &n_prop);

    for(i=0; i<n_prop; i++){
      if(n_prop == 2){
        Properties_setDefault(prop, vals[0], vals[1]);
        count++;
      }
      //free_string_array(vals, n_prop);
    }
  }
  return count;
}

char **
split_string(char *key, const char delim,  int *n_keys)
{
  char **res=NULL;
  char *new_key;
  int i;
  char *s1;
  int len_s1;
  int len = 0;

  *n_keys = 0;

  if(key == NULL) {
    return NULL;
  }

  len = strlen(key);

  for(i=0; i<len;i++){

    if(isblank(key[i]) != 0) continue;
    if(key[i] == delim) {
      new_key = (char *)calloc(1, len_s1+1);
      strncpy(new_key, s1, len_s1);

      if(res == NULL){
        res = (char **)calloc(1, sizeof(char *));
      }else{
        res = (char **)realloc(res, (*n_keys + 1) * sizeof(char *));
      }

      res[*n_keys] = new_key;
     
      *n_keys += 1;
      s1 = 0;
      len_s1 = 0;
    }else{
      if(s1 == 0){
        s1 = &key[i];
        len_s1 = 1;
      }else{
        len_s1++;
      }
    }
  }
  if(len_s1 > 0){
    new_key = (char *)calloc(1, len_s1+1);
    strncpy(new_key, s1, len_s1);

    if(res == NULL){
      res = (char **)calloc(1, sizeof(char *));
    }else{
      res = (char **)realloc(res, (*n_keys+1) * sizeof(char *));
    }
    res[*n_keys] = new_key;
    *n_keys += 1;
  }
  return res;
}

char *
trim_string(char *key)
{
  char *res;
  int len = strlen(key);
  int i;
   
  for(i=0; i< len; i++){
    if(res == NULL){
      if(isblank(key[i]) != 0) continue;
      res = &key[i];
    }else{
      if(isblank(key[i]) != 0){
        key[i] = '\0';
        return res;  
      }
    }
  }
  return res;
}

/*

*/
char *
Properties_getProperty(RTC_Properties *prop, char *name)
{

  return NULL;
}

/*

*/
int
Properties_setProperty(RTC_Properties *prop, char *name, char *value)
{

  return 0;
}

/*

*/
RTC_Properties *
Properties_getNode(RTC_Properties *prop, char *name)
{

  return NULL;
}

/*

*/
char *
Properties_formatString(char *format, RTC_Properties *prop)
{

  return 0;
}
/*

*/
int
Properties_load(RTC_Properties *prop, char *fname)
{

  return 0;
}
/*

*/
int
Properties_appendProperty(RTC_Properties *prop, char *fname, char *value)
{

  return 0;
}

/*

*/
int
Properties_appendProperties(RTC_Properties *prop, RTC_Properties *aprop)
{

  return 0;
}

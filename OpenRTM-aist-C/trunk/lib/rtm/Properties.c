/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Properties.c
 * \brief RTCのコンフィグレーションなどを保持する、[RTC_Properties]型構造体データと、各種操作(挿入/取り出し/検索/...)用の関数などのUtilityファイル。
 *
 *        主に、RTCが持つ、設定用パラメータ群を登録するのに使われ、CORBAインタフェースの
関数で必要とされるパラメータは適宜、このデータから取り出すことを目的とする。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/Properties.h>
#include <rtm/DefaultConfig.h>

/*!
 * \brief RTCのデフォルトConfig値格納用変数。
 */
RTC_Properties *Default_Config = NULL;

/*********************** [ Prototype (static) ] ******************************/
static RTC_Properties *Properties_duplicate(RTC_Properties *prop);
static void print_index(int idx);

/*****************************************************************************/
/*************************** [ Functions ] ***********************************/
/*****************************************************************************/

/*
   Creaet a new RTC_Properties. 
 Called from [RTC_Manager_createComponent(),  Properties_make_system_default(), 
              Properties_createDefaultProperties(),  Properties_setDefault(), 
              Properties_appendProperties(), Properties_duplicate()].
*/
RTC_Properties *
Properties__new(char *name)
{
  RTC_Properties *res;
  res = (RTC_Properties *)calloc(1, sizeof(RTC_Properties));
  res->name = strdup(name);
  return res;
}


/*
  Create a system default properties.
 Called from [RTC_Manager_configure()].
*/

RTC_Properties *
Properties_make_system_default()
{
  const char *val;
  int i;

  /* delete and create */
  if (Default_Config != NULL){
    Properties_delete(Default_Config);
  }
  Default_Config = Properties__new("root");

  /* set 1st data */
  val = default_config[0];  /* [0]="config.version" { ref:DefaultConfig.h } */

  /* set data(name/value) to RTC_Properties data as "Default" */
  for(i=0; val != NULL; i+=2){
    /*                    arg[0]:RTC_Properties, arg[1]:"name", arg[2]:value */
    Properties_setDefault(Default_Config, (char *)val, (char *)default_config[i+1]);
    val = default_config[i+2];
  }

  return Default_Config;
}


/*
 Called from [RTC_Manager_procComponentArgs()].
*/
RTC_Properties *
Properties_createDefaultProperties(const char **spec)
{
  RTC_Properties *res;
  const char *val;
  int i;

  res = Properties__new("root");
  val = spec[0]; /* set 1st data as "name" */

  for(i=0; val != NULL; i+=2){
    /*     arg[0]:RTC_Properties, arg[1]:"name", arg[2]:value */
    Properties_setDefault(res, (char *)val, (char *)spec[i+1]);
    val = spec[i+2];
  }

  return res;
}


/*
  delete RTC_Properties
 Called from [Properties_make_system_default(), Properties_clearLeaf()].
*/
void
Properties_delete(RTC_Properties *prop)
{
  int i;

  for(i=0;i<prop->n_leaf;i++){
    Properties_delete(prop->leaf[i]);
  }
  free(prop->leaf);
  prop->leaf = NULL;
  prop->n_leaf = 0;

  free(prop->name);
  free(prop->default_value);
  free(prop->value);
  free(prop);
  return;
}


/*
  clear leaf RTC_Properties
 (Uncalled).
*/
void
Properties_clearLeaf(RTC_Properties *prop)
{
  int i;

  for(i=0;i<prop->n_leaf;i++){
    Properties_delete(prop->leaf[i]);
  }
  free(prop->leaf);
  prop->leaf = NULL;
  prop->n_leaf = 0;
  return;
}


/*
 Called from [Properties_setDefault(), Properties_appendProperties()].
*/
int
Properties_leaf_append(RTC_Properties *crr, RTC_Properties *next)
{
  if(crr == NULL || next == NULL){
    return 0;
  }
  /* Allocate/ReAllocate memory for [leaf] */
  if(crr->n_leaf == 0){
    crr->leaf = (RTC_Properties **)malloc(sizeof(RTC_Properties *));
  }else{
    int size = crr->n_leaf + 1;
    void *res = realloc(crr->leaf, sizeof(RTC_Properties *) * size );
    if(res == NULL){
      fprintf(stderr, "ERROR; Properties_leaf_append\n");
      return -1;
    }
    crr->leaf = res;
  }
  
  /* set [leaf], increment [n_leaf] */
  crr->leaf[crr->n_leaf] = next;
  crr->n_leaf++;

  return crr->n_leaf;
}


/*
 Called from [Properties_setDefault(), Properties_findProperties()].
*/
RTC_Properties *
Properties_has_key(RTC_Properties *crr, char *key)
{
  RTC_Properties *res=NULL;
  int i;
  
  if(crr == NULL) { return NULL; }

  for(i=0; i< crr->n_leaf; i++){
    RTC_Properties *leaf = crr->leaf[i];
    if(leaf != NULL){
      if(leaf->name != NULL){
        if(strcmp( leaf->name, key) == 0){
          res = leaf;
        }
      }
    }
  }
  return res;
}


/*
 Called from [Properties_make_system_default(), Properties_setDefaults(), 
              Properties_createDefaultProperties(), Properties_setProperty()].
*/
RTC_Properties * 
Properties_setDefault(RTC_Properties *prop, char *key, char *value)
{
  RTC_Properties *crr, *next;
  string_sequence *keys;
  int i;

  if(key == NULL) return NULL;
  if(prop == NULL){
    prop = Properties__new("root");
  }

  /* Split key by "." */
  keys = split_string(key, '.', 0);  /* "aaa.bbb.ccc" ==> [aaa][bbb][ccc] */

  if(keys->length > 0){
    crr = prop;
    /* search [leaf], create[leaf], set [key], hierarchically */
    for(i=0; i<keys->length;i++){
      /* Search wheher [leaf(key)] already exist or not. */
      next = Properties_has_key(crr, keys->buffer[i]);
      if(next == NULL){ /* If not found => */
        next = Properties__new(keys->buffer[i]); /* create [leaf] */
        next->root = crr;
        Properties_leaf_append(crr, next); /* append [leaf] */
      }
      crr = next;
    }
    /* set [value] */
    if(value != NULL){
      crr->default_value = strdup(value);
      crr->value = strdup(value);
    }
  }else{
    fprintf(stderr, "!!!!Invalid key found: key = %s\n", key);
  }

  free_string_sequence(keys);
  return prop;
}


/*
 Called from [RTC_Manager_configure()]. (Unused) 
*/
RTC_Properties *
Properties_setDefaults(RTC_Properties *prop, char **str, int n)
{
#if 0
  int i;
  string_sequence *vals;

  for(i=1; i<n; i++){
    vals = split_string(str[i] , ':', 2); 
    if(vals->length == 2){
      prop = Properties_setDefault(prop, vals->buffer[0], vals->buffer[1]);
    }
  }
#endif
  return prop;
}


/*
 Called from [Properties_getProperty(), Properties_setProperty(), 
              Properties_getNode(), Properties_appendProperties()].
*/
RTC_Properties *
Properties_findProperties(RTC_Properties *prop, char *key)
{
  RTC_Properties *crr=NULL;
  string_sequence *names;
  int i;

  if(prop != NULL){
    crr = prop;
    names = split_string(key, '.', 0);

    for(i=0; crr != NULL && i < names->length; i++){
      crr = Properties_has_key(crr, names->buffer[i]);
    }
  }
  return crr;
}


/*
 Called from [RTC_Manager_createComponent(), RTC_Manager_initNaming(),
              RTC_Manager_initManagerServant(), RTC_Manager_configureComponent(),
              RTC_RTObject_getCategory(), RTC_RTObject_getTypeName(),
              RTC_RTObject_getInstanceName(), RTC_RTObject_getProperty(),
              RTC_RTObject_getNamingNames(), impl_RTC_RTObject_get_component_profile(),
              Properties_formatString()].
*/
char *
Properties_getProperty(RTC_Properties *prop, char *key)
{
  char *res = NULL;
  RTC_Properties *crr = Properties_findProperties(prop, key);

  if(crr != NULL){
     res = crr->value; 
     if(res == NULL){
       res = crr->default_value; 
     }
  }
  return res;
}


/*
 Called from [RTC_Manager_setSystemInformation(), RTC_Manager_procComponentArgs(),
              RTC_Manager_createComponent(), RTC_RTObject_setInstanceName(),
              RTC_RTObject_setProperty(), Properties_load()].
*/
RTC_Properties *
Properties_setProperty(RTC_Properties *prop, char *name, char *value)
{
  int res = 0;
  RTC_Properties *crr = Properties_findProperties(prop, name);

  if(crr == NULL){
    prop = Properties_setDefault(prop, name, value); /* Create [leaf] and set "name" and "value." */
  }else{
    if(value != NULL){
      crr->value = strdup(value); /* Only set "value" */
    }
  }
  return prop;
}


/*
 Called from [RTC_Manager_initManagerServant()].
*/
RTC_Properties *
Properties_getNode(RTC_Properties *prop, char *key)
{
  RTC_Properties *crr = Properties_findProperties(prop, key);
  return crr;
}


/*
 Called from [RTC_Manager_initManagerServant(), RTC_Manager_configureComponent()].
*/
char *
Properties_formatString(char *format, RTC_Properties *prop)
{
  char *res = NULL;
#if 1
  /* Delete duplicative format */
  string_sequence *seq = split_string(format, ',', 2);
  if( (seq->length == 2) && (strcmp(seq->buffer[0], seq->buffer[1]) == 0) ) {
    format = strdup(seq->buffer[0]);
  }
  free_string_sequence(seq);
#endif

  if(format != NULL && prop != NULL){
    char str[MAX_STRBUF];
    int i, current, count;
    int len = MIN(strlen(format), MAX_STRBUF);

    memset(str, 0, MAX_STRBUF);
    count = 0;
    current = 0;

    for(i=0; i<len;i++){
      char c = format[i];
      if(c == '%'){
        count += 1;
        if( (count % 2) == 0 ){
          str[current] = c;
          current += 1;
        }
      }else if(c == '$'){
        count = 0;
        i += 1;
        c = format[i];
        if(c == '{'  || c == '(' ){
          i += 1;
          c = format[i];
          char env[MAX_STRBUF];
          int j = 0;
          memset(env,0, MAX_STRBUF);
          for( ; i<len && c != '}' && c != ')' ;i++){
            c = format[i+1];
            env[j]=c;
            j += 1;
          }
          char *envval = getenv(env);
          if(envval != NULL){
            int len2 = strlen(envval);
            strncpy(&str[current], envval, len2);
            current += len2;
          }
        }else{
         str[current] = c;
         current += 1;
        }
      }else{
        if( (count > 0) && ((count % 2) == 1)){
          count = 0;
          char *val=NULL;
          int len2;

          if( c == 'n'){
            val = Properties_getProperty(prop,"instance_name");
          }else if( c == 't'){
            val = Properties_getProperty(prop,"type_name");
          }else if( c == 'm'){
            val = Properties_getProperty(prop,"type_name");
          }else if( c == 'v'){
            val = Properties_getProperty(prop,"version");
          }else if( c == 'V'){
            val = Properties_getProperty(prop,"vendor");
          }else if( c == 'c'){
            val = Properties_getProperty(prop,"category");
          }else if( c == 'h'){
            val = Properties_getProperty(prop,"manager.os.hostname");
          }else if( c == 'M'){
            val = Properties_getProperty(prop,"manager.name");
          }else if( c == 'p'){
            val = Properties_getProperty(prop,"manager.pid");
          }else{
          }
          if(val != NULL){
            len2 = strlen(val);
            strncpy(&str[current], val, len2);
            current += len2;
          }else{
            str[current] = c;
            current += 1;
          }
        }else{
          count = 0;
          str[current] = c;
          current += 1;
        }
      }
    }
    res = strdup(str);
  }

  return res;
}


/*
 Called from [RTC_Manager_configure(), RTC_Manager_configureComponent()].
*/
RTC_Properties *
Properties_load(RTC_Properties *prop, char *fname)
{
  FILE *fp;
  char line[1024];

  fp = fopen(fname,"r");
  if(fp != NULL){
    char *res;
    res = fgets(line, 1024, fp);
    do {
      char *comment = index(line, '#');
      if(comment != NULL){
        *comment = '\0';
      }
      int n = count_delim(line, ':');
      if(n > 0){
        string_sequence *seq = split_string(line, ':', 2);
        if(strlen(seq->buffer[0]) > 0 && strlen(seq->buffer[1]) > 0){
          prop = Properties_setProperty(prop, seq->buffer[0], seq->buffer[1]);
        }
        free_string_sequence(seq);
      }
      res = fgets(line, 1024, fp);
    
    } while(res != NULL);
    fclose(fp);
  }else{
    fprintf(stderr," Fail to access a configureation file : %s\n", fname);
  }

  return prop;
}


/*
 Called from [RTC_Manager_configureComponent(), RTC_Manager_createComponent(), RTC_RTObject_appendProperties()].
*/
RTC_Properties *
Properties_appendProperties(RTC_Properties *prop, RTC_Properties *aprop)
{
  int i;

  if(aprop == NULL){ return 0; }

  if(prop == NULL){
    prop = Properties__new("root");
  }

  for(i=0; i<aprop->n_leaf; i++){
    RTC_Properties *leaf = aprop->leaf[i];
    char *name = leaf->name;

    RTC_Properties *crr = Properties_findProperties(prop, name);

    if(crr == NULL){ /* Not exist ==> append [leaf] */
       Properties_leaf_append(prop, Properties_duplicate(leaf));
    }else{ /* already exist ==> only overwrite "value" */
      if(leaf->value != NULL){ crr->value = strdup(leaf->value); } /* overwrite */
      Properties_appendProperties(crr, leaf); /* recursive set */
    }
  }
  return prop;
}


/*
 Called from [RTC_Manager_configure()].
*/
void
Properties_dumpProperties(RTC_Properties *prop, int idx)
{
  int i;

  if(prop == NULL){
     fprintf(stderr, "No Properties\n");
     return;
  }
  if(idx == 0) {
    fprintf(stderr, "========= DUMP ============\n");
  }
  fprintf(stderr, "%s: %s\n", prop->name, prop->value);

  for(i=0;i<prop->n_leaf;i++){
    print_index(idx+1);
    Properties_dumpProperties(prop->leaf[i], idx+1);
  }

  return;
}


/********************* [ static functions ] **********************************/


/*!
 * \brief 引数[prop]のコピーを生成し、そのポインタを返す。<BR>
 *        全体の領域をcallocし、中身もすべてコピーし、[leaf]があれば、階層的に当関数をcallしてコピー。 <BR>
 *         [Properties_appendProperties()]　からcallされる。
 * \param prop コピー元の[RTC_Properties]型データ
 * \return コピー先の[RTC_Properties]型データ
 */
static RTC_Properties *
Properties_duplicate(RTC_Properties *prop)
{
  RTC_Properties *res = NULL;
  int i;

  if(prop != NULL){
    res = Properties__new(prop->name);
    res->n_leaf = prop->n_leaf; 
    if( prop->value != NULL){ res->value = strdup(prop->value); }
    if( prop->default_value != NULL){ res->default_value = strdup(prop->default_value); }
    /* duplicate [leaf] */
    if(prop->n_leaf > 0){
      res->leaf =  malloc(sizeof(RTC_Properties *) * prop->n_leaf );
      for(i=0;i<prop->n_leaf;i++){
        res->leaf[i] = Properties_duplicate(prop->leaf[i]); /* recursive */
      }
    }
  }
  return res;
}


/*!
 * \brief デバッグ出力用に、階層に応じた「スペース」を入れる。 
 *        Called from [Properties_dumpProperties()]
 */
static void print_index(int idx)
{
  int i;
  for(i=0;i<idx;i++){
    fprintf(stderr, "  ");
  }

  return; 
}


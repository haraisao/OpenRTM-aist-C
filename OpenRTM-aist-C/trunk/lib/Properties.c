/*


*/

#include <rtm/Properties.h>
#include <rtm/DefaultConfig.h>
/*
  GLOBAL Variable
*/

RTC_Properties *Default_Config=NULL;

/*
   Creaet a new RTC_Properties 
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
*/
RTC_Properties *
Properties_make_system_default()
{
  const char *val;
  int i;

  if (Default_Config != NULL){
    Properties_delete(Default_Config);
  }

  Default_Config = Properties__new("root");
  val = default_config[0];

  for(i=0; val != NULL; i+=2){
    Properties_setDefault(Default_Config, (char *)val, (char *)default_config[i+1]);
    val = default_config[i+2];
  }

  return Default_Config;
}

/*
  delete RTC_Properties
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
  free(prop->m_empty);
  free(prop);
  return;
}

/*
  clear leaf RTC_Properties
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


*/
int
Properties_leaf_append(RTC_Properties *crr, RTC_Properties *next)
{

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
  
  crr->leaf[crr->n_leaf] = next;
  crr->n_leaf++;
  return crr->n_leaf;
}

/*

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

  keys = split_string(key, '.', 0);

  if(keys->length > 0){
    crr = prop;
    for(i=0; i<keys->length;i++){
      next = Properties_has_key(crr, keys->buffer[i]);
      if(next == NULL){
        next = Properties__new(keys->buffer[i]);
        next->root = crr;
        Properties_leaf_append(crr, next);
      }
      crr = next;
    }
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


*/
RTC_Properties *
Properties_setDefaults(RTC_Properties *prop, char **str, int n)
{
  int i;
  string_sequence *vals;

  for(i=1; i<n; i++){
    vals = split_string(str[i] , ':', 2);
    if(vals->length == 2){
      prop = Properties_setDefault(prop, vals->buffer[0], vals->buffer[1]);
    }
  }
  return prop;
}

/*

*/
RTC_Properties *
Properties_findProperties(RTC_Properties *prop, char *name)
{
  RTC_Properties *crr=NULL;
  string_sequence *keys;
  int i;

  if(prop != NULL){
    crr = prop;
    keys = split_string(name, '.', 0);

    for(i=0; crr != NULL && i < keys->length; i++){
      crr = Properties_has_key(crr, keys->buffer[i]);
    }
  }
  return crr;
}

/*


*/
char *
Properties_getProperty(RTC_Properties *prop, char *name)
{
  char *res = NULL;
  RTC_Properties *crr = Properties_findProperties(prop, name);

  if(crr != NULL){
     res = crr->value; 
     if(res == NULL){
       res = crr->default_value; 
     }
  }
#if 0
  if(res == NULL){
    fprintf(stderr, "no property in %s\n",name);
  }
#endif
  return res;
}

/*

*/
RTC_Properties *
Properties_setProperty(RTC_Properties *prop, char *name, char *value)
{
  int res = 0;
  RTC_Properties *crr = Properties_findProperties(prop, name);

  if(crr == NULL){
    prop = Properties_setDefault(prop, name, value);
  }else{
    if(value != NULL){
      crr->value = strdup(value); 
    }
  }
  return prop;
}

/*

*/
RTC_Properties *
Properties_getNode(RTC_Properties *prop, char *name)
{
  RTC_Properties *crr = Properties_findProperties(prop, name);
  return crr;
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
RTC_Properties *
Properties_duplicate(RTC_Properties *prop)
{
  RTC_Properties *res = NULL;
  int i;

  if(prop != NULL){
    res = Properties__new(prop->name);
    res->n_leaf = prop->n_leaf; 
    if( prop->value != NULL){ res->value = strdup(prop->value); }
    if( prop->default_value != NULL){ res->default_value = strdup(prop->default_value); }

    if(prop->n_leaf > 0){
      res->leaf =  malloc(sizeof(RTC_Properties *) * prop->n_leaf );
      for(i=0;i<prop->n_leaf;i++){
        res->leaf[i] = Properties_duplicate(prop->leaf[i]);
      }
    }
  }
  return res;
}

/*

*/
RTC_Properties *
Properties_appendProperties(RTC_Properties *prop, RTC_Properties *aprop)
{
  int i;
  if(prop == NULL){
    prop = Properties__new("root");
  }

  for(i=0; i<aprop->n_leaf; i++){
    RTC_Properties *leaf = aprop->leaf[i];
    char *name = leaf->name;
    RTC_Properties *crr = Properties_findProperties(prop, name);

    if(crr == NULL){
       Properties_leaf_append(prop, Properties_duplicate(leaf));
    }else{
      if(leaf->value != NULL){ crr->value = strdup(leaf->value); }
      Properties_appendProperties(crr, leaf);
    }
  }
  return prop;
}

/*

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

void print_index(int idx)
{
  int i;
  for(i=0;i<idx;i++){
    fprintf(stderr, "  ");
  }

  return; 
}


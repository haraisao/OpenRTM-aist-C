/*


*/

#ifndef RTM_PROPERTIES_H
#define RTM_PROPERTIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Properties_struct {
  char * name;
  char * value;
  char * default_value;
  char * m_empty;
  int n_leaf;

  struct Properties_struct *root;
  struct Properties_struct **leaf;
} RTC_Properties;


/************************/
RTC_Properties *Properties__new();
void Properties_leaf_append(RTC_Properties *crr, RTC_Properties *next);
RTC_Properties *Properties_has_key(RTC_Properties *crr, char *key);
char * Properties_setDafault(RTC_Properties *prop, char *key,  char *value);
char **split_string(char *key, const char delim,  int *n_keys);



#endif /* RTM_PROPERTIES_H */


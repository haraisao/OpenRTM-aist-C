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
char * Properties_setDefault(RTC_Properties *prop, char *key,  char *value);
void free_string_array(char **str, int n);
int Properties_setDefaults(RTC_Properties *prop, char **str, int n);
char **split_string(char *key, const char delim,  int *n_keys);
char * trim_string(char *key);
RTC_Properties * Properties_findProperties(RTC_Properties *prop, char *name);
char * Properties_getProperty(RTC_Properties *prop, char *name);

int Properties_setProperty(RTC_Properties *prop, char *name, char *value);
RTC_Properties * Properties_getNode(RTC_Properties *prop, char *name);
char * Properties_formatString(char *format, RTC_Properties *prop);
int Properties_load(RTC_Properties *prop, char *fname);

int Properties_appendProperty(RTC_Properties *prop, char *fname, char *value);
int Properties_appendProperties(RTC_Properties *prop, RTC_Properties *aprop);
void Properties_dumpProperties(RTC_Properties *prop, int idx);
void print_index(int idx);

#endif /* RTM_PROPERTIES_H */


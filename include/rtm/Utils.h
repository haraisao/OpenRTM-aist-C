/*


*/

#ifndef RTM_UTILS_H
#define RTM_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  int maximum;
  int length;
  char **buffer;
}string_sequence;

string_sequence * new_string_sequence(int len);
void free_string_sequence(string_sequence *seq);
string_sequence *split_string(char *str, const char delim, int max);
char * trim_string(char *str);

#endif

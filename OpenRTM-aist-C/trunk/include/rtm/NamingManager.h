/*



*/

#ifndef RTC_NAMING_MANAGER_H
#define RTC_NAMING_MANAGER_H

#include <rtm/Manager.h>

typedef struct {
  char *name;
  RTC_RTObject rtobj;
} RTC_Comp;

typedef struct {
  char *methods;
  char *nsname;
} RTC_Name;

typedef struct {
  RTC_Name **m_names;
  RTC_Comp *m_compNames;

} RTC_NamingManager;


/*******  ******/


#endif /* RTC_NAMING_MANAGER_H */

/*



*/

#ifndef RTC_NAMING_MANAGER_H
#define RTC_NAMING_MANAGER_H

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
void RTC_NamingManager_registerNameServer(const char *method, const char *name_server);
void RTC_NamingManager_bindObject(const char *name, const RTC_RTObject name_server);
void RTC_NamingManager_update();
void RTC_NamingManager_unbindObject(const char *name);
void RTC_NamingManager_unbindAll();

#endif /* RTC_NAMING_MANAGER_H */

/*



*/

#ifndef RTC_NAMING_MANAGER_H
#define RTC_NAMING_MANAGER_H
#include <RtORB/corba.h>
#include <CosName/CosNaming.h>

typedef struct {
  char *name_server;
  CORBA_ORB orb;
  CosNaming_NamingContext rootContext;
  CORBA_Environment env;
} RTC_NamingBase;


typedef struct {
  char *name;
  RTC_RTObject rtobj;
} RTC_Comp;

typedef struct {
  char *methods;
  char *nsname;
  RTC_NamingBase *name;
} RTC_Name;

typedef struct {
  RTC_Name **m_names;
  int n_name;
  RTC_Comp **m_compNames;
  int n_comp;
  struct RTC_Manager_struct *m_manager;

} RTC_NamingManager;


/*******  ******/
void RTC_NamingManager_registerNameServer(RTC_NamingManager *mgr, const char *method, const char *name_server);
void RTC_NamingManager_bindObject(RTC_NamingManager *mgr, const char *name, const RTC_RTObject name_server);
void RTC_NamingManager_update(RTC_NamingManager *mgr);
void RTC_NamingManager_unbindObject(RTC_NamingManager *mgr, const char *name);
void RTC_NamingManager_unbindAll(RTC_NamingManager *mgr);

int NamingOnCorba_connect(RTC_NamingBase *nb);

RTC_NamingBase * RTC_NamingBase_createNamingObj(RTC_NamingManager *nm, char *method, char *name_server);

RTC_Name * RTC_Name__new(char *method, char *name_server, RTC_NamingBase *name);



#endif /* RTC_NAMING_MANAGER_H */

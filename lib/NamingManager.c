/*


*/

#include <rtm/OpenRTM.h>

/*
 Create RTC_Manager and initialize...

*/
RTC_NamingManager *
RTC_NamingManager__new(RTC_Manager *mgr)
{
  RTC_NamingManager *res = (RTC_NamingManager *)calloc(1,sizeof(RTC_NamingManager));


  return res;
}

void
RTC_NamingManager_registerNameServer(const char *method, const char *name_server)
{

}

void
RTC_NamingManager_bindObject(const char *name, const RTC_RTObject *name_server)
{

}

#if 0
void
RTC_NamingManager_bindObject(const char *name, const RTC_ManagerServant *rtobj)
{

}
#endif

void
RTC_NamingManager_update()
{

}

void
RTC_NamingManager_unbindObject(const char *name)
{

}

void
RTC_NamingManager_unbindAll()
{

}


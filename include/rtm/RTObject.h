/*


*/
#ifndef RTM_RTOBJECT_H
#define RTM_RTOBJECT_H

#include <rtm/OpenRTM-aist.h>
#include <rtm/OpenRTM-aist-decls.h>
#include <rtm/Manager.h>

CORBA_RTC_RTObject RTC_DataFlowComponentBase_create(RTC_Manager *manager);
OpenRTM_OutPortCdr RTC_OutPort_create(RTC_Manager *mgr, const char *typ, void **data);
void RTC_OutPort_write( OpenRTM_OutPortCdr *port );

RTC_Properties *RTC_RTObject_getProperties(CORBA_RTC_RTObject obj);
char * RTC_RTObject_getCategory(CORBA_RTC_RTObject obj);
char * RTC_RTObject_getTypeName(CORBA_RTC_RTObject obj);
char * RTC_RTObject_getInstanceName(CORBA_RTC_RTObject obj);
int RTC_RTObject_setProperty(CORBA_RTC_RTObject obj, char *name, char *value);
int RTC_RTObject_appendProperty(CORBA_RTC_RTObject obj, char *name, char *value);

char * RTC_RTObject_getProperty(CORBA_RTC_RTObject obj, char *name);
int RTC_RTObject_registerProperty(CORBA_RTC_RTObject obj, RTC_Properties *prop);
RTC_Properties * RTC_RTObject_appendProperties(CORBA_RTC_RTObject obj, RTC_Properties *prop);
char ** RTC_RTObject_getNamingNames(CORBA_RTC_RTObject obj, int *len);

#endif /* RTM_RTOBJECT_H */

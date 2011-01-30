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

void RTC_RTObject_configureComponent(CORBA_RTC_RTObject comp, RTC_Manager *manager);
//void RTC_RTObject_initialize(CORBA_RTC_RTObject comp);
void RTC_RTObject_registerComponent(CORBA_RTC_RTObject comp);


#endif /* RTM_RTOBJECT_H */

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






#endif /* RTM_RTOBJECT_H */

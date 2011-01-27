/*


*/

#include <rtm/OpenRTM.h>


/*


*/
CORBA_RTC_RTObject *
RTC_DataFlowComponentBase_create(RTC_Manager *manager)
{
  CORBA_RTC_RTObject *res;
  PortableServer_POA servant;
  CORBA_Environment ev;

  *res = impl_RTC_RTObject__create(servant, &ev);

  return res;

}

/*

*/
OpenRTM_OutPortCdr *
RTC_OutPort_create(const char *typ, void **data)
{

  OpenRTM_OutPortCdr *res;
  PortableServer_POA servant;
  CORBA_Environment ev;

  *res = impl_OpenRTM_OutPortCdr__create(servant, &ev);

  return res;
}


/*

*/
void
RTC_OutPort_write( OpenRTM_OutPortCdr *port )
{
  return;
}

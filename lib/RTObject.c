/*


*/

#include <rtm/OpenRTM.h>


/*


*/
CORBA_RTC_RTObject *
RTC_DataFlowComponentBase_create(RTC_Manager *manager)
{
  CORBA_RTC_RTObject *res;
  CORBA_Environment ev;

  *res = impl_RTC_RTObject__create(manager->m_pPOA, &ev);

  return res;

}

/*

*/
OpenRTM_OutPortCdr *
RTC_OutPort_create(RTC_Manager *manager, const char *typ, void **data)
{

  OpenRTM_OutPortCdr *res;
  CORBA_Environment ev;

  *res = impl_OpenRTM_OutPortCdr__create(manager->m_pPOA, &ev);

  return res;
}


/*

*/
void
RTC_OutPort_write( OpenRTM_OutPortCdr *port )
{
  return;
}

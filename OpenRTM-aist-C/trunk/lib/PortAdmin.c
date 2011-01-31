/*


*/

#include <rtm/OpenRTM.h>
#include <rtm/PortAdmin.h>

RTC_PortAdmin *
PortAdmin__new()
{
  RTC_PortAdmin *res;
  res = (RTC_PortAdmin *)calloc(1, sizeof(RTC_PortAdmin));
  return res;
}

/*

*/
RTC_PortServiceList PortAdmin_getPortServiceList(RTC_PortAdmin *admin)
{

}
/*

*/
RTC_PortProfileList PortAdmin_getPortProfileList(RTC_PortAdmin *admin)
{

}
/*

*/
RTC_PortService PortAdmin_getPortRef(RTC_PortAdmin *admin, char *port_name)
{

}

/*

*/
RTC_PortService PortAdmin_getPort(RTC_PortAdmin *admin, char *port_name)
{

}
/*

*/
int PortAdmin_addPort(RTC_PortAdmin *admin, RTC_PortService *port)
{

}
/*

*/
int PortAdmin_addPortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{

}
/*

*/
int PortAdmin_registerPort(RTC_PortAdmin *admin, RTC_PortService *port)
{

}
/*

*/
int PortAdmin_registerPortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{

}
/*

*/
int PortAdmin_removePort(RTC_PortAdmin *admin, RTC_PortService *port)
{

}
/*

*/
int PortAdmin_removePortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{

}
/*

*/
int PortAdmin_deletePort(RTC_PortAdmin *admin, RTC_PortService *port)
{

}
/*

*/
int PortAdmin_deletePortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{

}

/*

*/
int PortAdmin_finalizePorts(RTC_PortAdmin *admin)
{

}


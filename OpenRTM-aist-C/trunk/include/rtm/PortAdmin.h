/*


*/

#ifndef RTM_PORTADMIN_H
#define RTM_PORTADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct PortAdmin_struct {
  CORBA_ORB *m_pORB;
  PortableServer_POA  *m_pPOA;
  RTC_PortServiceList *m_portRefs;

} RTC_PortAdmin;



/************************/
RTC_PortAdmin *PortAdmin__new();

RTC_PortServiceList * PortAdmin_getPortServiceList(RTC_PortAdmin *admin);
RTC_PortProfileList * PortAdmin_getPortProfileList(RTC_PortAdmin *admin, RTC_PortProfileList *ppl);
RTC_PortService PortAdmin_getPortRef(RTC_PortAdmin *admin, char *port_name);

RTC_PortService PortAdmin_getPort(RTC_PortAdmin *admin, char *port_name);

int PortAdmin_addPort(RTC_PortAdmin *admin, RTC_PortService *port);
int PortAdmin_addPortService(RTC_PortAdmin *admin, RTC_PortService *port_service);
int PortAdmin_registerPort(RTC_PortAdmin *admin, RTC_PortService *port);
int PortAdmin_registerPortService(RTC_PortAdmin *admin, RTC_PortService *port_service);

int PortAdmin_removePort(RTC_PortAdmin *admin, RTC_PortService *port);
int PortAdmin_removePortService(RTC_PortAdmin *admin, RTC_PortService *port_service);
int PortAdmin_deletePort(RTC_PortAdmin *admin, RTC_PortService *port);
int PortAdmin_deletePortService(RTC_PortAdmin *admin, RTC_PortService *port_service);

int PortAdmin_deletePortByName(RTC_PortAdmin *admin, char *port);

int PortAdmin_activatePorts(RTC_PortAdmin *admin);
int PortAdmin_deactivatePorts(RTC_PortAdmin *admin);
int PortAdmin_finalizePorts(RTC_PortAdmin *admin);

#endif /* RTM_PORT_ADMIN_H */


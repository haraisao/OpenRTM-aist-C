/*


*/

#include <rtm/OpenRTM.h>
#include <rtm/PortAdmin.h>

RTC_PortServiceList * RTC_PortServiceList_duplicate(RTC_PortServiceList *psl);
RTC_PortProfile *PortService_get_port_profile(RTC_PortService *ps);

RTC_PortAdmin *
PortAdmin__new()
{
  RTC_PortAdmin *res;
  res = (RTC_PortAdmin *)calloc(1, sizeof(RTC_PortAdmin));
  return res;
}

/*
  called from impl_RTC_RTObject_get_ports
*/
RTC_PortServiceList *
PortAdmin_getPortServiceList(RTC_PortAdmin *admin)
{
  RTC_PortServiceList* retval;
  if( admin == NULL ){
    retval = RTC_PortServiceList__alloc();
  }else{

  if( admin == NULL && admin->m_portRefs == NULL){
    retval = RTC_PortServiceList__alloc();
  }else{
    retval = RTC_PortServiceList_duplicate(admin->m_portRefs);
  }
  }
  return retval;
}
/*

*/
RTC_PortProfileList *
PortAdmin_getPortProfileList(RTC_PortAdmin *admin, RTC_PortProfileList *ppl)
{
  int i;
  if(admin == NULL || ppl == NULL){
    ppl = RTC_PortProfileList__alloc();
    ppl->_maximum = ppl->_length = 0;
    ppl->_buffer = NULL;
    ppl->_release = 0;
  }else{
    if( admin->m_portRefs == NULL){
      ppl = RTC_PortProfileList__alloc();
      ppl->_maximum = ppl->_length = 0;
      ppl->_buffer = NULL;
      ppl->_release = 0;
    }else{
      int len = admin->m_portRefs->_length;

      ppl->_maximum = ppl->_length = len;
      ppl->_buffer = malloc(sizeof(RTC_PortProfile) * len);
      for(i = 0; i< len ; i++){
        memcpy(&ppl->_buffer[i], PortService_get_port_profile((RTC_PortService *)admin->m_portRefs->_buffer[i]), sizeof(RTC_PortService));
      }
    }
  }

  return ppl;
}
/*

*/
char *
PortService__name(RTC_PortService ps)
{
  char *res = "";
  impl_POA_RTC_PortService  *implobj=(impl_POA_RTC_PortService *)ps->servant;
  res = implobj->m_name;
  return res;
}
/*

*/
RTC_PortService
PortAdmin_getPortRef(RTC_PortAdmin *admin, char *port_name)
{
  int i;
  RTC_PortService res = NULL;
  RTC_PortServiceList *psl = admin->m_portRefs;
  for(i=0; res == NULL && i<psl->_length;i++){
    if(strcmp(PortService__name(psl->_buffer[i]), port_name) == 0){
      res = psl->_buffer[i];
    }
  }
  return res;
}

/*

*/
RTC_PortService
PortAdmin_getPort(RTC_PortAdmin *admin, char *port_name)
{
  int i;
  RTC_PortService res = NULL;
  RTC_PortServiceList *psl = admin->m_portRefs;
  for(i=0; res == NULL && i<psl->_length;i++){
    if(strcmp(PortService__name(psl->_buffer[i]), port_name) == 0){
      res = psl->_buffer[i];
    }
  }

  return res;
}
/*

*/
int 
PortAdmin_addPort(RTC_PortAdmin *admin, RTC_PortService *port)
{
  int i;
  int res = 0;
  RTC_PortServiceList *psl = admin->m_portRefs;
  int len = psl->_length;
  psl->_maximum = len+1;
  psl->_length = len+1;
  
  psl->_buffer = realloc(psl->_buffer, sizeof(RTC_PortService) * psl->_length);
  memcpy( &psl->_buffer[len], port, sizeof(RTC_PortService));

  res = len+1;
  return res;
}
/*

*/
int 
PortAdmin_addPortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{
  return PortAdmin_addPort(admin, port_service);
}
/*

*/
int 
PortAdmin_registerPort(RTC_PortAdmin *admin, RTC_PortService *port)
{
  return PortAdmin_addPort(admin, port);
}
/*

*/
int 
PortAdmin_registerPortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{
  return PortAdmin_addPort(admin, port_service);
}
/*

*/
int 
PortAdmin_removePort(RTC_PortAdmin *admin, RTC_PortService *port)
{
  int res = 0;
  return res;
}
/*

*/
int 
PortAdmin_removePortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{
  int res = 0;
  return res;
}
/*

*/
int 
PortAdmin_deletePort(RTC_PortAdmin *admin, RTC_PortService *port)
{
  int res = 0;
  return res;
}
/*

*/
int 
PortAdmin_deletePortService(RTC_PortAdmin *admin, RTC_PortService *port_service)
{
  int res = 0;
  return res;
}

/*

*/
int 
PortAdmin_finalizePorts(RTC_PortAdmin *admin)
{
  int res = 0;
  return res;
}


/************ PortService ***********/
RTC_PortServiceList *
RTC_PortServiceList_duplicate(RTC_PortServiceList *psl)
{
  RTC_PortServiceList *res;
  int i;
  res = RTC_PortServiceList__alloc();
  res->_maximum = psl->_maximum;
  res->_length = psl->_length;
  res->_release = psl->_release;
  res->_buffer = malloc(sizeof(RTC_PortService) * psl->_length);
  for(i=0;i< psl->_length;i++)
  {
     res->_buffer[i] = psl->_buffer[i];
  }
  
  return  psl;
}


/****** PortService ***/
RTC_PortProfile *
PortService_get_port_profile(RTC_PortService *ps)
{
  RTC_PortProfile *res;
  res = RTC_PortProfile__alloc();

  return res;
}

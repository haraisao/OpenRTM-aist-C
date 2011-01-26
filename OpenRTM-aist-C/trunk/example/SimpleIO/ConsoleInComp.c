/*
   SimpleIO: ConsoleInComp.c


*/

#include <rtm/OpenRTM.h>
#include <strings.h>
#include "ConsoleIn.h"

/*
   Console In Procedure
*/
RTC_ReturnCode_t
MyModuleInit(RTC_Manager *manager)
{
  RTC_RtcBase *comp;
  RTC_ComponentProfile *prof;
  RTC_PortServiceList *portlist;
  int i, n;

  /*
    Userfunction
  */
  ConsoleInInit(manager);

  /*
     Create a component: library
  */
  fprintf(stdout,  "Creating a component: \"ConsoleIn\"....");
  comp = (RTC_RtcBase *)RTC_Manager_createComponent(manager, "ConsoleIn");
  fprintf(stdout,  "succeed.\n");

  prof = RTC_get_component_profile(comp);

  fprintf(stdout, "=================================================\n" );
  fprintf(stdout, " Component Profile\n");
  fprintf(stdout, "-------------------------------------------------\n" );
  fprintf(stdout, "InstanceID:     %s", prof->instance_name );
  fprintf(stdout, "Implementation: %s", prof->type_name );
  fprintf(stdout, "Description:    %s", prof->description );
  fprintf(stdout, "Version:        %s", prof->version );
  fprintf(stdout, "Maker:          %s", prof->vendor );
  fprintf(stdout, "Category:       %s", prof->category );
  fprintf(stdout, "  Other properties   \n");

  NVUtil_dump(prof->properties);

  fprintf(stdout, "=================================================\n");

  portlist = RTC_get_ports(comp);
  n = portlist->_length; 

  for (i=0; i < n; ++i)
  {
    RTC_PortService *port;
    RTC_PortProfile *port_profile;
    RTC_PortInterfaceProfileList *iflist;
    int ProfileLen=0;
    int j;
    const char* pol;

    port = portlist->_buffer[i];
    port_profile = RTC_PortService_get_port_profile(port);

    fprintf(stdout, "=================================================\n");
    if(port_profile != NULL){
      fprintf(stdout, "Port%d (name): %s\n", i, port_profile->name);
    }else{
      fprintf(stdout, "Port%d (name): NoName\n", i);
    }
    fprintf(stdout, "-------------------------------------------------\n");

    iflist = &port_profile->interfaces;
    ProfileLen = iflist->_length;

    for (j=0; i < n; ++j)
    {
        pol = iflist->_buffer[i].polarity == 0 ? "PROVIDED" : "REQUIRED";

        fprintf(stdout, "I/F name: %s\n", iflist->_buffer[j].instance_name);
        fprintf(stdout, "I/F type: %s\n", iflist->_buffer[j].type_name);
        if(iflist->_buffer[j].polarity == 0){
          fprintf(stdout, "Polarity: PROVIDED\n");
        }else{
          fprintf(stdout, "Polarity: REQUIRED\n");
        }
    }

    fprintf(stdout, "- properties -\n");
    NVUtil_dump(port_profile->properties);
    fprintf(stdout, "-------------------------------------------------\n");
  }
  return RTC_RTC_OK;
}

/*
   M A I N
*/
int
main(int argc, char** argv)
{
  RTC_Manager *manager;
  ECMode_t mode = RTC_MGR_NON_BLOCKING;

  manager = RTC_Manager_init(argc, argv);

  RTC_Manager_setModuleInitProc(manager, MyModuleInit);

  RTC_Manager_activateManager(manager);

  RTC_Manager_runManager(manager, mode);

  return 0;
}


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
  RTC_RtcBase comp;
  RTC_ComponentProfile *prof;
  RTC_PortServiceList *portlist;
  CORBA_Environment env;

  int i, n;

  /*
    Userfunction
  */
  ConsoleInInit(manager);

  /*
     Create a component: library
  */
  fprintf(stdout,  "Creating a component: \"ConsoleIn\"....");
  clearEnvironment(&env);

  comp = RTC_Manager_createComponent(manager, "ConsoleIn");

  fprintf(stdout,  "succeed.\n");

  prof = RTC_RTObject_get_component_profile(comp, &env);

  fprintf(stdout, "=================================================\n" );
  fprintf(stdout, " Component Profile\n");
  fprintf(stdout, "-------------------------------------------------\n" );
  fprintf(stdout, "InstanceID:     %s\n", prof->instance_name );
  fprintf(stdout, "Implementation: %s\n", prof->type_name );
  fprintf(stdout, "Description:    %s\n", prof->description );
  fprintf(stdout, "Version:        %s\n", prof->version );
  fprintf(stdout, "Maker:          %s\n", prof->vendor );
  fprintf(stdout, "Category:       %s\n", prof->category );
  fprintf(stdout, "  Other properties   \n");

  NVUtil_dump(prof->properties);

  fprintf(stdout, "=================================================\n");

  portlist = RTC_RTObject_get_ports(comp, &env);
  n = portlist->_length; 

  if(n == 0){
      fprintf(stdout, "No data port found.\n");
  }

  for (i=0; i < n; ++i)
  {
    RTC_PortService *port;
    RTC_PortProfile *port_profile;
    RTC_PortInterfaceProfileList *iflist;
    RTC_PortInterfaceProfile *pip;
    int ProfileLen=0;
    int j;
    const char* pol;

    port = CORBA_sequence_elementAt(portlist,i);
    port_profile = RTC_PortService_get_port_profile(port, &env);

    fprintf(stdout, "=================================================\n");
    if(port_profile != NULL){
      fprintf(stdout, "Port%d (name): %s\n", i, port_profile->name);
    }else{
      fprintf(stdout, "Port%d (name): NoName\n", i);
    }
    fprintf(stdout, "-------------------------------------------------\n");

    iflist = &port_profile->interfaces;
    ProfileLen = iflist->_length;

    for (j=0; j < n; ++j)
    {
        pip = &(iflist->_buffer[j]);
        pol = pip->polarity == 0 ? "PROVIDED" : "REQUIRED";

        fprintf(stdout, "I/F name: %s\n", pip->instance_name);
        fprintf(stdout, "I/F type: %s\n", pip->type_name);
        if(pip->polarity == 0){
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


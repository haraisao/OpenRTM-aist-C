/*


*/

#include <rtm/OpenRTM.h>


/*
 Create RTC_Manager and initialize...

*/
RTC_Manager *
RTC_Manager_init(int argc, char **argv)
{
  RTC_Manager *res = (RTC_Manager *)calloc(1,sizeof(RTC_Manager));

  if(res != NULL){
    res->status = RTC_INACTIVE;
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_init: fail to create manager\n");
  }

  return res;
}

/*
   set an initializing procedure of the RTComponent to the manager.
*/
void 
RTC_Manager_setModuleInitProc(RTC_Manager *manager,
                              RTC_ReturnCode_t (*init_func)(RTC_Manager *manager))
{

  if(manager != NULL){
    manager->module_init_func = init_func;
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_setModuleInitProc: no manager\n");
  }
  return;
}

/*
   activate the manager.
*/
void 
RTC_Manager_activateManager(RTC_Manager *manager)
{
  if(manager != NULL){
    if(manager->module_init_func != NULL){
      RTC_ReturnCode_t res = (manager->module_init_func)(manager);
      if(res == RTC_RTC_OK){
        manager->status = RTC_ACTIVE;
      }else{
         fprintf(stderr, "ERROR in RTC_Manager_activateManager: fail to initilize module\n");
      }
    }else{
      fprintf(stderr, "ERROR in RTC_Manager_activateManager: no init_func\n");
    }
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_activateManager: no manager\n");
  }
  return;
}

/*
   run the manager.
*/
void 
RTC_Manager_runManager(RTC_Manager *manager, ECMode_t mode)
{

  if(manager != NULL){
    manager->status = RTC_RUNNING;
  }else{
    fprintf(stderr, "ERROR in RTC_Manager_runManager: no manager\n");
  }
  return;
}

/*
   stop the manager.
*/
void 
RTC_Manager_stopManager(RTC_Manager *manager)
{

  manager->status = RTC_ACTIVE;
  return;
}


/*
   delete the manager.
*/
void 
RTC_Manager_delete(RTC_Manager *manager)
{
  free(manager);
  return;
}

/*

*/
RTC_RtcBase *
RTC_Manager_createComponent(RTC_Manager *manager, const char *name)
{
  RTC_RtcBase *res;
  res = NULL;
  return res;
}


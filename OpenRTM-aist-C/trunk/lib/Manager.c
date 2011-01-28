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
    RTC_Manager_initManager(res, argc, argv);
    RTC_Manager_initLogger(res);
    RTC_Manager_initORB(res);
    RTC_Manager_initNaming(res);
    RTC_Manager_initFactories(res);
    RTC_Manager_initExecContext(res);
    RTC_Manager_initComposite(res);
    RTC_Manager_initTimer(res);
    RTC_Manager_initManagerServant(res);
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
    manager->ModuleInitProc = init_func;
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
    if(manager->ModuleInitProc != NULL){
      RTC_ReturnCode_t res = (manager->ModuleInitProc)(manager);
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
  res = RTC_DataFlowComponentBase_create(manager);

  return res;
}

/*

*/

void
RTC_Manager_registerFactory(RTC_Manager *manager, RTC_Properties *profile,
                            void *(*creat_func)(RTC_Manager *manager),
			    void (*delete_func)(void **obj))
{

  return;
}

/*
  Initialize RTC Manager
*/
void
RTC_Manager_initManager(RTC_Manager *mgr, int argc, char **argv)
{
  mgr->argc = argc;
  mgr->argv = argv;
  
  mgr->m_config = RTC_Manager_configure(argc, argv);

  return;
}

/*
   Not supported
*/
void
RTC_Manager_initLogger(RTC_Manager *mgr)
{

  return;
}

/*

*/
void
RTC_Manager_initORB(RTC_Manager *mgr)
{
  CORBA_Environment env;

  // ORB initialization
  mgr->m_pORB = (CORBA_ORB)CORBA_ORB_init(&mgr->argc, mgr->argv, 0, &env);

  // Get the RootPOA
  CORBA_Object poa_obj = CORBA_ORB_resolve_initial_references(mgr->m_pORB, "RootPOA", &env);
  mgr->m_pPOA = poa_obj->poa;

  catchDefaultException(&env);

  // Get the POAManager
  mgr->m_pPOAManager =
         (PortableServer_POAManager)PortableServer_POA__get_the_POAManager(mgr->m_pPOA, &env);

  PortableServer_POAManager_activate(mgr->m_pPOAManager, &env);

  return;
}

/*

*/
void
RTC_Manager_initNaming(RTC_Manager *mgr)
{
  mgr->m_namingManager = (RTC_NamingManager *)calloc(1, sizeof(RTC_NamingManager));
  return;
}

/*

*/
void
RTC_Manager_initFactories(RTC_Manager *mgr)
{

  return;
}

/*

*/
void
RTC_Manager_initExecContext(RTC_Manager *mgr)
{

  return;
}

/*

*/
void
RTC_Manager_initComposite(RTC_Manager *mgr)
{

  return;
}

/*

*/
void
RTC_Manager_initTimer(RTC_Manager *mgr)
{

  return;
}

/*

*/
void
RTC_Manager_initManagerServant(RTC_Manager *mgr)
{

  return;
}

/*

*/
RTC_Properties *
RTC_Manager_configure(int argc, char **argv)
{
  int n;
  RTC_Properties *res = NULL;

/*
  n = Properties_setDafaults(res, argv, argc);
 */ 
  return res;
}

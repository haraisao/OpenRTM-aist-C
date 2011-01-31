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
    decompose(arg): args -> id?key0=value0&key1=value1....
*/
int
RTC_Manager_procComponentArgs(const char *args, RTC_Properties *id, RTC_Properties *conf)
{
  return 1;
}
/*

*/
RTC_RtcBase
RTC_Manager_createComponent(RTC_Manager *manager, const char *args)
{
  RTC_RtcBase res;
  CORBA_Environment env;
 
  RTC_Properties *id;
  RTC_Properties *conf;
  RTC_Properties *prop;

  if(RTC_Manager_procComponentArgs(args, id, conf) != 1){
    return NULL;
   }


#if 0
  if(Properties_findNode("exported_ports") != 0){
    char *exported_ports_str = "";
    char *exported_ports_val;
    char **exported_ports;
    int i, len;

    exported_ports_val = Propertirs_getProperty(conf, "exported_ports");
    exported_ports = split_string(exported_ports_val, ',', &len );
    for(i=0; i<len;++i){
      char **keyvals;
      int key_len;
      keyvals =  split_string(exported_ports[i], '.', &key_len);
      if(key_len > 2){
        append_string(exported_ports_str, keyvals[0]);
        append_string(exported_ports_str, ","); 
        append_string(exported_ports_str, keyvals[len -1]);
      }else{
        append_string(exported_ports_str, exported_ports[i]);
      }

      if( i != len -1){
        append_string(exported_ports_str, ",");
      }
    }
    
    Propertirs_setProperty(conf, "exported_ports", exported_ports_str);
    Propertirs_setProperty(conf, "conf.default.exported_ports", exported_ports_str);
  }
#endif 

#if 0
  /*** find factory **/
  FactoryBase *factory = Foctory_find(manager->m_factory, id);
  if(factory == NULL){
      /* module will be automatically loading */
      
      /* after loading modules... , try again*/
      factory = Foctory_find(manager->m_factory, id);
      if(factory == NULL){
        fprintf(stderr, "ERROR: factory not found\n");
        return;
      }
  }
#endif 



#if 0
  prop = factory->profile;
  prop = Properties_appendProperties(prop, conf);
  const char *inherit_prop[] = {
      "exec_cxt.periodic.type",
      "exec_cxt.periodic.rate",
      "exec_cxt.evdriven.type",
      "naming.formats",
      "logger.enable",
      "logger.log_level",
      "naming.enable",
      "naming.type",
      "naming.formats",
      ""
    };

    for(i=0; inherit_prop[i][0] != '\0' ; +i){
      if(Properties_getProperty(prop,inherit_prop[i]) == NULL){
        Properties_setProperty(prop, inherit_prop[i],
          Properties_getProperty(manager->m_config, inherit_prop[i]));
      } 
    }

  res = (factory->create)(manager);
#else
  prop = conf;
  res = RTC_DataFlowComponentBase_create(manager);
#endif
  if(res == NULL){
    fprintf(stderr, "ERROR: Fail to create a cmponent.\n");
    return;
  }

  RTC_Manager_configureComponent(manager, res, prop);

  clearEnvironment(&env);
  if (RTC_RTObject_initialize(res, &env) != RTC_RTC_OK){
#if 0
    (res->exit)();
#endif
    fprintf(stderr, "ERROR: Fail to initialize a cmponent.\n");
  }  

  RTC_RTObject_registerComponent(res);

  return res;
}

/*

*/

void
RTC_Manager_registerFactory(RTC_Manager *manager, char **profile,
                            void *(*create_func)(RTC_Manager *manager),
			    void (*delete_func)(void **obj))
{
  manager->ModuleCreateProc = create_func;
  manager->ModuleDeleteProc = delete_func;

  manager->ModuleProfile = profile;

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
 
#if 0
  mgr->m_module = ModuleManager__new(mgr->m_config);
  mgr->m_terminator = Terminator__new(mgr);
#endif

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
  mgr->m_namingManager = RTC_NamingManager__new(mgr);

  return;
}

/*

*/
void
RTC_Manager_initFactories(RTC_Manager *mgr)
{
#if 0
  RTC_FacoryInit();
#endif
  return;
}

/*

*/
void
RTC_Manager_initExecContext(RTC_Manager *mgr)
{
#if 0
  RTC_PeriodicExecutionContextInit(mgr);
  RTC_ExtTrigExecutionContextInit(mgr);
  RTC_OpenHRPExecutionContextInit(mgr);
#endif

  return;
}

/*

*/
void
RTC_Manager_initComposite(RTC_Manager *mgr)
{
#if 0
  RTC_PeriodicECSharedCompositeInit(mgr);
#endif

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
  CORBA_Environment ev;
  int i, len;
  RTC_Properties *prop;
  char **names;

  mgr->m_mgrservant = impl_RTM_Manager__create(mgr->m_pPOA, &ev);

  prop = Properties_getNode(mgr->m_config,"manager");
  names = split_string(Properties_getProperty(prop,"naming_formats"), ',', &len);

  char *is_master = Properties_getProperty(prop,"is_master");
  if(is_master != NULL &&  strcmp(is_master, "YES") == 0){
    for(i=0;i<len;i++){
      char *mgr_name = Properties_formatString(names[i], prop);
      RTC_NamingManager_bindObject(mgr_name, mgr->m_mgrservant);
    }
  }

  return;
}

/*

*/
RTC_Properties *
RTC_Manager_configure(int argc, char **argv)
{
  int n;
  RTC_Properties *res = NULL;

  n = Properties_setDefaults(res, argv, argc);

  return res;
}

/*

*/
void
RTC_Manager_configureComponent(RTC_Manager *mgr, RTC_RtcBase comp, RTC_Properties *prop)
{

  char *category  = RTC_RTObject_getCategory(comp);
  char *type_name = RTC_RTObject_getTypeName(comp);
  char *inst_name = RTC_RTObject_getInstanceName(comp);
 
  char *type_conf[128];
  char *name_conf[128];

  sprintf(type_conf, "%s.%s,config_file", category, type_name);
  sprintf(name_conf, "%s.%s,config_file", category, inst_name);

  RTC_Properties *type_prop, *name_prop;

  char *conf_file  = Properties_getProperty(mgr->m_config, name_conf);
  if(conf_file != NULL){
    Properties_load(name_prop, conf_file);
  }

  char *type_file  = Properties_getProperty(mgr->m_config, type_conf);
  if(type_file != NULL){
    Properties_load(type_prop, type_file);
  }
  
  RTC_RTObject_appendProperties(comp, prop);

  Properties_appendProperties(type_prop, name_prop);
  RTC_RTObject_appendProperties(comp, type_prop);
 
  /** create component's name for NameService **/
  char naming_formats[256];
  char *naming_name;

  sprintf(naming_formats, "%s, %s", Properties_getProperty(mgr->m_config, "namig_formats"),
                                    RTC_RTObject_getProperty(comp, "namig_formats"));
  Propertties_formatString(naming_formats, RTC_RTObject_getProperties(comp));

  RTC_RTObject_setProperty(comp, "naming.formats", strdup(naming_formats));
  RTC_RTObject_setProperty(comp, "naming.names", naming_name);

  return;
}

/*

*/
void
RTC_Manager_registerComponent(RTC_Manager *mgr, RTC_RtcBase comp)
{
  int i,len;
  char **names;

#if 0
  RTC_ComponentManager_registerObject(mgr->m_compManager, comp);
#endif

  names = RTC_RTObject_getNamingNames(comp, &len);

  for (i = 0; i < len; ++i){
    RTC_NamingManager_bindObject(names[i], comp);
  }

  return;
}


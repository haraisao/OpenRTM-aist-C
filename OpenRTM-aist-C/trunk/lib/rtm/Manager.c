/*


*/

#include <rtm/OpenRTM.h>
#include <rtm/DefaultConfig.h>
#include <sys/utsname.h>

#define STR_BUFSIZE	256

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
  CORBA_Environment env;
  if(manager != NULL){
    manager->status = RTC_RUNNING;
    clearEnvironment(&env);
    CORBA_ORB_run(manager->m_pORB, &env);
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
RTC_Properties *
RTC_Manager_setSystemInformation(RTC_Properties *prop)
{
    char pidc[8];
    struct utsname sysinfo;
    uname(&sysinfo);
    sprintf(pidc, "%d", getpid());

    prop = Properties_setProperty(prop, "manager.os.name",     sysinfo.sysname);
    prop = Properties_setProperty(prop, "manager.os.release",  sysinfo.release);
    prop = Properties_setProperty(prop, "manager.os.version",  sysinfo.version);
    prop = Properties_setProperty(prop, "manager.os.arch",     sysinfo.machine);
    prop = Properties_setProperty(prop, "manager.os.hostname", sysinfo.nodename);
    prop = Properties_setProperty(prop, "manager.pid",         pidc);

  return prop;
}
/*
    decompose(arg): args -> id?key0=value0&key1=value1....
*/
int
RTC_Manager_procComponentArgs(RTC_Manager *mgr, const char *args,
    RTC_Properties **id, RTC_Properties **conf)
{
  int n;
  string_sequence *id_and_conf;

  id_and_conf = split_string((char *)args, '?', 0);

  if(id_and_conf->length > 2){
    fprintf(stderr, "Invalid arguments. Too more '?' in arg: %s\n", args);
    free_string_sequence(id_and_conf);
    return 0;
  }

  n = count_delim(id_and_conf->buffer[0], ':');

  if(n == 0){
    *id = Properties_setProperty(NULL, "RTC", "RTC");
    *id = Properties_setProperty(NULL, "vendor", "");
    *id = Properties_setProperty(NULL, "category", "");
    *id = Properties_setProperty(NULL, "implementation_id", id_and_conf->buffer[0]);
    *id = Properties_setProperty(NULL, "version", "");
  }else if(n == 4){
    string_sequence *id_prop;
    id_prop = split_string((char *)args, ':', 0);
    *id = Properties_setProperty(NULL, "RTC", id_prop->buffer[0]);
    *id = Properties_setProperty(NULL, "vendor", id_prop->buffer[1]);
    *id = Properties_setProperty(NULL, "category", id_prop->buffer[2]);
    *id = Properties_setProperty(NULL, "implementation_id", id_prop->buffer[3]);
    *id = Properties_setProperty(NULL, "version", id_prop->buffer[4]);
    free_string_sequence(id_prop);
  }else{
    fprintf(stderr, "Invalid id type: %s\n", id_and_conf->buffer[0]);
    free_string_sequence(id_and_conf);
    return 0;
  }

  *conf = Properties_createDefaultProperties((const char **)mgr->ModuleProfile);

  if(id_and_conf->length == 2){
    int i;
    string_sequence *confs = split_string(id_and_conf->buffer[1],'&',0);
    
    for(i=0; i<confs->length; i++){
      string_sequence *keyval = split_string(confs->buffer[i], '=', 0);
      if(keyval->length == 2){
         *conf = Properties_setProperty(*conf, keyval->buffer[0], keyval->buffer[2]);
      }
      free_string_sequence(keyval);
    }
    free_string_sequence(confs);
  }

  free_string_sequence(id_and_conf);
  return 1;
}

/*

*/
CORBA_RTC_RTObject
RTC_Manager_createComponent(RTC_Manager *manager, const char *args)
{
  CORBA_RTC_RTObject res;
  CORBA_Environment env;
 
  RTC_Properties *id=NULL;
  RTC_Properties *conf=NULL;
  RTC_Properties *prop=NULL;
  int i;

  if(RTC_Manager_procComponentArgs(manager, args, &id, &conf) != 1){
    return NULL;
   }

#if 0
  if(Properties_findNode("exported_ports") != 0){
    char *exported_ports_str = "";
    char *exported_ports_val;
    string_sequence *exported_ports;

    exported_ports_val = Propertirs_getProperty(conf, "exported_ports");
    exported_ports = split_string(exported_ports_val, ',', 0);

    for(i=0; i<exported_ports->length;++i){
      string_sequence *keyvals;
      int key_len;
      keyvals =  split_string(exported_ports->buffer[i], '.', 0);
      if(keyvals->length > 2){
        append_string(exported_ports_str, keyvals->buffer[0]);
        append_string(exported_ports_str, ","); 
        append_string(exported_ports_str, keyvals->buffer[keyvals->length -1]);
      }else{
        append_string(exported_ports_str, exported_ports->buffer[i]);
      }

      if( i != kexported_poets->length -1){
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

  prop = Properties__new("root");
  prop = Properties_appendProperties(prop, conf);
  prop = RTC_Manager_setSystemInformation(prop);

  const char *inherit_prop[] = {
      "exec_cxt.periodic.type",
      "exec_cxt.periodic.rate",
      "exec_cxt.evdriven.type",
      "naming.formats",
      "logger.enable",
      "logger.log_level",
      "naming.enable",
      "naming.type",
      ""
    };

    for(i=0; inherit_prop[i][0] != '\0' ; i++){
      if(Properties_getProperty(prop,(char *)inherit_prop[i]) == NULL){
        Properties_setProperty(prop, (char *)inherit_prop[i],
          Properties_getProperty(manager->m_config, (char *)inherit_prop[i]));
      } 
    }

  res = RTC_DataFlowComponentBase_create(manager);
#endif

  if(res == NULL){
    fprintf(stderr, "ERROR: Fail to create a component.\n");
    return;
  }
  RTC_RTObject_appendProperties(res, prop);
  char inst_name[STR_BUFSIZE];
  sprintf(inst_name, "%s%d",  RTC_RTObject_getTypeName(res), manager->m_counter);
  manager->m_counter += 1;
  RTC_RTObject_setInstanceName(res,inst_name);

  RTC_Manager_configureComponent(manager, res, prop);

  clearEnvironment(&env);
  if ( RTC_RTObject_initialize(res, &env) != RTC_RTC_OK){
#if 0
    (res->exit)();
#endif
    fprintf(stderr, "ERROR: Fail to initialize a component.\n");
  }

  RTC_Manager_registerComponent(manager, res);

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
  mgr->m_counter = 0;
  
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

  /* ORB initialization */
  mgr->m_pORB = (CORBA_ORB)CORBA_ORB_init(&mgr->argc, mgr->argv, 0, &env);

  /* Get the RootPOA */
#if 0
  CORBA_Object poa_obj = CORBA_ORB_resolve_initial_references(mgr->m_pORB, "RootPOA", &env);
  mgr->m_pPOA = poa_obj->poa;
#else
  mgr->m_pPOA = The_RootPOA;
#endif

  catchDefaultException(&env);

  /* Get the POAManager */
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
  char *type;

  mgr->m_namingManager = RTC_NamingManager__new(mgr);

  type = Properties_getProperty(mgr->m_config, "naming.type");
  if(type == NULL){
    fprintf(stderr, "Invalid naming.type\n");
  }else{
    int i;
    string_sequence *meth = split_string(type, ',', 0);
    for(i=0; i<meth->length;i++){
      char ns[STR_BUFSIZE];
      char *nss;
      int j;
      sprintf(ns, "%s.nameservers", meth->buffer[i]);
      nss = Properties_getProperty(mgr->m_config, ns);
      string_sequence *names = split_string(nss, ',', 0);
      
      for(j=0;j<names->length;j++){
        RTC_NamingManager_registerNameServer(mgr->m_namingManager, meth->buffer[i], names->buffer[j]);
      }
      free_string_sequence(names);
    }
    free_string_sequence(meth);
  }
  return;
}

/*
   Not supported
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
  RTC_PeriodicExecutionContextInit(mgr);
  RTC_ExtTrigExecutionContextInit(mgr);
  RTC_OpenHRPExecutionContextInit(mgr);

  return;
}

/*

*/
void
RTC_Manager_initComposite(RTC_Manager *mgr)
{
  RTC_PeriodicECSharedCompositeInit(mgr);

  return;
}

/*
  Not supported
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
  string_sequence *names;

  mgr->m_mgrservant = impl_RTM_Manager__create(mgr->m_pPOA, &ev);

  prop = Properties_getNode(mgr->m_config,"manager");

  char *value = Properties_getProperty(prop,"naming_formats");

  if(value == NULL){
    names = split_string(value, ',', 0);
  }

  char *is_master = Properties_getProperty(prop,"is_master");

  if(is_master != NULL &&  strcmp(is_master, "YES") == 0){
    for(i=0;i<names->length;i++){
      char *mgr_name = Properties_formatString(names->buffer[i], prop);
      RTC_NamingManager_bindObject(mgr->m_namingManager, mgr_name, mgr->m_mgrservant);
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
  const char *val;
  char *fname = "rtc.conf";
  int i;

#if 0
  res = Properties__new("root");
#else
  res = Properties_make_system_default();
#endif
  res = RTC_Manager_setSystemInformation(res);

#if 0
/*** parse argument and set options **/
  res = Properties_setDefaults(res, argv, argc);
/*** ***/
#endif

  res = Properties_load(res, fname);
#if 0
  Properties_dumpProperties(res, 0);
#endif

  return res;
}

/*

*/
void
RTC_Manager_configureComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp, RTC_Properties *prop)
{
  RTC_Properties *type_prop=NULL, *name_prop=NULL;

  char *category  = RTC_RTObject_getCategory(comp);
  char *type_name = RTC_RTObject_getTypeName(comp);
  char *inst_name = RTC_RTObject_getInstanceName(comp);
 
  char type_conf[128];
  char name_conf[128];

  if(category == NULL){
   fprintf(stderr, "ERROR: category not found\n");
   return ;
  }

  if(type_name == NULL){
   fprintf(stderr, "ERROR: type_name not found\n");
   return ;
  }

  if(inst_name == NULL){
   fprintf(stderr, "ERROR: inst_name not found\n");
   return ;
  }

  sprintf(type_conf, "%s.%s,config_file", category, type_name);
  sprintf(name_conf, "%s.%s,config_file", category, inst_name);


  char *conf_file  = Properties_getProperty(mgr->m_config, name_conf);
  if(conf_file != NULL){
    Properties_load(name_prop, conf_file);
  }

  char *type_file  = Properties_getProperty(mgr->m_config, type_conf);
  if(type_file != NULL){
    Properties_load(type_prop, type_file);
  }

  Properties_appendProperties(type_prop, name_prop);
  RTC_RTObject_appendProperties(comp, type_prop);
 
  /** create component's name for NameService **/
  char naming_formats[STR_BUFSIZE];
  char *naming_name;

  sprintf(naming_formats, "%s, %s", Properties_getProperty(mgr->m_config, "naming.formats"),
                                    RTC_RTObject_getProperty(comp, "naming.formats"));

  naming_name = Properties_formatString(naming_formats, RTC_RTObject_getProperties(comp));

  RTC_RTObject_setProperty(comp, "naming.formats", strdup(naming_formats));
  RTC_RTObject_setProperty(comp, "naming.names", naming_name);
  free(naming_name);

  return;
}

/*

*/
void
RTC_Manager_registerComponent(RTC_Manager *mgr, CORBA_RTC_RTObject comp)
{
  int i,len;
  char **names;

#if 0
  RTC_ComponentManager_registerObject(mgr->m_compManager, comp);
#endif

  names = RTC_RTObject_getNamingNames(comp, &len);

  for (i = 0; i < len; ++i){
    RTC_NamingManager_bindObject(mgr->m_namingManager, names[i], comp);
  }

  return;
}


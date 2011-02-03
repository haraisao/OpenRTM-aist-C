/*


*/

#include <rtm/OpenRTM.h>

/*
 Create RTC_Manager and initialize...

*/
RTC_NamingManager *
RTC_NamingManager__new(RTC_Manager *mgr)
{
  RTC_NamingManager *res = (RTC_NamingManager *)calloc(1,sizeof(RTC_NamingManager));
  res->m_manager = mgr;

  return res;
}

void
RTC_NamingManager_appendNamingBase(RTC_NamingManager *mgr, RTC_Name *name)
{
  if(mgr->n_name == 0){   
    mgr->m_names = malloc(sizeof(RTC_Name *));
  }else{
    mgr->m_names = realloc(mgr->m_names, sizeof(RTC_Name *) * (mgr->n_name + 1));
  }
  mgr->m_names[mgr->n_name] = name;

  if(mgr->m_names != NULL){
    mgr->n_name += 1;
  }
  return;
}

RTC_Name *
RTC_Name__new(char *method, char *name_server, RTC_NamingBase *name)
{
  RTC_Name *res=(RTC_Name *)malloc(sizeof(RTC_Name));
  res->methods = strdup(method);
  res->nsname = strdup(name_server);
  res->name = name;

  return res;
}

void
RTC_NamingManager_registerNameServer(RTC_NamingManager *mgr, 
        const char *method, const char *name_server)
{
  RTC_NamingBase* name = NULL;
  fprintf(stderr, "	registerNameServer: (%s : %s)\n",method, name_server);

  name = RTC_NamingBase_createNamingObj(mgr, (char *)method, (char *)name_server);
  
  RTC_NamingManager_appendNamingBase(mgr, 
	RTC_Name__new((char *)method, (char *)name_server, name));

  return;
}

void
RTC_NamingManager_bindObject(RTC_NamingManager *mgr, const char *name, const RTC_RTObject rtobj)
{
  int i;

  for(i=0; i < mgr->n_name; i++){
    RTC_NamingBase *nb = mgr->m_names[i]->name;
    if (nb != NULL){
      RTC_NamingBase_bindObject(nb, name, rtobj);
    }
  }

#if 0
  registerComponent(name, rtobj);
#endif
}

void
RTC_NamingManager_update(RTC_NamingManager *mgr)
{
  return;
}

void
RTC_NamingManager_unbindObject(RTC_NamingManager *mgr, const char *name)
{
  return;
}

void
RTC_NamingManager_unbindAll(RTC_NamingManager *mgr)
{
  return;
}

RTC_NamingBase *
NamingOnCorba__new(CORBA_ORB orb, char *name_server)
{
  RTC_NamingBase *res = (RTC_NamingBase *)calloc(1, sizeof(RTC_NamingBase));
  res->name_server = strdup(name_server); 
  res->orb = orb; 

  return res;
}

void
NamingOnCorba_delete(RTC_NamingBase *nb)
{
  free(nb->name_server);
  free(nb);
  return;
}

int
NamingOnCorba_connect(RTC_NamingBase *nb)
{
  int res = -1;
  char loc[256];

  clearEnvironment(&nb->env);

  sprintf(loc, "corbaloc::%s/NameService", nb->name_server);

  nb->rootContext = CORBA_ORB_string_to_object(nb->orb, loc, &nb->env);

  if(nb->rootContext == NULL){
    fprintf(stderr, "ERROR : in string_to_object\n\n");
  } 
  res = catchDefaultException(&nb->env);

  return res;
}

RTC_NamingBase *
RTC_NamingBase_createNamingObj(RTC_NamingManager *nm, char *method, char *name_server)
{
  RTC_NamingBase *res = NULL;

  if(strcmp(method, "corba") == 0){
    res = NamingOnCorba__new(nm->m_manager->m_pORB, name_server);
    if(res == NULL){
      fprintf(stderr, "ERROR in creta NamingOnCorba: (%s)\n", name_server);
    }else{
      if(NamingOnCorba_connect(res) == 0){
        fprintf(stderr, "=== NameServer resolve suceeded:%s/%s ===\n", method, name_server);
      }else{
        fprintf(stderr, "=== NameServer resolve fail:%s/%s ===\n", method, name_server);
        NamingOnCorba_delete(res);
        res = NULL;
      }
    }  
  }else{
    fprintf(stderr, "Sorry, unsupport type of NamingService required. (%s)\n", method);
  }
  return res;
}

RTC_NamingBase_bindObject(RTC_NamingBase *nb, char *name, CORBA_Object obj)
{
  CosNaming_Name *namingName;
  string_sequence *names = split_string(name, '/',0);
  int i;

  namingName = CosNaming_Name__alloc();
  namingName->_buffer = CosNaming_Name_allocbuf(names->length);
  namingName->_length = namingName->_maximum = names->length;

  for(i=0;i<names->length;i++){
    char *nn = names->buffer[i];
    if(count_delim(nn, '.') > 0){
      char *str = rindex(nn, '.'); 
      char str1[256];
      memset(str1, 0, 256);
      strncpy(str1, nn, strlen(nn) - strlen(str));
      namingName->_buffer[i].id = strdup(str1);
      namingName->_buffer[i].kind = strdup(str+1);
    }
  }

  clearEnvironment(&nb->env);
  CosNaming_NamingContext_rebind(nb->rootContext, namingName, obj, &nb->env);
  if(catchException(&nb->env, NULL) ){
    fprintf(stderr, "Error, %s \n", nb->env._repo_id );
    return 0;
  }
  
  for(i=0; i < namingName->_maximum ;i++){
    free(namingName->_buffer[i].id);
    free(namingName->_buffer[i].kind);
  }
  free(namingName->_buffer);
  free(namingName);
  
  free_string_sequence(names);
  return 1;
}


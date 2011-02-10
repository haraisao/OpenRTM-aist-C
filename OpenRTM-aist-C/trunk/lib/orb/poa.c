/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 * RtORB:
 *     poa.c
 *
 * Copyright(C) 2006, Isao Hara, AIST
 *
 * $Revision: 1.8 $
 * $Date: 2008/05/29 04:54:56 $
 * $Id: poa.c,v 1.8 2008/05/29 04:54:56 yoshi Exp $
 *
 */
/*!
 * @file poa.c
 * @if jp
 * @brief POA, POA_Managerなどに関する操作関数群。
 * @else
 * @brief Actions for POA, POA_Manager, etc.
 * @endif
 * @author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <RtORB/corba.h>
#include <RtORB/sockport.h>

void
PortableServer_POAManager_activate(PortableServer_POAManager poa_mgr,
		CORBA_Environment *env) 
{
  PortableServer_POA_activate(poa_mgr, env);
  return;
}
/*
 *
 * PortableServer_POA
 *
 **/

/*
 PortableServer::POA
*/
PortableServer_POA
PortableServer_POA_new(char *id, unsigned short port){

  PortableServer_POA poa = (PortableServer_POA)RtORB_calloc(1, sizeof(PortableServer_POA_struct), "PortableServer_POA_new");

  poa->object_map = createHashtable(64);
  poa->_server = GIOP_Connection__create();
  GIOP_Connection__open(poa->_server, port);

  poa->requests = 0;

  set_SockProfile_arg(poa->_server->sock, poa);

  poa->id = (char *)RtORB_strdup(id, "PortableServer_POA_new");
  return poa;
}

/*
 create_POA
*/
PortableServer_POA
PortableServer_POA_createPOA(PortableServer_POA ppoa,
		char *id, 
		PortableServer_POAManager mgr, 
		CORBA_Environment *env)
{
  fprintf(stderr, "!!!! RtORB doesn't support multi POA...\n");
  if(!id) return (PortableServer_POA)NULL;
  PortableServer_POA poa = PortableServer_POA_new(id, 0);

#if 0
  poa->orb = ppoa->orb;
#endif

  return poa;
}

void
PortableServer_POA_activate(PortableServer_POA poa, CORBA_Environment *env) 
{
  if(poa->status == POA_INACTIVE){
    CORBA_system_exception(env, "AdapterInactive");
    return;
  }
  if(poa->status == POA_ACTIVE) return;
  poa->status = POA_ACTIVE;

  set_SockProfile(poa->_server->sock, SOCK_SERVER, NULL, NULL, PortableServer_enqueue_request);
}

void
PortableServer_POA_deactivate(PortableServer_POA poa, CORBA_Environment *env) 
{
   if(poa->status == POA_INACTIVE){
     CORBA_system_exception(env, "AdapterInactive");
     return;
   }
   poa->status = POA_INACTIVE;

   GIOP_Connection__shutdown(poa->_server);

   return;
}

/*
 shutdown
*/
void 
PortableServer_POA_shutdown(PortableServer_POA poa, CORBA_Environment *env) 
{

   poa->status = POA_DISCARDING;

   GIOP_Connection__shutdown(poa->_server);

   return;
}


void
PortableServer_POA_destory(PortableServer_POA poa, CORBA_Environment *env) 
{
  PortableServer_POA_shutdown(poa, env);
  GIOP_Connection__free(poa->_server);
  poa->_server = 0;

  poa->status = POA_INACTIVE;
  return;
}

/*
 get_status
*/
uint32_t
PortableServer_POA_get_state(PortableServer_POA poa, CORBA_Environment *env)
{
   return poa->status;
}

PortableServer_POAManager
PortableServer_POA__get_the_POAManager(PortableServer_POA poa, CORBA_Environment *env){
  return poa;
}

/* change for shmc */
int PortableServer_enqueue_request(GIOP_ConnectionHandler *h){

  PortableServer_POA poa = (PortableServer_POA) GIOP_ConnectionHandler_get_arg(h);

  CORBA_MUTEX_LOCK();
  poa->requests =  (PtrList *)GIOP_enqueue_request(h, poa->requests);
  CORBA_MUTEX_UNLOCK();

  if(poa->requests == NULL ){
	  return -1;
  }
  
  return 1;
}


void PortableServer_execute_request(void *arg){
  PortableServer_POA poa = (PortableServer_POA)arg;

  poa->requests = (PtrList *)GIOP_execute_request(poa, poa->requests);

  return;
}

void POA_main_loop(PortableServer_POA rootPOA){
  server_loop(10000.0, PortableServer_execute_request, rootPOA);

}

/******************************/
PortableServer_ObjectId
PortableServer_POA_activate_object(PortableServer_POA poa, 
		PortableServer_Servant servant, CORBA_Environment *env)
{
  PortableServer_ObjectId obj_id = NULL;
  CORBA_Object obj;
  PortableServer_ServantBase *sb = (PortableServer_ServantBase *)servant;
  RtORB_POA_Object *poa_obj = (RtORB_POA_Object *)sb->_private;

  if(poa_obj == NULL) {
    CORBA_system_exception(env, "Error in PortableServer_POA_activate_object:RtORB_POA_Object is NULL");
  }else{
    obj = poa_obj->obj;
    if(obj == NULL) {
      CORBA_system_exception(env, "Error in PortableServer_POA_activate_object:CORBA_Object is NULL");
    }else{
#if 0
      obj->poa = poa;
#endif
      obj_id = RtORB_strdup((char *)obj->object_key, "PortableServer_POA_activate_object");
      register_PortableServer_Servant(poa, servant, env);
    }
  }
  return obj_id;
}

void register_PortableServer_Servant(PortableServer_POA poa,
		PortableServer_Servant servant, CORBA_Environment *env){

  char *ior = NULL;
  CORBA_Object obj = NULL;
  RtORB_POA_Object *poa_obj;
  PortableServer_ServantBase *sb = (PortableServer_ServantBase *)servant; 


  if(sb->_private){
    obj = ((RtORB_POA_Object *)sb->_private)->obj;
    poa_obj = (RtORB_POA_Object *)sb->_private;
  }else{
    CORBA_system_exception(env, "Error in register Servant");
    return;
  }
  if(!obj){
    CORBA_system_exception(env, "CORBA_Object not bind");
    return;
  }

  ior = ( char* )RtORB_alloc( 1024,"register_PortableServer_Servant");
  memset(ior,0,1024);

  registerItem(poa->object_map, obj->object_key, poa_obj);

  createIOR(ior,poa->_server->sock,(char *)obj->typedId,(char *)obj->object_key);
  obj->_ior_string = (unsigned char *)RtORB_strdup(ior, "register_PortableServer_Servant");
  RtORB_free ( ior,"register_PortableServer_Servant");

  return;
}

CORBA_Object
impl_POA_ServantBase_to_Object(impl_POA_ServantBase *poa_servant){
  RtORB_POA_Object *poa_obj = (RtORB_POA_Object *)poa_servant->servant._private;

  return poa_obj->obj;

}

void RtORB_POA_Object__create(PortableServer_ClassInfo *info,
		PortableServer_Servant servant,
		void (*finalize)(), void *vepv)
{
  PortableServer_ServantBase *sb = (PortableServer_ServantBase *)servant;
  RtORB_POA_Object *poa_obj;

  if(!sb){
    fprintf(stderr, "Error: Invalid Servant \n");
    return;
  }
  poa_obj = (RtORB_POA_Object *)RtORB_alloc(sizeof(RtORB_POA_Object),
		  "RtORB_POA_Object__create");
  memset(poa_obj, 0, sizeof(RtORB_POA_Object));

  poa_obj->impl_serv._private = info;
  poa_obj->obj = (CORBA_Object)new_CORBA_Object(NULL);
  poa_obj->obj->connection = GIOP_Connection__create();
  poa_obj->obj->_url = NULL;
  poa_obj->obj->num_urls = 0;

  poa_obj->obj->impl = info->class_impl;
  poa_obj->obj->typedId = (unsigned char *)RtORB_strdup(info->class_name, "RtORB_POA_Object__create");
  poa_obj->servant = servant;
  poa_obj->obj->servant = servant;

  sb->_private = poa_obj;

  return;
}

void
PortableServer_POA_deactivate_object(PortableServer_POA poa, 
		PortableServer_ObjectId id,
		CORBA_Environment *env)
{

  deleteItem(poa->object_map, id);
  return ;
}

void
PortableServer_POA_reinstall_object(PortableServer_POA poa, 
		CORBA_Object obj, char *object_key, CORBA_Environment *env)
{

  PortableServer_ServantBase *sb;

  if (!obj || !object_key) return;
  deleteItem(poa->object_map, obj->object_key);
  RtORB_free(obj->_ior_string, "PortableServer_POA_reinstall_object");
  RtORB_free(obj->object_key, "PortableServer_POA_reinstall_object");
  obj->object_key = (unsigned char *)RtORB_strdup(object_key, "PortableServer_POA_reinstall_object");

  sb = (PortableServer_ServantBase *)obj->servant;
  register_PortableServer_Servant(poa, sb, env);

  return ;
}

CORBA_Object
PortableServer_POA_servant_to_reference(PortableServer_POA poa,
		PortableServer_Servant servant, CORBA_Environment *env){
  PortableServer_ServantBase *sb;
  RtORB_POA_Object *poa_obj;
  
  sb = (PortableServer_ServantBase *)servant;
  poa_obj = (RtORB_POA_Object *)sb->_private;
#if 0
  if (poa_obj->obj->poa == NULL) {
    poa_obj->obj->poa = poa;
  }
#endif

  return poa_obj->obj;

}

/*
 ServantBase
*/
PortableServer_POA
PortableServer_ServantBase__default_POA(PortableServer_Servant servant, CORBA_Environment *env)
{
  PortableServer_ServantBase *sb = (PortableServer_ServantBase *)servant;

  if (!sb || !sb->_private){
    CORBA_system_exception(env, "PortableServer_ServantBase__default_POA : servant is NULL");
    return NULL;
  }

#if 0
  RtORB_POA_Object *prvt=(RtORB_POA_Object *)sb->_private;
  if(!prvt->poa){
    return prvt->obj->poa;
  }

  return prvt->poa;
#else
  return The_RootPOA;
#endif
}

CORBA_boolean
PortableServer_ServantBase__is_a(PortableServer_Servant servant, const char *id, CORBA_Environment *env){
  int i;
  CORBA_Class_Impl *clsimpl;
  
  PortableServer_ServantBase *sb = (PortableServer_ServantBase *)servant;
  RtORB_POA_Object *poa_obj;
  if (!servant){
    CORBA_system_exception(env, "PortableServer_ServantBase__is_a : Servant is NULL");
    return FALSE;
  }

  poa_obj = (RtORB_POA_Object *)sb->_private;
  PortableServer_ClassInfo *info = (PortableServer_ClassInfo *)poa_obj->impl_serv._private;

  if(!strcmp(id, info->class_name)) return TRUE;

  clsimpl = info->class_impl;
  for (i=0; i<clsimpl->n_base_types; i++) {
    if (!strcmp(id, clsimpl->base_types[i])) { return TRUE; }
  }

  return FALSE;
}

CORBA_boolean
PortableServer_ServantBase__non_existent(PortableServer_Servant servant,  CORBA_Environment *env){
  return FALSE;
}
void
PortableServer_ServantBase__add_ref(PortableServer_Servant servant,  CORBA_Environment *env){
  return ;
}

void
PortableServer_ServantBase__remove_ref(PortableServer_Servant servant,  CORBA_Environment *env){
  return ;
}

void
PortableServer_ServantBase__fini(PortableServer_Servant servant, CORBA_Environment *env){
  RtORB_free(servant,"PortableServer_ServantBase__fini");
  return;
}

void
PortableServer_ServantBase__init(PortableServer_ServantBase *servant, CORBA_Environment *env){
  PortableServer_ServantBase *sb = (PortableServer_ServantBase *)servant;

  if (!sb) {
    CORBA_system_exception(env, "PortableServer_ServantBase__init : servant is NULL");
    return;
  }
  if (!sb->vepv || !sb->vepv[0]){
    CORBA_system_exception(env, "PortableServer_ServantBase__init : servant vepv is NULL");
    return;
  }
  if (!sb->vepv[0]->finalize)
      sb->vepv[0]->finalize = PortableServer_ServantBase__fini; 
  if (!sb->vepv[0]->default_POA)
      sb->vepv[0]->default_POA = PortableServer_ServantBase__default_POA; 
  if (!sb->vepv[0]->is_a)
      sb->vepv[0]->is_a = PortableServer_ServantBase__is_a; 
  if (!sb->vepv[0]->non_existent)
      sb->vepv[0]->non_existent = PortableServer_ServantBase__non_existent; 
  if (!sb->vepv[0]->add_ref)
      sb->vepv[0]->add_ref = PortableServer_ServantBase__add_ref; 
  if (!sb->vepv[0]->remove_ref)
      sb->vepv[0]->remove_ref = PortableServer_ServantBase__remove_ref; 

  return;
}

PortableServer_POA PortableServer_root_POA(CORBA_Environment *ev)
{
  PortableServer_POA poa = NULL;
    if (!The_ORB) {
      return NULL;
    }
#if 0
  poa = (PortableServer_POA) ((CORBA_Object)CORBA_ORB_resolve_initial_references(The_ORB, "RootPOA",  ev))->poa;
#else
  poa = The_RootPOA;
#endif
  return poa;
}

PortableServer_POA PortableServer_POA__narrow(CORBA_Object obj)
{
#if 0
  PortableServer_POA poa = NULL;
  if(obj) poa = obj->poa;
  return poa;
#else
  return The_RootPOA;
#endif
}

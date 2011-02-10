/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*
 *   RtORB:
 *     orb.c
 *
 *   Copyright(C) 2006, Isao Hara, AIST
 *
 *   $Revision: 1.2 $
 *   $Date: 2008/04/11 12:47:39 $
 *   $Id: orb.c,v 1.2 2008/04/11 12:47:39 yoshi Exp $
 *
 */
/*!
 * @file orb.c
 * @if jp
 * @brief CORBA_ORB関連処理群
 * @else
 * @brief CORBA ORB actions.
 * @endif
 * @author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <RtORB/corba.h>

CORBA_ORB  The_ORB;
struct PortableServer_POA_struct  *The_RootPOA;
CORBA_Object  The_RootPOA_Object=NULL;


#ifdef USE_THREAD
pthread_mutex_t CORBA_MUTEX = PTHREAD_MUTEX_INITIALIZER;
#endif

/**********************/
void CORBA_exception_init(CORBA_Environment *env){
   memset(env, 0, sizeof(*env));
   return;
}

char *
CORBA_exception_id(CORBA_Environment *ev){
	return (char *)ev->_repo_id;
}

CORBA_any 
CORBA_exception_value(CORBA_Environment *ev){
  return ev->_params;
}

void
CORBA_exception_free(CORBA_Environment *ev){
  if (ev->_repo_id){
    RtORB_free(ev->_repo_id, "CORBA_exception_free(repo_id)");
  }

  RtORB_free(ev, "CORBA_exception_free");
}

void
set_CORBA_exception(CORBA_Environment *ev, uint32_t id, char *report){
  ev->_major = id;
  ev->_repo_id = (unsigned char *)RtORB_strdup(report, "set_CORBA_exception");
  return;
}

/********************/
void setServiceID(CORBA_Config *cfg, char *argv[]){
 fprintf(stderr, "ServerID = %s\n", argv[1]);
}

void setORBid(CORBA_Config *cfg, char *argv[]){
 fprintf(stderr, "ORBid = %s\n", argv[1]);
}

void setListenEndpoints(CORBA_Config *cfg, char *argv[]){
 fprintf(stderr, "ListenEndpoints = %s\n", argv[1]);
}

void setProprietaryActivation(CORBA_Config *cfg, char *argv[]){
 fprintf(stderr, "ProprietayActivation = %s\n", argv[1]);
}

void setInitRef(CORBA_Config *cfg, char *argv[]){
  char *tmp;
  CORBA_Ref *ref = (CORBA_Ref *)RtORB_alloc(sizeof(CORBA_Ref), "setInitRef");

  tmp = nextToken(&ref->key, argv[1], "=");
  ref->url = RtORB_strdup(tmp+1, "setInitRef");

  cfg->init_ref = PtrList_append(cfg->init_ref, ref, NULL);
}

void setDefaultInitRef(CORBA_Config *cfg, char *argv[]){
  cfg->default_init_ref = argv[1];
}

void setServerPort(CORBA_Config *cfg, char *argv[]){
 cfg->port = (unsigned short)atoi(argv[1]);
}

int checkArgParams(char *argv[], int n){
  int i;
  for(i=0;i<n;i++) if(*argv[i+1] == '-') return 0;
  return 1;
}

int checkArgs(CORBA_Config *cfg, int *argc, char *argv[], int i,
	  char *arg_name, void (*func)(CORBA_Config*,char**), int requires){
   int j;

   if(!strcmp(argv[i], arg_name)){
     if(*argc > i+requires && checkArgParams(&argv[i], requires)){
	(*func)(cfg, &argv[i]);
         for(j=i+requires+1; j < *argc; j++){
            argv[j-requires-1] = argv[j];
        }
       *argc -= requires+1;
       return 1;
   }else{
      fprintf(stderr, "Error: Invalid Option %s \n", arg_name);
      exit(1);
    }
  }
  return 0;
}

/*!
 * @if jp
 * @brief  オブジェクトKeyとURLを出力する。
 * @else
 * @brief  Output Object Key and URL 
 * @endif
 * @param val init_ref(CORBA_Config)
 * @return 1:OK
 */
int32_t
CORBA_Ref__print(void *val)
{
  CORBA_Ref *ref = (CORBA_Ref *)val;
  fprintf(stderr, "object_key = %s, url = %s\n", ref->key, ref->url);
  return 1;
}

/*!
 * @if jp
 * @brief  CORBA_Ref型データのkeyを比較する。
 * @else
 * @brief  Comapre 'key' of CORBA_Ref data.
 * @endif
 * @param val value for comapring
 * @param ref CORBA_Ref data
 * @return 0:UnMatched, else:Matched
 */
int32_t
CORBA_Ref_CompKey(void *val, void *ref)
{
  return (!strcmp((char *)val, ((CORBA_Ref *)ref)->key));
}

/*!
 * @if jp
 * @brief  配列からオブジェクトKeyに一致するURLを取得する。
 * @else
 * @brief  get CORBA URL by Object Key
 * @endif
 * @param refs CORBA URL
 * @param name Object Key
 * @return CORBA_URL (or NULL)
 */
char *
CORBA_Ref_find_url(PtrList *refs, char *name){
  char *res=NULL;
  CORBA_Ref *val=NULL;
  if(refs == NULL) return NULL;

  val = (CORBA_Ref *)PtrList_find_item(refs, name, (int32_t (*)(void*, void *))CORBA_Ref_CompKey);
  if(val != NULL){
    res = val->url;
  }

  return res;
}

CORBA_ORB
CORBA_ORB_init(int *argc, char **argv, char orb_id, CORBA_Environment *env){
	/* 
           Initialize ORB
	   Setup POA, IR, NameingSerive, and other Object Services
	*/
  int i;
  CORBA_ORB orb = (CORBA_ORB)RtORB_calloc(sizeof(CORBA_ORB_struct), 1, "CORBA_ORB_init");

  memset(&orb->cfg, 0, sizeof(CORBA_Config));
  memset(env, 0, sizeof(CORBA_Environment));

  if(*argc > 1){
    for(i=1 ; i < *argc ; i++){
      if(strncmp(argv[i], "-ORB", 4)) continue;
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBServerId", setServiceID, 1);
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBid", setORBid, 1);
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBListenEndpoints", setListenEndpoints, 1);
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBNoProprietaryActivation", setProprietaryActivation, 0);
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBInitRef", setInitRef, 1);
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBDefaultInitRef", setDefaultInitRef, 1);
      i -= checkArgs(&orb->cfg, argc, argv, i, "-ORBServerPort", setServerPort, 1);
    }
  }

  /* init_refs */
  if(orb->cfg.init_ref){
    PtrList_foreach(orb->cfg.init_ref, (void *(*)(void *))CORBA_Ref__print);
  }

  CORBA_Ref_find_url(orb->cfg.init_ref, "NameService");

  orb->hostname = (char *)Get_IP_Address();

  /* create the RootPOA */
  The_RootPOA = PortableServer_POA_new("RootPOA", orb->cfg.port);
#if 0
  The_RootPOA->orb = orb;
#endif
  The_RootPOA->status = POA_HOLDING;

#if 0
  The_RootPOA_Object = new_CORBA_Object("RootPOA");
  The_RootPOA_Object->poa = The_RootPOA;
#endif

  The_ORB = orb;
  return orb;
}

CORBA_Object
CORBA_ORB_resolve_initial_references(CORBA_ORB orb, char *obj_key, 
		CORBA_Environment *env)
{
  CORBA_Object obj=NULL;
  char *url;

  if(strcmp(obj_key, "RootPOA") == 0){
    return The_RootPOA;
//    return The_RootPOA_Object;
  }
  url = CORBA_Ref_find_url(orb->cfg.init_ref, obj_key);

  if(url){
    return CORBA_ORB_string_to_object(orb, (unsigned char *)url, env);
  }

  fprintf(stderr, "Error in getValue %s\n", obj_key);
  CORBA_system_exception(env, "InvalidName");

  return obj;
}

CORBA_Object
new_CORBA_Object(char *object_key){
  CORBA_Object obj = (CORBA_Object)RtORB_alloc(sizeof(CORBA_Object_struct),
		  "new_CORBA_Object");
  memset(obj, 0, sizeof(CORBA_Object_struct));

  obj->ref = 1;
  if(!object_key) obj->object_key = (unsigned char *)new_ObjectID();
  else obj->object_key = (unsigned char *)RtORB_strdup(object_key, "new_CORBA_Object");
#if DEBUG
  fprintf(stderr, "\t[[[Call new_CORBA_Object: (%x)ref=%d\n",obj, obj->ref);
#endif
  return obj;
}

int  CORBA_Object_free(CORBA_Object obj){
#if DEBUG
  fprintf(stderr, "\t[[[Call CORBA_Object_free: (%x)ref=%d\n", obj,obj->ref);
#endif
  if(obj->ref == 0) return 0;

  if(obj->ref > 0) obj->ref -= 1;
  if(obj->ref == 0){
    delete_CORBA_Object(obj);
    return 0;
  }
  return obj->ref;
}

CORBA_Object
CORBA_Object_dup(CORBA_Object obj){
  if(!obj) {
   fprintf(stderr, "Error in CORBA_Object_dup\n");
   return NULL;
  }
  obj->ref += 1;
#if DEBUG 
  fprintf(stderr, "\t[[[Call CORBA_Object_dup: (%x)ref=%d\n", obj,obj->ref);
#endif
  return obj;
}

void
CORBA_Object__set_object_key(CORBA_Object obj, char *key, CORBA_Environment *env){
  RtORB_free(obj->object_key, "CORBA_Object__set_object_key");
  if(!key) obj->object_key = (unsigned char *)new_ObjectID();
  else obj->object_key = (unsigned char *)RtORB_strdup(key, "CORBA_Object__set_object_key");

  return;
}

void
CORBA_Object__narrow(CORBA_Object obj, CORBA_TypeCode tc, CORBA_Environment *env){
  if(obj->typedId) RtORB_free(obj->typedId, "CORBA_Object__narrow");
  obj->typedId = (unsigned char *)RtORB_strdup(tc->repository_id, "CORBA_Object__narrow");

  return;
}

void delete_CORBA_Object(CORBA_Object obj){
  if(!obj) return;
#if DEBUG
  fprintf(stderr, "   Call delete Object %x \n", obj);
  fprintf(stderr, "   Call delete Object %s \n", obj->_ior_string);
#endif
  if(obj->_url){
    CORBA_URL__delete(obj->_url, obj->num_urls);
    RtORB_free(obj->_url, "delete_CORBA_Object(url)");
  }
  String__delete((char *)obj->typedId, "delete_CORBA_Object(typedId)");
  String__delete((char *)obj->object_key, "delete_CORBA_Object(object_key)");

  if(obj->connection){
    String__delete((char *)obj->connection->hostname, "delete_CORBA_Object(connection.hostname)");
  } 
  String__delete((char *)obj->_ior_string, "delete_CORBA_Object(_ior_string)");

  if(obj->servant) RtORB_free(obj->servant,"delete_CORBA_Object(servant)");

/*
  I should check whether poa is RootPOA and whether orb is ROOT.
 
  if(obj->poa) RtORB_free(obj->poa, "PortableServer_POA_struct");
  if(obj->orb) RtORB_free(obj->orb, "CORBA_ORB");
*/


  if(obj->connection) RtORB_free(obj->connection,"GIOP_Connection");
#if 0
  if(obj->impl) RtORB_free(obj->impl, "impl");
#endif

  RtORB_free(obj, "delete_CORBA_Object");

   return;
}

unsigned char *
CORBA_ORB_id(CORBA_ORB orb, CORBA_Environment *env){
  return orb->_id;
}

char *
CORBA_Object__to_string(CORBA_Object obj, CORBA_Environment *env)
{
  char *str = NULL;
  str = (char *)RtORB_alloc( 4096, "CORBA_Object__to_string");
  memset(str,0,4096 );

  createIOR(str, obj->connection->sock, (char *)obj->typedId, (char *)obj->object_key);
  obj->_ior_string = (unsigned char *)RtORB_strdup(str, "__to_string");

  if( str ){
    RtORB_free( str, "CORBA_Object__to_string");
  }

  return (char *)obj->_ior_string;
}

unsigned char *
CORBA_ORB_object_to_string(CORBA_ORB orb, CORBA_Object obj,
		CORBA_Environment *env)
{
  unsigned char *retval;
  char *str = NULL;
  char *ior;

  if(!obj) return NULL;

  str = ( char* )RtORB_alloc( 1024,"CORBA_ORB_object_to_string");
  memset(str,0,1024);

  if(!obj->_ior_string){
    if (obj->connection->sock && obj->typedId && obj->object_key){
      createIOR(str, obj->connection->sock, (char *)obj->typedId, (char *)obj->object_key);
      obj->_ior_string = (unsigned char *)RtORB_strdup(str, "object_to_string");

    }else if (obj->_url->_ior_string){
      ior = Octet2String((octet *)obj->_url->_ior_string, obj->_url->_ior_string_len);
      sprintf(str, "IOR:0%d000000%s", (int)obj->_url->byte_order,ior);
      obj->_ior_string = (unsigned char *)RtORB_strdup(str, "object_to_string");
    }else{
      CORBA_exception_set(env,  CORBA_SYSTEM_EXCEPTION, 
       "Object doesn't have connection or typedId or object_key", NULL);
        if ( str ){
          RtORB_free( str, "CORBA_ORB_object_to_string");
        }
	return NULL;
    }
  }

  retval = obj->_ior_string;

  if ( str ) {
     RtORB_free( str, "CORBA_ORB_object_to_string");
  }
  return retval;
}

CORBA_Object
CORBA_ORB_string_to_object(CORBA_ORB orb, unsigned char *str,
		CORBA_Environment *env)
{
#ifdef DEBUG
  fprintf(stderr, "   [[ Call CORBA_ORB_stringto_object (%s)\n", str);
#endif 
  CORBA_Object obj = new_CORBA_Object(NULL);

  obj->num_urls = parseCorbaURL(&obj->_url, (char *)str);

#if 0
  obj->orb = orb;
#endif

  if(obj->num_urls){
    if(obj->_url[0].protocol == PROTO_RIR){
     delete_CORBA_Object(obj);
     return CORBA_ORB_resolve_initial_references(orb, obj->_url[0].object_key, env);
    }
#ifdef DEBUG
    fprintf(stderr, "\n\tGIOP_Connection_create in CORBA_ORB_string_to_object (%s:%d)\n", obj->_url[0].hostname, obj->_url[0].port);
#endif
    obj->connection = GIOP_Connection__create();
    RtORB_free(obj->connection->hostname, "CORBA_ORB_string_to_object");
    obj->connection->hostname=(unsigned char *)RtORB_strdup(obj->_url[0].hostname, "string_to_object");
    obj->connection->port = obj->_url[0].port;
#if 0
    obj->poa = 0;
#endif
    if(obj->_url[0].type_id){
      obj->typedId = (unsigned char *)obj->_url[0].type_id;
    }
    if(obj->object_key) RtORB_free(obj->object_key, "CORBA_ORB_string_to_object(object_key)");
    obj->object_key = (unsigned char *)RtORB_strdup(obj->_url[0].object_key, "CORBA_ORB_string_to_object");

  }else{
    obj->connection = NULL;
#if 0
    obj->poa = 0;
#endif
  }
  return obj;
}

boolean
CORBA_ORB_get_service_information(CORBA_ORB orb,
		unsigned short service_type,
		CORBA_ServiceInforamtion *service_information,
		CORBA_Environment *env) 
{
	return FALSE;
}

void 
CORBA_ORB_get_default_context(CORBA_ORB orb, CORBA_Context *ctx,
		CORBA_Environment *env) 
{
   ctx = (CORBA_Context *)RtORB_alloc(sizeof(CORBA_Context),
		   "CORBA_ORB_get_default_context");
   memset(ctx, 0, sizeof(CORBA_Context));
   return;
}

boolean
CORBA_ORB_work_pending(CORBA_ORB orb, CORBA_Environment *env){
  return FALSE;
}

void
CORBA_ORB_perform_work(CORBA_ORB orb, CORBA_Environment *env){
  return ;
}

void 
CORBA_ORB_run(CORBA_ORB orb,  CORBA_Environment *env) {
  POA_main_loop( The_RootPOA );
  return;
}

void 
CORBA_ORB_shutdown(CORBA_ORB orb, boolean wait_for_completion,
		CORBA_Environment *env) 
{
   return;
}

void
CORBA_ORB_destroy(CORBA_ORB orb, CORBA_Environment *env){
  The_ORB=NULL;

  PortableServer_POA_destory(The_RootPOA, env);
#if 0
  CORBA_Object_free(The_RootPOA_Object);
#endif

  RtORB_free(orb->hostname, "destroy_hostname");
  RtORB_free(orb, "CORBA_ORB_destory");
  return;
}

/******** Object *********/

CORBA_Object 
CORBA_Object_duplicate(CORBA_Object object, CORBA_Environment *env){
  object->ref++;
  return object;
}

void 
CORBA_Object_release(CORBA_Object object, CORBA_Environment *env){
  if( object->ref <= 0) return;
  object->ref--;
  return ;
}

boolean
CORBA_Object_is_nil(CORBA_Object object, CORBA_Environment *env){
  if(object->ref == 0) return TRUE;
  return FALSE;
}

boolean
CORBA_Object_is_a(CORBA_Object object,
		unsigned char *logical_type_id,
		CORBA_Environment *env)
{
  if(!strcmp((char *)logical_type_id, "IDL:omg.org/CORBA/Object:1.0")) return TRUE;
  return FALSE;
}

boolean
CORBA_Object_non_existent(CORBA_Object object, CORBA_Environment *env){
  if(object->ref == 0) return FALSE;
  return TRUE;
}

uint32_t
CORBA_Object_hash(CORBA_Object object,
		uint32_t maximum,
		CORBA_Environment *env){
  uint32_t val = elfhash(object->object_key);

  if(maximum) val =  val % maximum;
  return val;
}

boolean
CORBA_Object_is_equivalent(CORBA_Object object,
		CORBA_Object other_object,
		CORBA_Environment *env){
  if (!object || !other_object) { return FALSE; }

  /* First, compare typedId if exist. They might be empty. */
  if(object->typedId && other_object->typedId
     && strcmp((char *)object->typedId, (const char *)other_object->typedId) == 0) {
    return TRUE;
  }
  /* Second, compare object_key */
  if (object->object_key && object->object_key &&
      strcmp((char *)object->object_key, (const char *)other_object->object_key) == 0) {
    return TRUE;
  }
  return FALSE;
}


CORBA_Object
CORBA_Object_get_component( CORBA_Object object,
		CORBA_Environment *env)
{
  return object;
}

CORBA_ORB
CORBA_Object_get_orb( CORBA_Object object,
		CORBA_Environment *env)
{
#if 0
  return object->orb;
#else
  return The_ORB;
#endif
}


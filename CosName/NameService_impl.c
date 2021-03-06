/* This is a template file generated by command */
/* rtorb-idl --skeleton-impl CosNaming.idl */
/* User must edit this file, inserting servant  */
/* specific code between markers. */

#include "CosNaming.h"

#ifdef USE_THREAD
#include <pthread.h>
static pthread_mutex_t GLOBAL_SOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
#define SOCKET_LOCK() pthread_mutex_lock(&GLOBAL_SOCK_MUTEX)
#define SOCKET_UNLOCK() pthread_mutex_unlock(&GLOBAL_SOCK_MUTEX)
#else
#define SOCKET_LOCK() 
#define SOCKET_UNLOCK() 
#endif


#define MIN(x,y)	(((x) < (y)) ? (x) : (y))

/*** App-specific servant structures ***/
typedef struct
{
  POA_CosNaming_NamingContext servant;
  PortableServer_POA poa;

  /* ------ add private attributes here ------ */
  struct PrtList_struct *ObjectList;
  CosNaming_BindingList *binding_list;
  /* ------ ---------- end ------------ ------ */
} impl_POA_CosNaming_NamingContext;

typedef struct
{
  POA_CosNaming_BindingIterator servant;
  PortableServer_POA poa;

  /* ------ add private attributes here ------ */
  /* ------ ---------- end ------------ ------ */
} impl_POA_CosNaming_BindingIterator;


typedef struct
{
  POA_CosNaming_NamingContextExt servant;
  PortableServer_POA poa;

  /* ------ add private attributes here ------ */
  struct PrtList_struct *ObjectList;
  CosNaming_BindingList *binding_list;
  /* ------ ---------- end ------------ ------ */
} impl_POA_CosNaming_NamingContextExt;


/*** Implementation stub prototypes ***/
static void
impl_CosNaming_NamingContext__destroy (impl_POA_CosNaming_NamingContext *
				       servant, CORBA_Environment * ev);

static CORBA_boolean
impl_CosNaming_NamingContext__is_a (impl_POA_CosNaming_NamingContext *
				    servant, const CORBA_char * id,
				    CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_bind (impl_POA_CosNaming_NamingContext * servant,
				   CosNaming_Name * n,
				   CORBA_Object obj, CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_rebind (impl_POA_CosNaming_NamingContext *
				     servant, CosNaming_Name * n,
				     CORBA_Object obj,
				     CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_bind_context (impl_POA_CosNaming_NamingContext *
					   servant, CosNaming_Name * n,
					   CosNaming_NamingContext nc,
					   CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_rebind_context (impl_POA_CosNaming_NamingContext
					     * servant, CosNaming_Name * n,
					     CosNaming_NamingContext nc,
					     CORBA_Environment * ev);

static CORBA_Object
impl_CosNaming_NamingContext_resolve (impl_POA_CosNaming_NamingContext *
				      servant, CosNaming_Name * n,
				      CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_unbind (impl_POA_CosNaming_NamingContext *
				     servant, CosNaming_Name * n,
				     CORBA_Environment * ev);

static CosNaming_NamingContext
impl_CosNaming_NamingContext_new_context (impl_POA_CosNaming_NamingContext *
					  servant, CORBA_Environment * ev);

static CosNaming_NamingContext
impl_CosNaming_NamingContext_bind_new_context
(impl_POA_CosNaming_NamingContext * servant, CosNaming_Name * n, CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_destroy (impl_POA_CosNaming_NamingContext *
				      servant, CORBA_Environment * ev);

static void
impl_CosNaming_NamingContext_list (impl_POA_CosNaming_NamingContext * servant,
				   CORBA_unsigned_long how_many,
				   CosNaming_BindingList ** bl,
				   CosNaming_BindingIterator * bi,
				   CORBA_Environment * ev);
static void
impl_CosNaming_BindingIterator__destroy (impl_POA_CosNaming_BindingIterator *
					 servant, CORBA_Environment * ev);
static CORBA_boolean
impl_CosNaming_BindingIterator_next_one (impl_POA_CosNaming_BindingIterator *
					 servant, CosNaming_Binding ** b,
					 CORBA_Environment * ev);
static CORBA_boolean
impl_CosNaming_BindingIterator_next_n (impl_POA_CosNaming_BindingIterator *
				       servant, CORBA_unsigned_long how_many,
				       CosNaming_BindingList ** bl,
				       CORBA_Environment * ev);

static void
impl_CosNaming_BindingIterator_destroy (impl_POA_CosNaming_BindingIterator *
					servant, CORBA_Environment * ev);

/*** epv structures ***/

static PortableServer_ServantBase__epv impl_CosNaming_NamingContext_base_epv = {
  NULL,				/* _private data */
  (void (*)(void *, CORBA_Environment *)) &impl_CosNaming_NamingContext__destroy,	/* finalize routine */
  NULL,				/* default_POA routine */
};

static POA_CosNaming_NamingContext__epv impl_CosNaming_NamingContext_epv = {
  NULL,				/* _private */

  (CORBA_boolean (*)(void *, const CORBA_char *, CORBA_Environment *)) &
    impl_CosNaming_NamingContext__is_a,

  (void (*)(void *, CosNaming_Name *, CORBA_Object, CORBA_Environment *))
    &impl_CosNaming_NamingContext_bind,

  (void (*)(void *, CosNaming_Name *, CORBA_Object, CORBA_Environment *))
    &impl_CosNaming_NamingContext_rebind,

  (void (*)
   (void *, CosNaming_Name *, CosNaming_NamingContext,
    CORBA_Environment *)) &impl_CosNaming_NamingContext_bind_context,

  (void (*)
   (void *, CosNaming_Name *, CosNaming_NamingContext,
    CORBA_Environment *)) &impl_CosNaming_NamingContext_rebind_context,

  (CORBA_Object (*)(void *, CosNaming_Name *, CORBA_Environment *)) &
    impl_CosNaming_NamingContext_resolve,

  (void (*)(void *, CosNaming_Name *, CORBA_Environment *))
    &impl_CosNaming_NamingContext_unbind,

  (CosNaming_NamingContext (*)(void *, CORBA_Environment *)) &
    impl_CosNaming_NamingContext_new_context,

  (CosNaming_NamingContext (*)(void *, CosNaming_Name *, CORBA_Environment *))
    & impl_CosNaming_NamingContext_bind_new_context,

  (void (*)(void *, CORBA_Environment *))
    &impl_CosNaming_NamingContext_destroy,

  (void (*)
   (void *, CORBA_unsigned_long, CosNaming_BindingList **,
    CosNaming_BindingIterator *,
    CORBA_Environment *)) &impl_CosNaming_NamingContext_list,

};

static PortableServer_ServantBase__epv impl_CosNaming_BindingIterator_base_epv
  = {
  NULL,				/* _private data */
  (void (*)(void *, CORBA_Environment *)) &impl_CosNaming_BindingIterator__destroy,	/* finalize routine */
  NULL,				/* default_POA routine */
};

static POA_CosNaming_BindingIterator__epv impl_CosNaming_BindingIterator_epv = {
  NULL,				/* _private */
  (CORBA_boolean (*)(void *, CosNaming_Binding **, CORBA_Environment *)) &
    impl_CosNaming_BindingIterator_next_one,

  (CORBA_boolean (*)
   (void *, CORBA_unsigned_long, CosNaming_BindingList **,
    CORBA_Environment *)) & impl_CosNaming_BindingIterator_next_n,

  (void (*)(void *, CORBA_Environment *))
    &impl_CosNaming_BindingIterator_destroy,

};

/*** vepv structures ***/
static POA_CosNaming_NamingContext__vepv impl_CosNaming_NamingContext_vepv = {
  &impl_CosNaming_NamingContext_base_epv,
  &impl_CosNaming_NamingContext_epv,
};

static POA_CosNaming_BindingIterator__vepv impl_CosNaming_BindingIterator_vepv
  = {
  &impl_CosNaming_BindingIterator_base_epv,
  &impl_CosNaming_BindingIterator_epv,
};

/******************* NameContext ***************************/

CosNaming_Name *
rest_of_CosNaming_Name(CosNaming_Name *name, int pos){
  int i;
  if(!name) return NULL;
  if(pos < name->_length - 1){
      CosNaming_Name *n = CosNaming_Name__alloc();
      n->_length = n->_maximum = name->_length - pos;
      n->_buffer = CosNaming_Name_allocbuf(n->_length);
      for(i=0;i<n->_length;i++){
	 n->_buffer[i].id = RtORB_strdup(name->_buffer[pos + i].id, "rest_of_CosNaming_Name");
	 n->_buffer[i].kind = RtORB_strdup(name->_buffer[pos + i].kind, "rest_of_CosNaming_Name");
      }
      return n;
  }
  return NULL;
}

void
free_CosNaming_Name(CosNaming_Name *name)
{
  int i;
  if(!name) return;
  for(i=0;i<name->_length;i++){
    free(name->_buffer[i].id);
    free(name->_buffer[i].kind);
  }
  free(name->_buffer);
  free(name);
  return;
}

/*  Exceptions */
void CosNaming_NotFound__set(CORBA_Environment *ev, long why, CosNaming_Name *rest, int pos){
   CosNaming_NamingContext_NotFound *ex =
	  (CosNaming_NamingContext_NotFound *)RtORB_alloc(sizeof(CosNaming_NamingContext_NotFound), "CosNaming_NotFound");

   ex->why = why;
#if 0
   ex->rest_of_name._length = rest->_length - pos;
   ex->rest_of_name._maximum = rest->_maximum - pos;
   ex->rest_of_name._release = rest->_release;
   ex->rest_of_name._buffer = rest_of_CosNaming_Name((CosNaming_Name *)rest->_buffer, pos);
#else
   ex->rest_of_name._length = 0;
   ex->rest_of_name._maximum = 0;
   ex->rest_of_name._release = 1;
   ex->rest_of_name._buffer = NULL;
#endif

   CORBA_user_exception_set(ev, ex_CosNaming_NamingContext_NotFound,
		   TC_CosNaming_NamingContext_NotFound, ex);
   return;
}

void CosNaming_CannotProceed__set(CORBA_Environment *ev, CosNaming_NamingContext cxt, CosNaming_Name *rest, int pos){
   CosNaming_NamingContext_CannotProceed *ex =
	  (CosNaming_NamingContext_CannotProceed *)RtORB_alloc(sizeof(CosNaming_NamingContext_CannotProceed), "CosNaming_CannotProceed");

   ex->cxt = CORBA_Object_dup(cxt);
#if 0
   ex->rest_of_name._length = rest->_length - pos;
   ex->rest_of_name._maximum = rest->_maximum - pos;
   ex->rest_of_name._release = rest->_release;
   ex->rest_of_name._buffer = rest_of_CosNaming_Name((CosNaming_Name *)rest->_buffer, pos);
#else
   ex->rest_of_name._length = 0;
   ex->rest_of_name._maximum = 0;
   ex->rest_of_name._release = 1;
   ex->rest_of_name._buffer = NULL;
#endif

   CORBA_user_exception_set(ev, ex_CosNaming_NamingContext_CannotProceed,
		   TC_CosNaming_NamingContext_CannotProceed, ex);
//   CORBA_exception_set(ev, CORBA_USER_EXCEPTION, ex_CosNaming_NamingContext_CannotProceed, (void *)ex);
   return;
}

void CosNaming_InvalidName__set(CORBA_Environment *ev){
   CORBA_exception_set(ev, CORBA_USER_EXCEPTION, ex_CosNaming_NamingContext_InvalidName, (void *)NULL);
   return;
}

void CosNaming_AlreadyBound__set(CORBA_Environment *ev){
   CORBA_exception_set(ev, CORBA_USER_EXCEPTION, ex_CosNaming_NamingContext_AlreadyBound, (void *)NULL);
   return;
}

void CosNaming_NotEmpty__set(CORBA_Environment *ev){
   CORBA_exception_set(ev, CORBA_USER_EXCEPTION, ex_CosNaming_NamingContext_NotEmpty, (void *)NULL);
   return;
}

void CosNaming_InvalidAddress__set(CORBA_Environment *ev){
   CORBA_exception_set(ev, CORBA_USER_EXCEPTION, ex_CosNaming_NamingContextExt_InvalidAddress, (void *)NULL);
   return;
}

/*******/

enum {
   CONTEXT = 1, OBJECT, OTHER
};

typedef struct BindObject{
   int type;
   CosNaming_NameComponent name;
   void *object;
}BindObject;

BindObject *
BindObject__alloc(int typ){
  BindObject *bo = (BindObject *)RtORB_alloc(sizeof(BindObject), "BindObject__alloc");
  memset(bo, 0, sizeof(BindObject));
  bo->type = typ;
  return bo;
}

void
BindObject__free(BindObject *bo){
  if(!bo) return;
  String__delete(bo->name.id, "BindObject__free(name.id)");
  String__delete(bo->name.kind, "BindObject__free(name.kind)");

  if(bo->object){
    if(bo->type == OBJECT){
      delete_CORBA_Object(bo->object);
    }
    else if(bo->type == CONTEXT){
      delete_CORBA_Object(bo->object);
      // BindObject__free((BindObject *)bo->object);
    }
  }
  free(bo);
}

boolean
BindObject_compare(BindObject *bo, CosNaming_NameComponent *nc){
  if(!bo || !nc) return FALSE;
  if(strcmp(bo->name.id, nc->id) == 0 && 
     strcmp(bo->name.kind, nc->kind) == 0 ){
	  return TRUE;
  }else{
	  return FALSE;
  }
}

PtrList *
ContextList__find_item(PtrList *lst, CosNaming_NameComponent *nc){
  if(!lst) return NULL;
  PtrList *tmp = (PtrList *)PtrList_first(lst);

  for(;tmp; tmp=tmp->next){
     if(BindObject_compare((BindObject *)tmp->item, nc)) break;
  }
  return tmp;
}

BindObject *
ContextList__resolve(PtrList *lst, CosNaming_NameComponent *nc){
  PtrList *tmp = ContextList__find_item(lst, nc);
  if(tmp) return (BindObject *)tmp->item;
  return NULL;
}

BindObject *
NamingContext_resolve_BindObject(impl_POA_CosNaming_NamingContext *
                                     servant, CosNaming_Name * n,
				     int depth,
                                     CORBA_Environment * ev)
{
    int i;
    impl_POA_CosNaming_NamingContext *srvt = servant;
    BindObject *tmp;


    for(i=0;i < n->_length - 1 && i < depth -1; i++){

        tmp = ContextList__resolve((PtrList *)srvt->ObjectList, &n->_buffer[i]);
        if(!tmp || tmp->type != CONTEXT){
          CosNaming_NotFound__set(ev, 0, n, i);
	  return NULL;
	}
        CORBA_Object _obj = (CORBA_Object)tmp->object;
        srvt = (impl_POA_CosNaming_NamingContext *)_obj->servant;
     }

     tmp = ContextList__resolve((PtrList *)srvt->ObjectList, &n->_buffer[i]);

     if(!tmp){

        CosNaming_NotFound__set(ev, 0, n, i);
     }

     return tmp;
}

PtrList **
NamingContext__resolve_ObjectList(impl_POA_CosNaming_NamingContext * servant,
			  CosNaming_Name * name,
			  CORBA_Environment * ev)
{
   BindObject *bo;

   if(name->_length > 1){
     bo = NamingContext_resolve_BindObject(servant, name, name->_length -1,  ev);

     if(!bo || bo->type != CONTEXT){
	fprintf(stderr, "bind :Bad Context Name..\n");
	CORBA_system_exception(ev, "Bad context name");
        return NULL;
     }
     CORBA_Object obj = (CORBA_Object)bo->object;
     return (PtrList **)&((impl_POA_CosNaming_NamingContext *)obj->servant)->ObjectList;
   }else{
     return (PtrList **)&servant->ObjectList;
   }
}

PtrList *
BindObject__append(PtrList *lst, int typ, CosNaming_NameComponent *nc, CORBA_Object obj){
   BindObject *item = BindObject__alloc(typ);
   item->name.id = RtORB_strdup(nc->id, "BindObject__append:id");
   item->name.kind = RtORB_strdup(nc->kind, "BindObject__append:kind");
   item->object = obj;
#if DEBUG
   fprintf(stderr, "BindObject__append %x \n", (int)item );
#endif
   return PtrList_append(lst, (void *)item, (void (*)(void **))BindObject__free);

}

void print_CosNaming_Name(CosNaming_Name *name)
{

  int i;
  int len=name->_length;

  for(i=0;i<len-1;i++){
    fprintf(stderr, "%s/%s :", name->_buffer[i].id, name->_buffer[i].kind);
  }
  fprintf(stderr, "%s/%s \n", name->_buffer[i].id, name->_buffer[i].kind);
  return;
}

CORBA_sequence_CosNaming_NameComponent *
addNamingComponent(CORBA_sequence_CosNaming_NameComponent *ncp, BindObject *bo)
{
  CORBA_sequence_CosNaming_NameComponent *res;
  int i;
  if(ncp == NULL){
    res= CORBA_sequence_CosNaming_NameComponent__alloc();
    res->_length = res->_maximum = 1;
    res->_buffer = CORBA_sequence_CosNaming_NameComponent_allocbuf(1);
    res->_buffer[0].id = strdup(bo->name.id);
    res->_buffer[0].kind = strdup(bo->name.kind);
 }else{
    CosNaming_NameComponent *buf;
    int len = ncp->_length;
    res = ncp;
    res->_length = res->_maximum = len+1;
    buf = CORBA_sequence_CosNaming_NameComponent_allocbuf(len+1);
    for(i=0;i<len;i++){
      buf[i].id = res->_buffer[i].id;
      buf[i].kind = res->_buffer[i].kind;
    }
    buf[i].id =  strdup(bo->name.id);
    buf[i].kind = strdup(bo->name.kind);
    free(res->_buffer);
    res->_buffer = buf;
  }
  return res;
}

CORBA_sequence_CosNaming_NameComponent *
mkNamingComponent(CORBA_sequence_CosNaming_NameComponent *prefix, BindObject *bo)
{

  CORBA_sequence_CosNaming_NameComponent *res;
  int i;
  int len=0;

  res= CORBA_sequence_CosNaming_NameComponent__alloc();
  if(prefix != NULL){ 
    len = prefix->_length;
  }
  res->_length = res->_maximum = len+1;
  res->_buffer = CORBA_sequence_CosNaming_NameComponent_allocbuf(len+1);
  for(i=0;i<len;i++){
    res->_buffer[i].id = strdup(prefix->_buffer[i].id);
    res->_buffer[i].kind = strdup(prefix->_buffer[i].kind);
  }
  res->_buffer[i].id =  strdup(bo->name.id);
  res->_buffer[i].kind = strdup(bo->name.kind);

  return res;
}

void
delete_CosNaming_Name(CosNaming_Name *name)
{

  int i;
  int len=name->_length;

  for(i=0;i<len;i++){
    RtORB_free(name->_buffer[i].id, "delete_CosNaming_Name(id)");
    RtORB_free(name->_buffer[i].kind, "delete_CosNaming_Name(kind)");
  }
//  RtORB_free(name, "delete_CosNaming_Name");
  return ;
}

void
delete_BindingList(CosNaming_BindingList *bl)
{
  int i;
  int len=bl->_length;

  for(i=0; i < len; i++){
    CosNaming_Binding *bi = &bl->_buffer[i];
    delete_CosNaming_Name(&bi->binding_name);
  }
  RtORB_free(bl->_buffer, "delete_BindingList");
  bl->_buffer=NULL;
  bl->_length = bl->_maximum = 0;
  return;
}

void
set_CosNaming_Name(CORBA_sequence_CosNaming_NameComponent *name, BindObject *bo)
{
  name->_length = name->_maximum = 1;
  name->_buffer = CORBA_sequence_CosNaming_NameComponent_allocbuf(1);

  name->_buffer[0].id =  strdup(bo->name.id);
  name->_buffer[0].kind = strdup(bo->name.kind);

  return;
}

void
copyNamingComponent(CosNaming_NameComponent *buf, BindObject *bo)
{
  buf->id = strdup(bo->name.id);
  buf->kind = strdup(bo->name.kind);
  return;
}

int ObjectList__length(impl_POA_CosNaming_NamingContext * servant){
  int i;
  int len = PtrList_length((PtrList *)servant->ObjectList);
  int res=0;

  for(i=0; i<len;i++){
    BindObject *bo = (BindObject *)PtrList_get_item((PtrList *)servant->ObjectList, i);
    if(bo != NULL) {
      res += 1;
      if(bo->type == CONTEXT){
        CORBA_Object obj = (CORBA_Object)bo->object;
        res += ObjectList__length((impl_POA_CosNaming_NamingContext *)obj->servant);
      }
    }
  }
  return res;
}

void CosNaming_Name_setval(CosNaming_Name *from, CosNaming_Name *to){
  int len = from->_length;

  to->_length = to->_maximum = len;
  to->_buffer = from->_buffer;
  free(from);
}

int
collectBinding(impl_POA_CosNaming_NamingContext * servant,int idx,
  CosNaming_Binding *b, CORBA_sequence_CosNaming_NameComponent *prefix)
{
  int i;

  SOCKET_LOCK();
  int len = PtrList_length((PtrList *)servant->ObjectList);

  for(i=0; i < len; i++){
    CosNaming_Binding *bi = &b[idx];
    BindObject *bo = (BindObject *)PtrList_get_item((PtrList *)servant->ObjectList, i);
    if(bo != NULL) {
      CosNaming_Name_setval(mkNamingComponent(prefix, bo), &bi->binding_name);
      print_CosNaming_Name(&bi->binding_name);
      idx++;
      if(bo->type == CONTEXT){
        bi->binding_type = CosNaming_ncontext;
        CORBA_Object obj = (CORBA_Object)bo->object;
        idx = collectBinding(obj->servant, idx, b, &bi->binding_name);
      }else{
        bi->binding_type = CosNaming_nobject;
      }
    }
  }
  SOCKET_UNLOCK();
  return idx;
}

impl_POA_CosNaming_NamingContext *
bind_new_context(impl_POA_CosNaming_NamingContext * servant,
   CosNaming_Name * n, int depth, CORBA_Environment * ev)
{
  int i;
  CosNaming_NameComponent *nc;
  impl_POA_CosNaming_NamingContext *srvt = servant;
  BindObject *bo;

  memset(ev, 0, sizeof(ev));

  SOCKET_LOCK();
//  PtrList *obj_list=(PtrList *)servant->ObjectList;

  if(depth > n->_length || depth < 0){
    depth = n->_length;
  }

  SOCKET_UNLOCK();

  for(i = 0 ; i < depth; i++){

    bo = NamingContext_resolve_BindObject(servant, n, i,  ev);

    if(!bo){
  SOCKET_LOCK();
      CORBA_Object retval = impl_CosNaming_NamingContext__create(servant->poa, ev); 
      nc = &n->_buffer[i];
      srvt->ObjectList = (void *)PtrList_first(BindObject__append((PtrList *)srvt->ObjectList, CONTEXT, nc, retval));
      srvt = (impl_POA_CosNaming_NamingContext *)retval->servant;
//      obj_list = (PtrList *)srvt->ObjectList;
  SOCKET_UNLOCK();

    }else if( bo->type != CONTEXT){
      fprintf(stderr, "This Name is already bounded, but it isn't contenxt..\n");
      return NULL;
    }else{
  SOCKET_LOCK();
      CORBA_Object obj = (CORBA_Object)bo->object;
      srvt = (impl_POA_CosNaming_NamingContext *)obj->servant;
//      obj_list = (PtrList *)srvt->ObjectList;
  SOCKET_UNLOCK();
    }
  }

  return srvt;
}


/***********************************************************/

/*** Stub implementations ***/

CORBA_CosNaming_NamingContext
       impl_CosNaming_NamingContext__create (PortableServer_POA poa,
					     CORBA_Environment * ev)
{
  CORBA_CosNaming_NamingContext retval;
  impl_POA_CosNaming_NamingContext *newservant;
  PortableServer_ObjectId objid;

  newservant =
    (impl_POA_CosNaming_NamingContext *) RtORB_calloc (1,
						       sizeof
						       (impl_POA_CosNaming_NamingContext),
						       " create...");
  newservant->servant.vepv = &impl_CosNaming_NamingContext_vepv;
  newservant->poa = poa;
  POA_CosNaming_NamingContext__init ((PortableServer_Servant) newservant, ev);
  /* Before servant is going to be activated all
   * private attributes must be initialized.  */

  /* ------ init private attributes here ------ */

   newservant->ObjectList = NULL;
   newservant->binding_list = NULL;

  /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object (poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference (poa, newservant, ev);

  return retval;
}

static void
impl_CosNaming_NamingContext__destroy (impl_POA_CosNaming_NamingContext *
				       servant, CORBA_Environment * ev)
{
  CORBA_Object_release ((CORBA_Object) servant->poa, ev);

  /* No further remote method calls are delegated to 
   * servant and you may free your private attributes. */
  /* ------ free private attributes here ------ */

  SOCKET_LOCK();
  PtrList_remove_item_all((PtrList *)servant->ObjectList);
  SOCKET_UNLOCK();

  /* ------ ---------- end ------------- ------ */

  POA_CosNaming_NamingContext__fini ((PortableServer_Servant) servant, ev);

  RtORB_free (servant, "servant");
}

 /*** create servent **/
impl_POA_ServantBase
       *impl_CosNaming_NamingContext__create_servant (PortableServer_POA poa,
						      CORBA_Environment * ev)
{
  impl_POA_CosNaming_NamingContext *newservant;

  newservant =
    (impl_POA_CosNaming_NamingContext *) RtORB_calloc (1,
						       sizeof
						       (impl_POA_CosNaming_NamingContext),
						       "  create_servant");
  newservant->servant.vepv = &impl_CosNaming_NamingContext_vepv;
  newservant->poa = poa;
  POA_CosNaming_NamingContext__init ((PortableServer_Servant) newservant, ev);
  /* Before servant is going to be activated all
   * private attributes must be initialized.  */

  /* ------ init private attributes here ------ */
  /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase *) newservant;
}

static CORBA_boolean
impl_CosNaming_NamingContext__is_a (impl_POA_CosNaming_NamingContext *
				    servant, const CORBA_char * id,
				    CORBA_Environment * ev)
{
  CORBA_boolean retval;
  /* ------   insert method code here   ------ */

   if(strcmp(TC_CosNaming_NamingContext->repository_id, id) == 0){
      retval = TRUE;
   }else{
     if(strcmp(TC_CosNaming_NamingContextExt->repository_id, id) == 0){
       retval = TRUE;
     }else{
      retval = FALSE;
     }
   }

  /* ------ ---------- end ------------ ------ */
  return retval;
}

static void
impl_CosNaming_NamingContext_bind (impl_POA_CosNaming_NamingContext * servant,
				   CosNaming_Name * n,
				   CORBA_Object obj, CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */

   CosNaming_NameComponent *nc;
   CosNaming_Name *name = (CosNaming_Name *)n;
   PtrList **obj_list;

  SOCKET_LOCK();
   obj_list = NamingContext__resolve_ObjectList(servant,(CosNaming_Name *)n,ev);
   if(obj_list == NULL) return;
   nc = &name->_buffer[name->_length - 1];
   if( ContextList__find_item(*obj_list, nc) ){
      fprintf(stderr, "Already binded\n");
      CosNaming_AlreadyBound__set(ev);
      return;
   }
  
   *obj_list = PtrList_first(BindObject__append(*obj_list, OBJECT, nc,
			   CORBA_Object_dup(obj)));

  SOCKET_UNLOCK();
  /* ------ ---------- end ------------ ------ */
}


static void
impl_CosNaming_NamingContext_rebind (impl_POA_CosNaming_NamingContext *
				     servant, CosNaming_Name * n,
				     CORBA_Object obj, CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
   CosNaming_NameComponent *nc, *tmp;
   impl_POA_CosNaming_NamingContext *contxt;
   PtrList **obj_list=NULL;

   contxt = bind_new_context(servant, n, n->_length -1, ev);
   clearException(ev);

  SOCKET_LOCK();
   obj_list = NamingContext__resolve_ObjectList(servant,(CosNaming_Name *)n,ev);
   tmp = &n->_buffer[n->_length - 1];
  
   nc = CosNaming_NameComponent__alloc();
   nc->id = RtORB_strdup(tmp->id, "CosNamin:rebind");
   nc->kind = RtORB_strdup(tmp->kind, "CosNamin:rebind");

   void *itm  = ContextList__find_item(*obj_list, nc);

   if(itm == NULL){
     fprintf(stderr, "new bind %s/%s ",nc->id, nc->kind);
     *obj_list = PtrList_first(BindObject__append(*obj_list, OBJECT, nc,
			   CORBA_Object_dup(obj)));
     if(ContextList__find_item(*obj_list, nc) == NULL){
        fprintf(stderr, " Fail \n");
     }else{
        fprintf(stderr, " Success \n");
     }
   }else{
     *obj_list = PtrList_remove_item( ContextList__find_item(*obj_list, nc) );
     *obj_list = PtrList_first(BindObject__append(*obj_list, OBJECT, nc,
			   CORBA_Object_dup(obj)));
   }

  SOCKET_UNLOCK();
  /* ------ ---------- end ------------ ------ */
}


static void
impl_CosNaming_NamingContext_bind_context (impl_POA_CosNaming_NamingContext *
					   servant, CosNaming_Name * n,
					   CosNaming_NamingContext nc,
					   CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
   fprintf(stderr, "bind_context not implemented....\n");

  /* ------ ---------- end ------------ ------ */
}

static void
impl_CosNaming_NamingContext_rebind_context (impl_POA_CosNaming_NamingContext
					     * servant, CosNaming_Name * n,
					     CosNaming_NamingContext nc,
					     CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
   fprintf(stderr, "rebind_context not implemented....\n");
  /* ------ ---------- end ------------ ------ */
}

static CORBA_Object
impl_CosNaming_NamingContext_resolve (impl_POA_CosNaming_NamingContext *
				      servant, CosNaming_Name * n,
				      CORBA_Environment * ev)
{
  CORBA_Object retval;
  /* ------   insert method code here   ------ */
   BindObject *tmp;

  SOCKET_LOCK();
   tmp = NamingContext_resolve_BindObject(servant,
		   (CosNaming_Name *)n, n->_length,  ev);
  SOCKET_UNLOCK();

   if(!tmp){ return NULL; }

   retval = CORBA_Object_dup((CORBA_Object)tmp->object);

  /* ------ ---------- end ------------ ------ */
  return retval;
}

static void
impl_CosNaming_NamingContext_unbind (impl_POA_CosNaming_NamingContext *
				     servant, CosNaming_Name * n,
				     CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
   CosNaming_NameComponent *nc;
   CosNaming_Name *name = (CosNaming_Name *)n;
   PtrList **obj_list;
   PtrList *tmp_item;

  SOCKET_LOCK();
   obj_list = NamingContext__resolve_ObjectList(servant,(CosNaming_Name *)n,ev);
   nc = &name->_buffer[name->_length - 1];
  
   tmp_item = ContextList__find_item(*obj_list, nc);
  SOCKET_UNLOCK();

   if( tmp_item == NULL ){
      fprintf(stderr, "Unbound context.\n");
      CosNaming_NotFound__set(ev, 0, name, 0);
      return;
   }

  SOCKET_LOCK();
   *obj_list = PtrList_first(PtrList_remove_item( tmp_item ));
  SOCKET_UNLOCK();
  /* ------ ---------- end ------------ ------ */
}

static CosNaming_NamingContext
impl_CosNaming_NamingContext_new_context (impl_POA_CosNaming_NamingContext *
					  servant, CORBA_Environment * ev)
{
  CosNaming_NamingContext retval;
  /* ------   insert method code here   ------ */
  SOCKET_LOCK();
   retval = CORBA_Object_dup(
		   impl_CosNaming_NamingContext__create(servant->poa, ev)); 

  SOCKET_UNLOCK();
  /* ------ ---------- end ------------ ------ */
  return retval;
}

static CosNaming_NamingContext
impl_CosNaming_NamingContext_bind_new_context
  (impl_POA_CosNaming_NamingContext * servant, CosNaming_Name * n,
   CORBA_Environment * ev)
{
  CosNaming_NamingContext retval;
  /* ------   insert method code here   ------ */
   PtrList **obj_list;
   CosNaming_NameComponent *nc;


  SOCKET_LOCK();
   obj_list = NamingContext__resolve_ObjectList(servant,(CosNaming_Name *)n,ev);
  SOCKET_UNLOCK();

   if(ev->_major > 0){
     fprintf(stderr, "Error in bind_new_context\n");
     return NULL;
   }
   if(ContextList__resolve(*obj_list, &n->_buffer[n->_length -1])){
     fprintf(stderr, "Error in bind_new_context\n");
     CORBA_exception_set(ev, CORBA_USER_EXCEPTION, 
	     ex_CosNaming_NamingContext_AlreadyBound, NULL);
     return NULL;
   }

  SOCKET_LOCK();
   retval = CORBA_Object_dup(
		   impl_CosNaming_NamingContext__create(servant->poa, ev)); 

   nc = &n->_buffer[n->_length - 1];
   *obj_list = PtrList_first(BindObject__append(*obj_list, CONTEXT, nc, retval));

  SOCKET_UNLOCK();
  /* ------ ---------- end ------------ ------ */
  return retval;
}

static void
impl_CosNaming_NamingContext_destroy (impl_POA_CosNaming_NamingContext *
				      servant, CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
   fprintf(stderr, "destroy not implemented....\n");
  /* ------ ---------- end ------------ ------ */
}

static void
impl_CosNaming_NamingContext_list (impl_POA_CosNaming_NamingContext * servant,
				   CORBA_unsigned_long how_many,
				   CosNaming_BindingList ** bl,
				   CosNaming_BindingIterator * bi,
				   CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
  int i;
  SOCKET_LOCK();
  CosNaming_BindingList *cbl = servant->binding_list;

  int len = PtrList_length((PtrList *)servant->ObjectList);

  if(cbl == NULL || cbl->_length != len){
    if(cbl == NULL){
      cbl = CORBA_sequence_CosNaming_Binding__alloc();
      servant->binding_list = cbl;
    }else{
      delete_BindingList(cbl);
    }
    if(len > 0){
      cbl->_buffer = CORBA_sequence_CosNaming_Binding_allocbuf(len);
      cbl->_length = cbl->_maximum = len;
    }else{
      cbl->_buffer = NULL;
      cbl->_length = cbl->_maximum = 0;
    }

    for(i=0; i < len; i++){
      CosNaming_Binding *bi = &cbl->_buffer[i];
      BindObject *bo;
      bo = (BindObject *)PtrList_get_item((PtrList *)servant->ObjectList, (int32_t)i);
      if(bo != NULL){
        set_CosNaming_Name(&bi->binding_name, bo);
        if(bo->type == CONTEXT){
          bi->binding_type = CosNaming_ncontext;
        }else{
          bi->binding_type = CosNaming_nobject;
        }
      }else{
        fprintf(stderr, "**** ERROR in NamingContext_list\n");
      }
    }
  }

  *bl = cbl;

  //bi = impl_CosNaming_BindingIterator__create (servant->poa, ev);
  bi = NULL;
  SOCKET_UNLOCK();
  /* ------ ---------- end ------------ ------ */
}

     CORBA_CosNaming_BindingIterator
       impl_CosNaming_BindingIterator__create (PortableServer_POA poa,
					       CORBA_Environment * ev)
{
  CORBA_CosNaming_BindingIterator retval;
  impl_POA_CosNaming_BindingIterator *newservant;
  PortableServer_ObjectId objid;

  SOCKET_LOCK();
  newservant =
    (impl_POA_CosNaming_BindingIterator *) RtORB_calloc (1,
							 sizeof
							 (impl_POA_CosNaming_BindingIterator),
							 " create...");
  newservant->servant.vepv = &impl_CosNaming_BindingIterator_vepv;
  newservant->poa = poa;
  POA_CosNaming_BindingIterator__init ((PortableServer_Servant) newservant,
				       ev);
  /* Before servant is going to be activated all
   * private attributes must be initialized.  */

  /* ------ init private attributes here ------ */
  /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object (poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference (poa, newservant, ev);
  SOCKET_UNLOCK();

  return retval;
}

static void
impl_CosNaming_BindingIterator__destroy (impl_POA_CosNaming_BindingIterator *
					 servant, CORBA_Environment * ev)
{
  CORBA_Object_release ((CORBA_Object) servant->poa, ev);

  /* No further remote method calls are delegated to 
   * servant and you may free your private attributes. */
  /* ------ free private attributes here ------ */
  /* ------ ---------- end ------------- ------ */

  SOCKET_LOCK();
  POA_CosNaming_BindingIterator__fini ((PortableServer_Servant) servant, ev);

  RtORB_free (servant, "servant");
  SOCKET_UNLOCK();
}

 /*** create servent **/
impl_POA_ServantBase
       *impl_CosNaming_BindingIterator__create_servant (PortableServer_POA
							poa,
							CORBA_Environment *
							ev)
{
  impl_POA_CosNaming_BindingIterator *newservant;

  SOCKET_LOCK();
  newservant =
    (impl_POA_CosNaming_BindingIterator *) RtORB_calloc (1,
							 sizeof
							 (impl_POA_CosNaming_BindingIterator),
							 "  create_servant");
  newservant->servant.vepv = &impl_CosNaming_BindingIterator_vepv;
  newservant->poa = poa;
  POA_CosNaming_BindingIterator__init ((PortableServer_Servant) newservant,
				       ev);
  /* Before servant is going to be activated all
   * private attributes must be initialized.  */

  /* ------ init private attributes here ------ */
  /* ------ ---------- end ------------- ------ */
  SOCKET_UNLOCK();

  return (impl_POA_ServantBase *) newservant;
}

static CORBA_boolean
impl_CosNaming_BindingIterator_next_one (impl_POA_CosNaming_BindingIterator *
					 servant, CosNaming_Binding ** b,
					 CORBA_Environment * ev)
{
  CORBA_boolean retval;
  /* ------   insert method code here   ------ */
  fprintf(stderr, "next_one not implemented\n");
   retval = FALSE;

  /* ------ ---------- end ------------ ------ */
  return retval;
}

static CORBA_boolean
impl_CosNaming_BindingIterator_next_n (impl_POA_CosNaming_BindingIterator *
				       servant, CORBA_unsigned_long how_many,
				       CosNaming_BindingList ** bl,
				       CORBA_Environment * ev)
{
  CORBA_boolean retval;
  /* ------   insert method code here   ------ */

  fprintf(stderr, "next_n not implemented\n");
   retval = FALSE;
  /* ------ ---------- end ------------ ------ */
  return retval;
}

static void
impl_CosNaming_BindingIterator_destroy (impl_POA_CosNaming_BindingIterator *
					servant, CORBA_Environment * ev)
{
  /* ------   insert method code here   ------ */
  fprintf(stderr, "destory not implemented\n");
  /* ------ ---------- end ------------ ------ */
}


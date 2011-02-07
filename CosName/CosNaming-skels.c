/*
 * This file was generated by orbit-idl-2 - DO NOT EDIT!
 */

#include <string.h>
#define ORBIT2_STUBS_API
#include "CosNaming.h"

static void * get_skel_small_CosNaming_NamingContext(POA_CosNaming_NamingContext *servant,
const char *opname,void * *m_data, void * *impl) 
{
  switch(opname[0])
  {
    case '_':
      if(strcmp((opname + 1), "is_a")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->_is_a;
      *m_data = &CosNaming_NamingContext__imp.methods [0];
      return (void *)_RtORB_impl_CosNaming_NamingContext__is_a;
      break;
    case 'b':
      switch(opname[1])
      {
        case 'i':
          switch(opname[2])
          {
            case 'n':
              switch(opname[3])
              {
                case 'd':
                  switch(opname[4])
                  {
                    case '\0':
                      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->bind;
                      *m_data = &CosNaming_NamingContext__imp.methods [1];
                      return (void *)_RtORB_impl_CosNaming_NamingContext_bind;
                      break;
                    case '_':
                      switch(opname[5])
                      {
                        case 'c':
                          if(strcmp((opname + 6), "ontext")){ break; }
                          *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->bind_context;
                          *m_data = &CosNaming_NamingContext__imp.methods [3];
                          return (void *)_RtORB_impl_CosNaming_NamingContext_bind_context;
                          break;
                        case 'n':
                          if(strcmp((opname + 6), "ew_context")){ break; }
                          *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->bind_new_context;
                          *m_data = &CosNaming_NamingContext__imp.methods [8];
                          return (void *)_RtORB_impl_CosNaming_NamingContext_bind_new_context;
                          break;
                        default:
                          break;
                      }
                      break;
                    default:
                      break;
                  }
                  break;
                default:
                  break;
              }
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    case 'd':
      if(strcmp((opname + 1), "estroy")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->destroy;
      *m_data = &CosNaming_NamingContext__imp.methods [9];
      return (void *)_RtORB_impl_CosNaming_NamingContext_destroy;
      break;
    case 'l':
      if(strcmp((opname + 1), "ist")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->list;
      *m_data = &CosNaming_NamingContext__imp.methods [10];
      return (void *)_RtORB_impl_CosNaming_NamingContext_list;
      break;
    case 'n':
      if(strcmp((opname + 1), "ew_context")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->new_context;
      *m_data = &CosNaming_NamingContext__imp.methods [7];
      return (void *)_RtORB_impl_CosNaming_NamingContext_new_context;
      break;
    case 'r':
      switch(opname[1])
      {
        case 'e':
          switch(opname[2])
          {
            case 'b':
              switch(opname[3])
              {
                case 'i':
                  switch(opname[4])
                  {
                    case 'n':
                      switch(opname[5])
                      {
                        case 'd':
                          switch(opname[6])
                          {
                            case '\0':
                              *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->rebind;
                              *m_data = &CosNaming_NamingContext__imp.methods [2];
                              return (void *)_RtORB_impl_CosNaming_NamingContext_rebind;
                              break;
                            case '_':
                              if(strcmp((opname + 7), "context")){ break; }
                              *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->rebind_context;
                              *m_data = &CosNaming_NamingContext__imp.methods [4];
                              return (void *)_RtORB_impl_CosNaming_NamingContext_rebind_context;
                              break;
                            default:
                              break;
                          }
                          break;
                        default:
                          break;
                      }
                      break;
                    default:
                      break;
                  }
                  break;
                default:
                  break;
              }
              break;
            case 's':
              if(strcmp((opname + 3), "olve")){ break; }
              *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->resolve;
              *m_data = &CosNaming_NamingContext__imp.methods [5];
              return (void *)_RtORB_impl_CosNaming_NamingContext_resolve;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    case 'u':
      if(strcmp((opname + 1), "nbind")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->unbind;
      *m_data = &CosNaming_NamingContext__imp.methods [6];
      return (void *)_RtORB_impl_CosNaming_NamingContext_unbind;
      break;
    default:
      break;
  }
  return NULL;
}

void POA_CosNaming_NamingContext__init(PortableServer_Servant servant, CORBA_Environment *env)
{
  static PortableServer_ClassInfo class_info = {
    NULL,
    (void*(*)())&get_skel_small_CosNaming_NamingContext,
    "IDL:omg.org/CosNaming/NamingContext:1.0",
    &CosNaming_NamingContext__classid,
    &CosNaming_NamingContext__imp
  };
  PortableServer_ServantBase__init (((PortableServer_ServantBase *)servant), env);
  RtORB_POA_Object__create (&class_info,
  servant, NULL,
  NULL);
}

void POA_CosNaming_NamingContext__fini(PortableServer_Servant servant,
CORBA_Environment *env)
{
  PortableServer_ServantBase__fini(servant, env);
}

static void * get_skel_small_CosNaming_BindingIterator(POA_CosNaming_BindingIterator *servant,
const char *opname,void * *m_data, void * *impl) 
{
  switch(opname[0])
  {
    case 'd':
      if(strcmp((opname + 1), "estroy")){ break; }
      *impl = (void *)servant->vepv->CosNaming_BindingIterator_epv->destroy;
      *m_data = &CosNaming_BindingIterator__imp.methods [2];
      return (void *)_RtORB_impl_CosNaming_BindingIterator_destroy;
      break;
    case 'n':
      switch(opname[1])
      {
        case 'e':
          switch(opname[2])
          {
            case 'x':
              switch(opname[3])
              {
                case 't':
                  switch(opname[4])
                  {
                    case '_':
                      switch(opname[5])
                      {
                        case 'n':
                          if(strcmp((opname + 6), "")){ break; }
                          *impl = (void *)servant->vepv->CosNaming_BindingIterator_epv->next_n;
                          *m_data = &CosNaming_BindingIterator__imp.methods [1];
                          return (void *)_RtORB_impl_CosNaming_BindingIterator_next_n;
                          break;
                        case 'o':
                          if(strcmp((opname + 6), "ne")){ break; }
                          *impl = (void *)servant->vepv->CosNaming_BindingIterator_epv->next_one;
                          *m_data = &CosNaming_BindingIterator__imp.methods [0];
                          return (void *)_RtORB_impl_CosNaming_BindingIterator_next_one;
                          break;
                        default:
                          break;
                      }
                      break;
                    default:
                      break;
                  }
                  break;
                default:
                  break;
              }
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  return NULL;
}

void POA_CosNaming_BindingIterator__init(PortableServer_Servant servant, CORBA_Environment *env)
{
  static PortableServer_ClassInfo class_info = {
    NULL,
    (void*(*)())&get_skel_small_CosNaming_BindingIterator,
    "IDL:omg.org/CosNaming/BindingIterator:1.0",
    &CosNaming_BindingIterator__classid,
    &CosNaming_BindingIterator__imp
  };
  PortableServer_ServantBase__init (((PortableServer_ServantBase *)servant), env);
  RtORB_POA_Object__create (&class_info,
  servant, NULL,
  NULL);
}

void POA_CosNaming_BindingIterator__fini(PortableServer_Servant servant,
CORBA_Environment *env)
{
  PortableServer_ServantBase__fini(servant, env);
}

static void * get_skel_small_CosNaming_NamingContextExt(POA_CosNaming_NamingContextExt *servant,
const char *opname,void * *m_data, void * *impl) 
{
  switch(opname[0])
  {
    case '_':
      if(strcmp((opname + 1), "is_a")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->_is_a;
      *m_data = &CosNaming_NamingContext__imp.methods [0];
      return (void *)_RtORB_impl_CosNaming_NamingContext__is_a;
      break;
    case 'b':
      switch(opname[1])
      {
        case 'i':
          switch(opname[2])
          {
            case 'n':
              switch(opname[3])
              {
                case 'd':
                  switch(opname[4])
                  {
                    case '\0':
                      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->bind;
                      *m_data = &CosNaming_NamingContext__imp.methods [1];
                      return (void *)_RtORB_impl_CosNaming_NamingContext_bind;
                      break;
                    case '_':
                      switch(opname[5])
                      {
                        case 'c':
                          if(strcmp((opname + 6), "ontext")){ break; }
                          *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->bind_context;
                          *m_data = &CosNaming_NamingContext__imp.methods [3];
                          return (void *)_RtORB_impl_CosNaming_NamingContext_bind_context;
                          break;
                        case 'n':
                          if(strcmp((opname + 6), "ew_context")){ break; }
                          *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->bind_new_context;
                          *m_data = &CosNaming_NamingContext__imp.methods [8];
                          return (void *)_RtORB_impl_CosNaming_NamingContext_bind_new_context;
                          break;
                        default:
                          break;
                      }
                      break;
                    default:
                      break;
                  }
                  break;
                default:
                  break;
              }
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    case 'd':
      if(strcmp((opname + 1), "estroy")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->destroy;
      *m_data = &CosNaming_NamingContext__imp.methods [9];
      return (void *)_RtORB_impl_CosNaming_NamingContext_destroy;
      break;
    case 'l':
      if(strcmp((opname + 1), "ist")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->list;
      *m_data = &CosNaming_NamingContext__imp.methods [10];
      return (void *)_RtORB_impl_CosNaming_NamingContext_list;
      break;
    case 'n':
      if(strcmp((opname + 1), "ew_context")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->new_context;
      *m_data = &CosNaming_NamingContext__imp.methods [7];
      return (void *)_RtORB_impl_CosNaming_NamingContext_new_context;
      break;
    case 'r':
      switch(opname[1])
      {
        case 'e':
          switch(opname[2])
          {
            case 'b':
              switch(opname[3])
              {
                case 'i':
                  switch(opname[4])
                  {
                    case 'n':
                      switch(opname[5])
                      {
                        case 'd':
                          switch(opname[6])
                          {
                            case '\0':
                              *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->rebind;
                              *m_data = &CosNaming_NamingContext__imp.methods [2];
                              return (void *)_RtORB_impl_CosNaming_NamingContext_rebind;
                              break;
                            case '_':
                              if(strcmp((opname + 7), "context")){ break; }
                              *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->rebind_context;
                              *m_data = &CosNaming_NamingContext__imp.methods [4];
                              return (void *)_RtORB_impl_CosNaming_NamingContext_rebind_context;
                              break;
                            default:
                              break;
                          }
                          break;
                        default:
                          break;
                      }
                      break;
                    default:
                      break;
                  }
                  break;
                default:
                  break;
              }
              break;
            case 's':
              switch(opname[3])
              {
                case 'o':
                  switch(opname[4])
                  {
                    case 'l':
                      switch(opname[5])
                      {
                        case 'v':
                          switch(opname[6])
                          {
                            case 'e':
                              switch(opname[7])
                              {
                                case '\0':
                                  *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->resolve;
                                  *m_data = &CosNaming_NamingContext__imp.methods [5];
                                  return (void *)_RtORB_impl_CosNaming_NamingContext_resolve;
                                  break;
                                case '_':
                                  if(strcmp((opname + 8), "str")){ break; }
                                  *impl = (void *)servant->vepv->CosNaming_NamingContextExt_epv->resolve_str;
                                  *m_data = &CosNaming_NamingContextExt__imp.methods [3];
                                  return (void *)_RtORB_impl_CosNaming_NamingContextExt_resolve_str;
                                  break;
                                default:
                                  break;
                              }
                              break;
                            default:
                              break;
                          }
                          break;
                        default:
                          break;
                      }
                      break;
                    default:
                      break;
                  }
                  break;
                default:
                  break;
              }
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    case 't':
      switch(opname[1])
      {
        case 'o':
          switch(opname[2])
          {
            case '_':
              switch(opname[3])
              {
                case 'n':
                  if(strcmp((opname + 4), "ame")){ break; }
                  *impl = (void *)servant->vepv->CosNaming_NamingContextExt_epv->to_name;
                  *m_data = &CosNaming_NamingContextExt__imp.methods [1];
                  return (void *)_RtORB_impl_CosNaming_NamingContextExt_to_name;
                  break;
                case 's':
                  if(strcmp((opname + 4), "tring")){ break; }
                  *impl = (void *)servant->vepv->CosNaming_NamingContextExt_epv->to_string;
                  *m_data = &CosNaming_NamingContextExt__imp.methods [0];
                  return (void *)_RtORB_impl_CosNaming_NamingContextExt_to_string;
                  break;
                case 'u':
                  if(strcmp((opname + 4), "rl")){ break; }
                  *impl = (void *)servant->vepv->CosNaming_NamingContextExt_epv->to_url;
                  *m_data = &CosNaming_NamingContextExt__imp.methods [2];
                  return (void *)_RtORB_impl_CosNaming_NamingContextExt_to_url;
                  break;
                default:
                  break;
              }
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      break;
    case 'u':
      if(strcmp((opname + 1), "nbind")){ break; }
      *impl = (void *)servant->vepv->CosNaming_NamingContext_epv->unbind;
      *m_data = &CosNaming_NamingContext__imp.methods [6];
      return (void *)_RtORB_impl_CosNaming_NamingContext_unbind;
      break;
    default:
      break;
  }
  return NULL;
}

void POA_CosNaming_NamingContextExt__init(PortableServer_Servant servant, CORBA_Environment *env)
{
  static PortableServer_ClassInfo class_info = {
    NULL,
    (void*(*)())&get_skel_small_CosNaming_NamingContextExt,
    "IDL:omg.org/CosNaming/NamingContextExt:1.0",
    &CosNaming_NamingContextExt__classid,
    &CosNaming_NamingContextExt__imp
  };
  PortableServer_ServantBase__init (((PortableServer_ServantBase *)servant), env);
  POA_CosNaming_NamingContext__init(servant, env);
  RtORB_POA_Object__create (&class_info,
  servant, NULL,
  NULL);
}

void POA_CosNaming_NamingContextExt__fini(PortableServer_Servant servant,
CORBA_Environment *env)
{
  POA_CosNaming_NamingContext__fini(servant, env);
  PortableServer_ServantBase__fini(servant, env);
}


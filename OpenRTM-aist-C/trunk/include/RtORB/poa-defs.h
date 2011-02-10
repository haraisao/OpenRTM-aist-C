/*
 * Copyright (c) 2008, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */

/*

 Simple GIOP Implementation for x86 (Big Endian)
 
*/
/*!
 * @file poa-defs.h
 * @if jp
 * @brief POA定義
 * @else
 * @brief POA Definition
 * @endif
 * @author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef __POA_DEFS_H__
#define __POA_DEFS_H__

#if USE_THREAD
#include <pthread.h>
#endif
#include <RtORB/array.h>
#include <RtORB/list.h>
#include <RtORB/hashtable.h>
#include <RtORB/typecode.h>

#ifdef __cplusplus
extern "C"
{
#endif 
/*    POA   */
#define POA_HOLDING 	1  /*!< HOLDING Status of POA Manager    (request --> Hold to Queue) */
#define POA_ACTIVE  	2  /*!< ACTIVE Status of POA Manager     (request --> Accept) */
#define POA_DISCARDING 	3  /*!< DISCARDING Status of POA Manager (request --> Destroy) */
#define POA_INACTIVE  	4  /*!< INACTIVE Status of POA Manager   (request --> Deny) */

/* POA   */
/*!
 * @struct PortableServer_POA_struct
 * @brief PortableServer_POA_struct structure
 * @param orb ORB
 * @param id ORB内での一のID(RootPOAなど)
 * @param _server POAサービスのためのGIOPポート
 * @param mgr_factory POA Manager Factory
 * @param manager POA Manager
 * @param children (TODO)
 * @param servant_mgr (TODO)
 * @param object_map POA内のオブジェクトアダプタ登録用table. 初期値64で生成.
 * @param requests Request Queue from client to Servant
 */
typedef struct PortableServer_POA_struct{
  char *id;
  struct GIOP_Connection *_server;
  hashtable *object_map;
  PtrList *requests;
  uint32_t status;

}PortableServer_POA_struct;

typedef PortableServer_POA_struct * PortableServer_POA;
typedef PortableServer_POA_struct * PortableServer_POAManager;

/* ObjectId   */
typedef char * PortableServer_ObjectId;

/*   Servant   */
typedef void *PortableServer_Servant;

/*!
 * @struct PortableServer_ServantBase__epv
 * @brief PortableServer_ServantBase__epv structure
 * @param finalize (TODO)
 * @param default_POA (TODO)
 * @param add_ref (TODO)
 * @param remove_ref (TODO)
 * @param get_interface (TODO)
 * @param is_a (TODO)
 * @param non_existent (TODO)
 */
typedef struct {
  void *_private;

  void (*finalize)(PortableServer_Servant , CORBA_Environment *);
  PortableServer_POA (*default_POA)(PortableServer_Servant, CORBA_Environment *);
  void (*add_ref)(PortableServer_Servant, CORBA_Environment *);
  void (*remove_ref)(PortableServer_Servant, CORBA_Environment *);
  CORBA_boolean (*is_a)(PortableServer_Servant, const char *, CORBA_Environment *);
  CORBA_boolean (*non_existent)(PortableServer_Servant, CORBA_Environment *);
} PortableServer_ServantBase__epv ;

typedef PortableServer_ServantBase__epv *PortableServer_ServantBase__vepv;

/*!
 * @struct PortableServer_ServantBase
 * @brief PortableServer_ServantBase structure
 * @param _private (TODO)
 * @param vepv (TODO)
 */
typedef struct {
  void *_private;
  PortableServer_ServantBase__vepv *vepv;
} PortableServer_ServantBase;

/*!
 * @struct impl_POA_ServantBase
 * @brief impl_POA_ServantBase structure
 * @param servant (TODO)
 * @param poa (TODO)
 * @param _private (TODO)
 */
typedef struct{
  PortableServer_ServantBase servant;
  PortableServer_POA poa;
  void *_private;
}impl_POA_ServantBase;

/*!
 * @struct PortableServer_ClassInfo
 * @brief PortableServer_ClassInfo structure
 * @param dummy (TODO)
 * @param impl_finder (TODO)
 * @param class_name (TODO)
 * @param class_id (TODO)
 * @param class_impl (TODO)
 */
typedef struct {
  void (*dummy)();
  void *(*impl_finder)();
  const char *class_name;
  uint32_t *class_id;
  CORBA_Class_Impl *class_impl;
}PortableServer_ClassInfo;

/*   RtORB POA Object  */
/*!
 * @struct RtORB_POA_Object
 * @brief RtORB_POA_Object structure
 * @param _private (TODO)
 * @param obj (TODO)
 * @param poa (TODO)
 * @param servant (TODO)
 * @param objectId (TODO)
 * @param _reserve (TODO)
 */
typedef struct{
  struct {
    void *_private;
    void *_vepv;
  } impl_serv;

  PortableServer_POA poa;

  PortableServer_Servant servant;

  CORBA_Object obj;

  void *_reserve;

}RtORB_POA_Object;

/*!
 * @brief return POA releated Object (Unused)(T.B.D)
 */
PortableServer_POA PortableServer_POA__narrow(CORBA_Object);

#ifdef __cplusplus
}
#endif 
#endif


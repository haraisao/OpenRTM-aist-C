/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_SDOPackage_Monitoring.c
 * \brief (未使用) 
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : SDOPackage                             ***/
/***      Interface   : Monitoring      [empty]              ***/
/***************************************************************/

CORBA_SDOPackage_Monitoring 
impl_SDOPackage_Monitoring__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_SDOPackage_Monitoring retval;
  impl_POA_SDOPackage_Monitoring *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_SDOPackage_Monitoring *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_Monitoring)," create...");
  newservant->servant.vepv = &impl_SDOPackage_Monitoring_vepv;
  newservant->poa = poa;
  POA_SDOPackage_Monitoring__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_SDOPackage_Monitoring__destroy(impl_POA_SDOPackage_Monitoring *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_SDOPackage_Monitoring__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_SDOPackage_Monitoring__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_SDOPackage_Monitoring *newservant;

  newservant = (impl_POA_SDOPackage_Monitoring *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_Monitoring), "  create_servant");
  newservant->servant.vepv = &impl_SDOPackage_Monitoring_vepv;
  newservant->poa = poa;
  POA_SDOPackage_Monitoring__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}


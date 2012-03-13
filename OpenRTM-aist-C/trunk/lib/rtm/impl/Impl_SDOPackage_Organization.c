/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_SDOPackage_Organization.c
 * \brief (未使用) 
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : SDOPackage                             ***/
/***      Interface   : Organization                         ***/
/***************************************************************/

CORBA_SDOPackage_Organization 
impl_SDOPackage_Organization__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_SDOPackage_Organization retval;
  impl_POA_SDOPackage_Organization *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_SDOPackage_Organization *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_Organization)," create...");
  newservant->servant.vepv = &impl_SDOPackage_Organization_vepv;
  newservant->poa = poa;
  POA_SDOPackage_Organization__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_SDOPackage_Organization__destroy(impl_POA_SDOPackage_Organization *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_SDOPackage_Organization__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_SDOPackage_Organization__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_SDOPackage_Organization *newservant;

  newservant = (impl_POA_SDOPackage_Organization *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_Organization), "  create_servant");
  newservant->servant.vepv = &impl_SDOPackage_Organization_vepv;
  newservant->poa = poa;
  POA_SDOPackage_Organization__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

SDOPackage_UniqueIdentifier
impl_SDOPackage_Organization_get_organization_id(
  impl_POA_SDOPackage_Organization *servant,
  CORBA_Environment *ev)
{
  SDOPackage_UniqueIdentifier retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_OrganizationProperty*
impl_SDOPackage_Organization_get_organization_property(
  impl_POA_SDOPackage_Organization *servant,
  CORBA_Environment *ev)
{
  SDOPackage_OrganizationProperty* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_any*
impl_SDOPackage_Organization_get_organization_property_value(
  impl_POA_SDOPackage_Organization *servant,
  const CORBA_char * name,
  CORBA_Environment *ev)
{
  CORBA_any* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_add_organization_property(
  impl_POA_SDOPackage_Organization *servant,
  SDOPackage_OrganizationProperty* organization_property,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_set_organization_property_value(
  impl_POA_SDOPackage_Organization *servant,
  const CORBA_char * name,
  CORBA_any* value,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_remove_organization_property(
  impl_POA_SDOPackage_Organization *servant,
  const CORBA_char * name,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_SDOSystemElement
impl_SDOPackage_Organization_get_owner(
  impl_POA_SDOPackage_Organization *servant,
  CORBA_Environment *ev)
{
  SDOPackage_SDOSystemElement retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_set_owner(
  impl_POA_SDOPackage_Organization *servant,
  SDOPackage_SDOSystemElement sdo,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_SDOList*
impl_SDOPackage_Organization_get_members(
  impl_POA_SDOPackage_Organization *servant,
  CORBA_Environment *ev)
{
  SDOPackage_SDOList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_set_members(
  impl_POA_SDOPackage_Organization *servant,
  SDOPackage_SDOList* sdos,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_add_members(
  impl_POA_SDOPackage_Organization *servant,
  SDOPackage_SDOList* sdo_list,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_remove_member(
  impl_POA_SDOPackage_Organization *servant,
  const CORBA_char * id,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_DependencyType
impl_SDOPackage_Organization_get_dependency(
  impl_POA_SDOPackage_Organization *servant,
  CORBA_Environment *ev)
{
  SDOPackage_DependencyType retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Organization_set_dependency(
  impl_POA_SDOPackage_Organization *servant,
  SDOPackage_DependencyType dependency,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}



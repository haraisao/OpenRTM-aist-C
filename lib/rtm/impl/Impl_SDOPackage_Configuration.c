/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_SDOPackage_Configuration.c
 * \brief (未使用) 
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : SDOPackage                             ***/
/***      Interface   : Configuration                        ***/
/***************************************************************/

CORBA_SDOPackage_Configuration 
impl_SDOPackage_Configuration__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_SDOPackage_Configuration retval;
  impl_POA_SDOPackage_Configuration *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_SDOPackage_Configuration *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_Configuration)," create...");
  newservant->servant.vepv = &impl_SDOPackage_Configuration_vepv;
  newservant->poa = poa;
  POA_SDOPackage_Configuration__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_SDOPackage_Configuration__destroy(impl_POA_SDOPackage_Configuration *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_SDOPackage_Configuration__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_SDOPackage_Configuration__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_SDOPackage_Configuration *newservant;

  newservant = (impl_POA_SDOPackage_Configuration *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_Configuration), "  create_servant");
  newservant->servant.vepv = &impl_SDOPackage_Configuration_vepv;
  newservant->poa = poa;
  POA_SDOPackage_Configuration__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

CORBA_boolean
impl_SDOPackage_Configuration_set_device_profile(
  impl_POA_SDOPackage_Configuration *servant,
  SDOPackage_DeviceProfile* dProfile,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_add_service_profile(
  impl_POA_SDOPackage_Configuration *servant,
  SDOPackage_ServiceProfile* sProfile,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_add_organization(
  impl_POA_SDOPackage_Configuration *servant,
  SDOPackage_Organization organization_object,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_remove_service_profile(
  impl_POA_SDOPackage_Configuration *servant,
  const CORBA_char * id,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_remove_organization(
  impl_POA_SDOPackage_Configuration *servant,
  const CORBA_char * organization_id,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ParameterList*
impl_SDOPackage_Configuration_get_configuration_parameters(
  impl_POA_SDOPackage_Configuration *servant,
  CORBA_Environment *ev)
{
  SDOPackage_ParameterList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_NVList*
impl_SDOPackage_Configuration_get_configuration_parameter_values(
  impl_POA_SDOPackage_Configuration *servant,
  CORBA_Environment *ev)
{
  SDOPackage_NVList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_any*
impl_SDOPackage_Configuration_get_configuration_parameter_value(
  impl_POA_SDOPackage_Configuration *servant,
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
impl_SDOPackage_Configuration_set_configuration_parameter(
  impl_POA_SDOPackage_Configuration *servant,
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

SDOPackage_ConfigurationSet*
impl_SDOPackage_Configuration_get_configuration_set(
  impl_POA_SDOPackage_Configuration *servant,
  const CORBA_char * config_id,
  CORBA_Environment *ev)
{
  SDOPackage_ConfigurationSet* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_set_configuration_set_values(
  impl_POA_SDOPackage_Configuration *servant,
  SDOPackage_ConfigurationSet* configuration_set,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_add_configuration_set(
  impl_POA_SDOPackage_Configuration *servant,
  SDOPackage_ConfigurationSet* configuration_set,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_remove_configuration_set(
  impl_POA_SDOPackage_Configuration *servant,
  const CORBA_char * config_id,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ConfigurationSetList*
impl_SDOPackage_Configuration_get_configuration_sets(
  impl_POA_SDOPackage_Configuration *servant,
  CORBA_Environment *ev)
{
  SDOPackage_ConfigurationSetList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ConfigurationSet*
impl_SDOPackage_Configuration_get_active_configuration_set(
  impl_POA_SDOPackage_Configuration *servant,
  CORBA_Environment *ev)
{
  SDOPackage_ConfigurationSet* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_boolean
impl_SDOPackage_Configuration_activate_configuration_set(
  impl_POA_SDOPackage_Configuration *servant,
  const CORBA_char * config_id,
  CORBA_Environment *ev)
{
  CORBA_boolean retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}



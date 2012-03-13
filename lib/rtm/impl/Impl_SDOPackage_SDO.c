/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_SDOPackage_SDO.c
 * \brief [RtSystemEditor]対応、get_configuration()のみ実装
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : SDOPackage                             ***/
/***      Interface   : SDO                                  ***/
/***        Inheritance   : SDOSystemElement                 ***/
/***************************************************************/

CORBA_SDOPackage_SDO 
impl_SDOPackage_SDO__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_SDOPackage_SDO retval;
  impl_POA_SDOPackage_SDO *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_SDOPackage_SDO *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_SDO)," create...");
  newservant->servant.vepv = &impl_SDOPackage_SDO_vepv;
  newservant->poa = poa;
  POA_SDOPackage_SDO__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_SDOPackage_SDO__destroy(impl_POA_SDOPackage_SDO *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_SDOPackage_SDO__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_SDOPackage_SDO__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_SDOPackage_SDO *newservant;

  newservant = (impl_POA_SDOPackage_SDO *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_SDO), "  create_servant");
  newservant->servant.vepv = &impl_SDOPackage_SDO_vepv;
  newservant->poa = poa;
  POA_SDOPackage_SDO__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

SDOPackage_UniqueIdentifier
impl_SDOPackage_SDO_get_sdo_id(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_UniqueIdentifier retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_string
impl_SDOPackage_SDO_get_sdo_type(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  CORBA_string retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_DeviceProfile*
impl_SDOPackage_SDO_get_device_profile(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_DeviceProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ServiceProfileList*
impl_SDOPackage_SDO_get_service_profiles(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_ServiceProfileList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_ServiceProfile*
impl_SDOPackage_SDO_get_service_profile(
  impl_POA_SDOPackage_SDO *servant,
  const CORBA_char * id,
  CORBA_Environment *ev)
{
  SDOPackage_ServiceProfile* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_SDOService
impl_SDOPackage_SDO_get_sdo_service(
  impl_POA_SDOPackage_SDO *servant,
  const CORBA_char * id,
  CORBA_Environment *ev)
{
  SDOPackage_SDOService retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_Monitoring
impl_SDOPackage_SDO_get_monitoring(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_Monitoring retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_OrganizationList*
impl_SDOPackage_SDO_get_organizations(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_OrganizationList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

SDOPackage_NVList*
impl_SDOPackage_SDO_get_status_list(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_NVList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

CORBA_any*
impl_SDOPackage_SDO_get_status(
  impl_POA_SDOPackage_SDO *servant,
  const CORBA_char * nme,
  CORBA_Environment *ev)
{
  CORBA_any* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
    /* ------ ---------- end ------------ ------ */

  return retval;
}

/*!
 * \brief 当関数は、[RtSystemEditor]を使用する場合に、その内部処理の際にcallされる。<BR>
 *        ダミー値(NULL)を返すのみとする。
 * \return SDOPackage_Configuration型データ
 */
SDOPackage_Configuration
impl_SDOPackage_SDO_get_configuration(
  impl_POA_SDOPackage_SDO *servant,
  CORBA_Environment *ev)
{
  SDOPackage_Configuration retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */
  retval = NULL;
    /* ------ ---------- end ------------ ------ */

  return retval;
}



/**********************************************************************************/
/* Caution : Comment out unused functions by "#if 0". 
 * Ref : [OpenRTM-aist.h :: #define SDOPackage_SDO_get_owned_organizations SDOPackage_SDOSystemElement_get_owned_organizations ]  
 */
/**********************************************************************************/


#if 0

SDOPackage_OrganizationList*
impl_SDOPackage_SDO_get_owned_organizations(
    impl_POA_SDOPackage_SDO *servant,
    CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
  SDOPackage_OrganizationList* retval;
    /* ------   insert method code here  (6) ------ */
  retval=NULL;
  fprintf(stderr, " impl_SDOPackage_SDO_get_owned_organizations( \n");
    /* ------ ---------- end ------------ ------ */

  return retval;
}

#endif



/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_SDOPackage_SDOSystemElement.c
 * \brief [RtSystemEditor]対応、get_owned_organizations()のみ実装
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : SDOPackage                             ***/
/***      Interface   : SDOSystemElement                     ***/
/***************************************************************/

CORBA_SDOPackage_SDOSystemElement 
impl_SDOPackage_SDOSystemElement__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_SDOPackage_SDOSystemElement retval;
  impl_POA_SDOPackage_SDOSystemElement *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_SDOPackage_SDOSystemElement *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_SDOSystemElement)," create...");
  newservant->servant.vepv = &impl_SDOPackage_SDOSystemElement_vepv;
  newservant->poa = poa;
  POA_SDOPackage_SDOSystemElement__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_SDOPackage_SDOSystemElement__destroy(impl_POA_SDOPackage_SDOSystemElement *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_SDOPackage_SDOSystemElement__fini((PortableServer_Servant)servant, ev);

    RtORB_free (servant, "servant");
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_SDOPackage_SDOSystemElement__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_SDOPackage_SDOSystemElement *newservant;

  newservant = (impl_POA_SDOPackage_SDOSystemElement *)RtORB_calloc(1, sizeof(impl_POA_SDOPackage_SDOSystemElement), "  create_servant");
  newservant->servant.vepv = &impl_SDOPackage_SDOSystemElement_vepv;
  newservant->poa = poa;
  POA_SDOPackage_SDOSystemElement__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */

   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief 当関数は、[RtSystemEditor]を使用する場合に、その内部処理の際にcallされる。<BR>
 *        ダミー値(NULL)を返すのみとする。
 * \return SDOPackage_Configuration型データ
 */
SDOPackage_OrganizationList*
impl_SDOPackage_SDOSystemElement_get_owned_organizations(
  impl_POA_SDOPackage_SDOSystemElement *servant,
  CORBA_Environment *ev)
{
  SDOPackage_OrganizationList* retval;
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  retval=SDOPackage_OrganizationList__alloc();
  retval->_maximum=0;
  retval->_length=0;
  retval->_release=0;
  retval->_buffer=NULL;
  
    /* ------ ---------- end ------------ ------ */

  return retval;
}

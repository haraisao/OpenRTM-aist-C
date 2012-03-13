/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file Impl_OpenRTM_InPortCdr.c
 * \brief <OpenRTM::InPortCdrインタフェース> DataPort接続時に生成されるInPortCdr型Interfaceに関する実装。主に、[put()]関数でのOutPort側からのデータの取得処理がメインとなる。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */
/***************************************************************/
/*** Stub implementations (from OpenRTM-aist-skelimpl.c)     ***/
/***    Module      : OpenRTM                                ***/
/***      Interface   : InPortCdr                            ***/
/***************************************************************/

CORBA_OpenRTM_InPortCdr 
impl_OpenRTM_InPortCdr__create(PortableServer_POA poa, CORBA_Environment *ev)
{
  CORBA_OpenRTM_InPortCdr retval;
  impl_POA_OpenRTM_InPortCdr *newservant;
  PortableServer_ObjectId objid;

  newservant = (impl_POA_OpenRTM_InPortCdr *)RtORB_calloc(1, sizeof(impl_POA_OpenRTM_InPortCdr)," create...");
  newservant->servant.vepv = &impl_OpenRTM_InPortCdr_vepv;
  newservant->poa = poa;
  POA_OpenRTM_InPortCdr__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributes must be initialized.  */

   /* ------ init private attributes here ------ */

  newservant->m_inport = NULL;
  newservant->m_isNew = -1;  
  newservant->m_buffer = NULL; 

   /* ------ ---------- end ------------- ------ */

  objid = PortableServer_POA_activate_object(poa, newservant, ev);
  retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

  return retval;
}

void
impl_OpenRTM_InPortCdr__destroy(impl_POA_OpenRTM_InPortCdr *servant, CORBA_Environment *ev)
{
    CORBA_Object_release ((CORBA_Object) servant->poa, ev);

    /* No further remote method calls are delegated to 
    * servant and you may free your private attributes. */
   /* ------ free private attributes here ------ */
   /* ------ ---------- end ------------- ------ */

    POA_OpenRTM_InPortCdr__fini((PortableServer_Servant)servant, ev);
#if 0 /* メモリ2重解放回避のため (POA_OpenRTM_InPortCdr__fini()関数ないでもfreeしているため) */
    RtORB_free (servant, "servant");
# endif
}



 /*** create servent **/ 
impl_POA_ServantBase * 
impl_OpenRTM_InPortCdr__create_servant(PortableServer_POA poa, CORBA_Environment *ev)
{
  impl_POA_OpenRTM_InPortCdr *newservant;

  newservant = (impl_POA_OpenRTM_InPortCdr *)RtORB_calloc(1, sizeof(impl_POA_OpenRTM_InPortCdr), "  create_servant");
  newservant->servant.vepv = &impl_OpenRTM_InPortCdr_vepv;
  newservant->poa = poa;
  POA_OpenRTM_InPortCdr__init((PortableServer_Servant)newservant, ev);
   /* Before servant is going to be activated all
    * private attributs must be initialized.  */
   /* ------ init private attributes here ------ */
   /* ------ ---------- end ------------- ------ */


  return (impl_POA_ServantBase*)newservant;
}

/*!
 * \brief OutPort側のRTCにて、write()関数により、当関数がcallされ、データを取得(受信)する。
 *
 *        (1) 引数にあるマーシャリング済みデータを取得し、そのサイズ(length)の分だけ、バッファ領域をメモリ確保し、そこに受信データをコピーする。<BR>
 *        (2) 新規データフラグを"1"に変更する。
 * \param data Cdr型データ(octet型の可変長サイズ)であり、OutPort側からの送信データがここにマーシャリングされた状態で入ってくる。
 * \return OpenRTM_PortStatus型のStatus値(PORT_OK/PORT_ERROR/....)
 */
OpenRTM_PortStatus
impl_OpenRTM_InPortCdr_put(
  impl_POA_OpenRTM_InPortCdr *servant,
  OpenRTM_CdrData* data,
  CORBA_Environment *ev)
{
  memset(ev, 0, sizeof(CORBA_Environment));
    /* ------   insert method code here (2)  ------ */

  /* set CdrData to InPort buffer */ 
  if (servant->m_buffer == NULL) {  /* Action (only first called) */
    servant->m_buffer = CORBA_sequence_CORBA_octet__alloc();
    if (servant->m_buffer == NULL) {
      fprintf(stderr, " [ERROR] <InPort_read> Can't allocate memory.\n");
      return OpenRTM_PORT_ERROR;
    }
  }

  /* set param */
  servant->m_buffer->_length = data->_length;
  servant->m_buffer->_maximum = data->_maximum;
  servant->m_buffer->_release = data->_release;

  /* [_buffer] part */
  if(servant->m_buffer->_buffer != NULL)  free(servant->m_buffer->_buffer);
  servant->m_buffer->_buffer = CORBA_sequence_CORBA_octet_allocbuf(data->_length);
  if (servant->m_buffer->_buffer == NULL) {
    fprintf(stderr, " [ERROR] <InPort_read> Can't allocate buffer memory.\n");
      return OpenRTM_PORT_ERROR;
  } else {
    /* copy CdrData and change Flag */
    memcpy(servant->m_buffer->_buffer, data->_buffer, data->_length);
    servant->m_isNew = 1; /* [isNew](1:unread, 0:read) */
  }

    /* ------ ---------- end ------------ ------ */

  return OpenRTM_PORT_OK;
}


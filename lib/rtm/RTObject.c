/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file RTObject.c
 * \brief RTCの基底となるRTObjectに関する関数群のファイル。主に、RTObjectの生成、コンフィグレーション情報の取得、DataPortを使用した操作などの目的で使用される。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#include <rtm/OpenRTM.h>
#include <rtm/OpenRTM-aist-skelimpl.h>

/*
 Called from [<USER_RTCOMP> create()].
*/
CORBA_RTC_RTObject
RTC_DataFlowComponentBase_create(RTC_Manager *manager)
{
  CORBA_RTC_RTObject res;
  CORBA_Environment ev;

  res = impl_RTC_RTObject__create(manager->m_pPOA, &ev);

  return res;
}


/*
 Called from [<USER_RTCOMP> onInitialzie()].
*/
RTC_OutPort*
RTC_OutPort_create(CORBA_RTC_RTObject rtobj, const char *port_name, const char *type_name)
{
  return (RTC_OutPort*)Port_createPort(rtobj, port_name, type_name, OUTPORT_TYPE);
}


/*
 Called from [<USER_RTCOMP> onInitialzie()].
*/
RTC_InPort*
RTC_InPort_create(CORBA_RTC_RTObject rtobj, const char *port_name, const char *type_name)
{
  return (RTC_InPort*)Port_createPort(rtobj, port_name, type_name, INPORT_TYPE);
}


/*
 Called from [<USER_RTCOMP> onInitialzie(), etc].
*/
int RTC_OutPort_setSeqLength(RTC_OutPort *out_port, CORBA_unsigned_long length, void* val, const char* val_name)
{

  if (length < 0) {
    fprintf(stderr, " [ERROR]Invalid Sequence Length. length=%d.\n", length);
    return -1;
  } else {
    if (Port_setSequenceLength(out_port, length, val, val_name) < 0)  return -1;
    return 1; 
  }
}


/*
 Called from [<USER_RTCOMP> onInitialzie(), etc].
*/
uint32_t RTC_OutPort_getSeqLength(RTC_OutPort *out_port, void* val, const char* val_name)
{

  return Port_getSequenceLength(out_port, val, val_name); 
}


/*
 Called from [<USER_RTCOMP> onInitialzie(), etc].
*/
uint32_t RTC_InPort_getSeqLength(RTC_InPort *in_port, void* val, const char* val_name)
{

  return Port_getSequenceLength(in_port, val, val_name); 
}


/*
 Called from [<USER_RTCOMP> onExecute(), etc].
*/
int RTC_InPort_isNew(RTC_InPort* in_port)
{
  /* Check whether received data is exist or not, and change Flag. */
  impl_POA_RTC_PortService *in_ps_servant;
  impl_POA_OpenRTM_InPortCdr *inportcdr_servant;

  /* Check whether InPortCdr(Port_Connection) is exist or not. */
  in_ps_servant = (impl_POA_RTC_PortService*)in_port->m_objref->servant;
  if (in_ps_servant->m_InPortCdr == NULL)
  {
#if 0
      fprintf(stderr," [RTC_InPort_isNew()] No OutPort_Connections.\n");
#endif
    return -1;
  } 
  inportcdr_servant = (impl_POA_OpenRTM_InPortCdr*)in_ps_servant->m_InPortCdr->servant;

  if(inportcdr_servant->m_isNew == 1)
  { 
     inportcdr_servant->m_isNew = 0;
     return 1; /* Radable data found. */
  } else {
     return -1; /* Not found readable data. */ 
  } 
}


/*
 Called from [<USER_RTCOMP> onExecute(), etc].
*/
int RTC_InPort_read(RTC_InPort* in_port)
{

  int flag = 1; /* Succeed to read data. */

  /* Check whether received data is exist or not, and change Flag. */
  impl_POA_RTC_PortService *in_ps_servant;
  impl_POA_OpenRTM_InPortCdr *inportcdr_servant;

  /* Check whether InPortCdr(Port_Connection) is exist or not. */
  in_ps_servant = (impl_POA_RTC_PortService*)in_port->m_objref->servant;
  if (in_ps_servant->m_InPortCdr == NULL)
  {
#if 0
    fprintf(stderr," [RTC_InPort_read()] No OutPort_Connections.\n");
#endif
    flag = -1;

  } else { 
    inportcdr_servant = (impl_POA_OpenRTM_InPortCdr*)in_ps_servant->m_InPortCdr->servant;

    /* Unmarshal CdrData, and set DataType's data to InPort_buffer.  */
    Port_UnMarshal_by_TypeCode(inportcdr_servant->m_buffer, inportcdr_servant->m_inport);

    /* Free memory of InPort buffer */
    free(inportcdr_servant->m_buffer->_buffer); 
    inportcdr_servant->m_buffer->_buffer = NULL;
    free(inportcdr_servant->m_buffer); 
    inportcdr_servant->m_buffer = NULL;
  }

  return flag;
}


/*
 Called from [<USER_RTCOMP> onExecute(), etc].
*/
int RTC_OutPort_write(RTC_OutPort* out_port)
{
  OpenRTM_PortStatus status;
  OpenRTM_CdrData cdrData;  /* marshalled CdrData(sequence_octet) */
  CORBA_Environment ev;

  /* Check whether Provider's InPortCdr_Servant(Port_Connection) is exist or not. */
  impl_POA_RTC_PortService *out_ps_servant;
  out_ps_servant = (impl_POA_RTC_PortService*)out_port->m_objref->servant;

  if (out_ps_servant->m_InPortCdr == NULL)
  {
#if 0
    fprintf(stderr," [RTC_OutPort_write()] No InPort_Connections.\n");
#endif
    return 0;
  } 
 
  /* Marshal value to CdrStreamData by DataType. */
  cdrData._buffer = NULL;
  if (Port_Marshal_by_TypeCode(&cdrData, out_port) < 0) return -1;

  /* send Data (call Provider's put() method.) */
  memset (&ev, 0, sizeof (CORBA_Environment));  /* initialize */
  status = OpenRTM_InPortCdr_put(out_ps_servant->m_InPortCdr, &cdrData, &ev);

  /* free buffer */
  if (cdrData._buffer) {
    RtORB_free(cdrData._buffer, "RTC_OutPort_write() free(cdrData._buffer)");
    cdrData._buffer = NULL;
  }

  if (status == OpenRTM_PORT_OK) return 1; //Succeed to write data.
  else                           return -1; //Fail to write data

}


/*
 Called from [RTC_Manager_configureComponent()].
*/
RTC_Properties *
RTC_RTObject_getProperties(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return implobj->m_properties;
}


/*
 Called from [RTC_Manager_configureComponent()].
*/
char *
RTC_RTObject_getCategory(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, "category");
}


/*
 Called from [RTC_Manager_configureComponent()].
*/
char *
RTC_RTObject_getTypeName(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, "type_name");
}


/*
 Called from [RTC_Manager_configureComponent()].
*/
char *
RTC_RTObject_getInstanceName(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, "instance_name");
}


/*
 Called from [RTC_Manager_createComponent()].
*/
int
RTC_RTObject_setInstanceName(CORBA_RTC_RTObject obj, char *name)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  implobj->m_properties = Properties_setProperty(implobj->m_properties, "instance_name", name);
  return 1;
}


/*
 Called from [RTC_Manager_configureComponent()].
*/
int
RTC_RTObject_setProperty(CORBA_RTC_RTObject obj, char *name, char *value)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  Properties_setProperty(implobj->m_properties, name, value);
  return 1;
}


/*
 Called from [RTC_Manager_configureComponent()].
*/
char *
RTC_RTObject_getProperty(CORBA_RTC_RTObject obj, char *name)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, name);
}


/*
 Uncalled.
*/
int
RTC_RTObject_registerProperty(CORBA_RTC_RTObject obj, RTC_Properties *prop)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  implobj->m_properties = prop;
  return 1;
}


/*
 Called from [RTC_Manager_createComponent(), RTC_Manager_configureComponent()].
*/
RTC_Properties *
RTC_RTObject_appendProperties(CORBA_RTC_RTObject obj, RTC_Properties *prop)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  if(prop != NULL){
    implobj->m_properties = Properties_appendProperties(implobj->m_properties, prop);
  }
  return implobj->m_properties;
}


/*
 Called from [RTC_Manager_registerComponent()].
*/
char **
RTC_RTObject_getNamingNames(CORBA_RTC_RTObject obj, int *len)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;

  char *names = Properties_getProperty(implobj->m_properties, "naming.names");
  string_sequence *tmp = split_string(names, ',', 0);
  *len = tmp->length;
  char **res = tmp->buffer;

  free(tmp);

  return res;
}


/*
 Called from [impl_RTC_LightweightRTObject_get_owned_contexts()].
*/
int
RTObject_get_owned_contexts(impl_POA_RTC_RTObject *servant, RTC_ExecutionContextList *ec)
{
  int res = -1;

  if(ec == NULL){
   fprintf(stderr, "Invalid ExecutionContextList\n");
  }else{
    ec->_maximum = ec->_length = 1;
    ec->_release = 0;
    ec->_buffer = RTC_ExecutionContextList_allocbuf(1);
    ec->_buffer[0] = CORBA_Object_dup((CORBA_RTC_ExecutionContext)servant->m_ecRef);
    res = ec->_length;
  }

  return res;
}


/*
 Called from [impl_RTC_LightweightRTObject_get_participating_contexts()].
*/
int
RTObject_get_participating_contexts(impl_POA_RTC_RTObject *servant, RTC_ExecutionContextList *ec)
{
  int res = -1;

  if(ec == NULL){
   fprintf(stderr, "Invalid ExecutionContextList\n");
  }else{
    ec->_maximum = ec->_length = 0;
    ec->_release = 0;
    ec->_buffer = NULL;
    res = ec->_length;
  }

  return res;
}


/*
 Called from [impl_RTC_LightweightRTObject_initialize()].
*/
double
RTObject_getExecutionContextRate(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return (double)atof(Properties_getProperty(implobj->m_properties, "exec_cxt.periodic.rate"));
}

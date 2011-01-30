// -*- C++ -*-
/*!
 * @file  ConsoleIn.cpp
 * @brief Console input component
 */

#include "ConsoleIn.h"
#include <stdio.h>

// Module specification
// <rtc-template block="module_spec">
static const char* consolein_spec[] =
  {
    "implementation_id", "ConsoleIn",
    "type_name",         "ConsoleIn",
    "description",       "Console input component",
    "version",           "1.0",
    "vendor",            "Noriaki Ando, AIST",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

ConsoleIn *
ConsoleIn_create(RTC_Manager *manager)
{
  ConsoleIn *res = (ConsoleIn *)RtORB_calloc(sizeof(ConsoleIn), 1, "Create ConsoleIn");
  res->parent = RTC_DataFlowComponentBase_create(manager);
  res->m_outOut = RTC_OutPort_create(manager, "out", res->m_out);

  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>
  return res;
}

void
ConsoleIn_delete(ConsoleIn *obj)
{
  return;
}


RTC_ReturnCode_t
ConsoleIn_onInitialize(ConsoleIn *obj)
{
  /*
    add Event Listener : DataListener
   */
#if 0
  RTC_addConnectorDataListener(obj->m_outOut, ON_BUFFER_WRITE,
                                     DataListener_create("ON_BUFFER_WRITE"));
  RTC_addConnectorDataListener(obj->m_outOut, ON_BUFFER_FULL, 
                                     DataListener_create("ON_BUFFER_FULL"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_BUFFER_WRITE_TIMEOUT, 
                                     DataListener_create("ON_BUFFER_WRITE_TIMEOUT"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_BUFFER_OVERWRITE, 
                                     DataListener_create("ON_BUFFER_OVERWRITE"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_BUFFER_READ, 
                                     DataListener_create("ON_BUFFER_READ"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_SEND, 
                                     DataListener_create("ON_SEND"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_RECEIVED,
                                     DataListener_create("ON_RECEIVED"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_RECEIVER_FULL, 
                                     DataListener_create("ON_RECEIVER_FULL"));
  RTC_addConnectorDataListener(obj->m_outOut,ON_RECEIVER_TIMEOUT, 
                                     DataListener_create("ON_RECEIVER_TIMEOUT"));

  /*
    add Event Listener : ConnectorListener
   */
  RTC_addConnectorListener(Oobj->m_outOut,N_BUFFER_EMPTY,
                                     ConnListener_create("ON_BUFFER_EMPTY"));
  RTC_addConnectorListener(obj->m_outOut,ON_BUFFER_READ_TIMEOUT,
                                     ConnListener_create("ON_BUFFER_READ_TIMEOUT"));
  RTC_addConnectorListener(obj->m_outOut,ON_SENDER_EMPTY,
                                     ConnListener_create("ON_SENDER_EMPTY"));
  RTC_addConnectorListener(obj->m_outOut,ON_SENDER_TIMEOUT,
                                     ConnListener_create("ON_SENDER_TIMEOUT"));
  RTC_addConnectorListener(obj->m_outOut,ON_SENDER_ERROR,
                                     ConnListener_create("ON_SENDER_ERROR"));
  RTC_addConnectorListener(obj->m_outOut,ON_CONNECT,
                                     ConnListener_create("ON_CONNECT"));
  RTC_addConnectorListener(obj->m_outOut,ON_DISCONNECT,
                                     ConnListener_create("ON_CONNECT"));
#endif
  return RTC_RTC_OK;
}

RTC_ReturnCode_t
ConsoleIn_onExecute(ConsoleIn *obj, RTC_UniqueIdentifier ec_id)
{

  fprintf(stdout, "Please input number: ");
  fscanf(stdin, "%d", &obj->m_out->data);

  fprintf(stdout, "data=%d\n", obj->m_out->data);

  if (obj->m_out->data == 666) return RTC_ERROR;

  RTC_OutPort_write(obj->m_outOut);

  return RTC_RTC_OK;
}


void
ConsoleInInit(RTC_Manager* manager)
{
  RTC_Manager_registerFactory(manager, consolein_spec,
         ConsoleIn_create, ConsoleIn_delete);
}
  


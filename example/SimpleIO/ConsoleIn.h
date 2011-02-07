// -*- C++ -*-
/*!
 * @file  ConsoleIn.h
 * @brief Console input component
 */

#ifndef CONSOLEIN_H
#define CONSOLEIN_H

#include <rtm/OpenRTM.h>

#include <stdio.h>

#if 0
typedef struct DataListener_Object
{
   ConnectorDataListenerT *parent;
   CORBA_Typecode datatype = RTC_TimedLong_TC;

   char* n_name;

} DataListener;

DataListener *
DataListener_create(const char* name)
{
  DataListener *res = RtORB_callloc(sizeof(DataListener), 1, "DataListener_create");
  res->m_name = name;
  return res;
}

void
DataListener_delete(DataListener *obj)
{
  fprintf(stdout, "dtor of %s\n");
  return;
}

void
DataListener_operator(DataListener *obj, const ConnectorInfo *info, const TimedLong *data)
{
  fprintf(stdout, "------------------------------\n");
  fprintf(stdout, "Data Listener: %s\n", obj->m_name);
  fprintf(stdout, "Profile::name: %s\n", info->name);
  fprintf(stdout, "Profile::id:   %d\n", info->id);
  fprintf(stdout, "Time(sec):%ld\n", data->tm.sec);
  fprintf(stdout, "Time(nsec):%ld\n", data->tm.nsec);
  fprintf(stdout, "Data:          %d\n", data->data);
  fprintf(stdout, "------------------------------\n");
};

struct ConnListener_Object
{
  ConnectorListener *parent;
  char * m_name;

} ConnectorListener;

ConnectorListener *
ConnectorListener_create(const char* name)
{
  ConnectorListener *res = RtORB_callloc(sizeof(ConnectorListener), 1, "ConnectorListener_create");
  res->m_name = name;
  return res;
}

void
ConnecotorListener_delete(ConnectorListener *obj)
{
  fprintf(stdout, "dtor of %s\n", obj->m_name);
  return;
}

void
ConnectorListener_operator(ConnectorListener *obj, const ConnectorInfo *info)
{
  fprintf(stdout, "------------------------------\n");
  fprintf(stdout, "Connector Listener: %s\n", obj->m_name);
  fprintf(stdout, "Profile::name: %s\n", info->name);
  fprintf(stdout, "Profile::id:   %d\n", info->id);

  fprintf(stdout, "Profile::propertied:  ");
  OutPut_Properties(info->properties);
  fprintf(stdout, "\n");
  fprintf(stdout, "------------------------------\n");
};
#endif

typedef struct ConsoleIn_Object
{
  CORBA_RTC_RTObject  *rtobj;

  RTC_ReturnCode_t (*on_initialize)(struct ConsoleIn_Object * obj);

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj))on_Finalize;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Startup;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Shutdown;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Activate;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Deactivate;

  RTC_ReturnCode_t (*on_Execute)(struct ConsoleIn_Object *obj, RTC_UniqueIdentifier ec_id);

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Aborting;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Error;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_Reset;
 
  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_StateUpDate;

  // (RTC_ReturnCode_t (*)(struct ConsoleIn_Object * obj, RTC_UniqueId ec_id))on_RateChanged;

  // DataOutPort declaration
  RTC_TimedLong *m_out;
  //RTC_OutPort *m_outOut;
  OpenRTM_OutPortCdr *m_outOut;
  
} ConsoleIn;

#endif // CONSOLEIN_H

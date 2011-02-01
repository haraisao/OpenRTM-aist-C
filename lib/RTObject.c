/*


*/

#include <rtm/OpenRTM.h>
#include <rtm/OpenRTM-aist-skelimpl.h>


/*


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

*/
OpenRTM_OutPortCdr
RTC_OutPort_create(RTC_Manager *manager, const char *typ, void **data)
{

  OpenRTM_OutPortCdr res;
  CORBA_Environment ev;

  res = impl_OpenRTM_OutPortCdr__create(manager->m_pPOA, &ev);

  return res;
}


/*

*/
void
RTC_OutPort_write( OpenRTM_OutPortCdr *port )
{
  return;
}


RTC_Properties *
RTC_RTObject_getProperties(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return implobj->m_properties;
}

char *
RTC_RTObject_getCategory(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, "category");
}


char *
RTC_RTObject_getTypeName(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, "type_name");

}

char *
RTC_RTObject_getInstanceName(CORBA_RTC_RTObject obj)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, "instance_name");
}


int
RTC_RTObject_setProperty(CORBA_RTC_RTObject obj, char *name, char *value)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  Properties_setProperty(implobj->m_properties, name, value);
  return 1;
}

char *
RTC_RTObject_getProperty(CORBA_RTC_RTObject obj, char *name)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  return Properties_getProperty(implobj->m_properties, name);
}

int
RTC_RTObject_registerProperty(CORBA_RTC_RTObject obj, RTC_Properties *prop)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  implobj->m_properties = prop;
  return 1;
}

RTC_Properties *
RTC_RTObject_appendProperties(CORBA_RTC_RTObject obj, RTC_Properties *prop)
{
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;
  implobj->m_properties = Properties_appendProperties(implobj->m_properties, prop);
  
  return implobj->m_properties;
}

char **
RTC_RTObject_getNamingNames(CORBA_RTC_RTObject obj, int *len)
{
  len = 0;
  impl_POA_RTC_RTObject  *implobj=(impl_POA_RTC_RTObject *)obj->servant;



  return NULL;
}

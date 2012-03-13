#include "RtcTemp.h"
#include <stdio.h>

/* Prototype */
RTC_ReturnCode_t Rtc_onInitialize(RTComp *obj);
RTC_ReturnCode_t Rtc_onFinalize(RTComp *obj);
RTC_ReturnCode_t Rtc_onStartup(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onShutdown(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onActivated(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onDeactivated(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onExecute(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onAborting(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onError(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onReset(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onStateUpDate(RTComp *obj, RTC_UniqueId ec_id);
RTC_ReturnCode_t Rtc_onRateChanged(RTComp *obj, RTC_UniqueId ec_id);

/* Module specification */
static const char* rtc_spec[] =
  {
    "implementation_id", "RtcTemp",
    "type_name",         "RtcTemp",
    "description",       "RTC Template Component",
    "version",           "1.0",
    "vendor",            "User",
    "category",          "RTC",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C",
    "lang_type",         "compile",
    NULL, NULL
  };

/* Create Procedure */
RTComp *
Rtc_create(RTC_Manager *manager)
{

  /* ======== [Common action] ================================== */
  /** Create RtcBase Object **/
  CORBA_RTC_RTObject rtobj = RTC_DataFlowComponentBase_create(manager);

  /** Allocate memory for RTC **/
  RTComp *res = (RTComp *)RtORB_calloc(1, sizeof(RTComp), "Create RTC...");
  res->m_private = (RTC_Member *)RtORB_calloc(1, sizeof(RTC_Member), "Create RTC member...");

  /** Set function pointers of RTC's activity **/
  res->onInitialize = Rtc_onInitialize;
  /*
  res->onFinalize = Rtc_onFinalize;
  res->onStartup = Rtc_onStartup;
  res->onShutdown = Rtc_onShutdown;
  res->onActivated = Rtc_onActivated;
  res->onDeactivated = Rtc_onDeactivated;
  res->onExecute = Rtc_onExecute;
  res->onAborting = Rtc_onAborting;
  res->onError = Rtc_onError;
  res->onReset = Rtc_onReset;
  res->onStateUpDate = Rtc_onStateUpDate;
  res->onRateChanged = Rtc_onRateChanged;
  */

  /** Set pointer **/
  res->m_manager = manager;
  res->m_rtobjRef = rtobj;
  rtobj->impl_obj = (void *)res;   
  /* ========================================================== */   

  return res;
}

/* Delete Procedure */
void
Rtc_delete(RTComp *obj)
{
  return;
}


RTC_ReturnCode_t
Rtc_onInitialize(RTComp *obj)
{
  /** Get Private Member **/
  RTC_Member *private = (RTC_Member*)obj->m_private;

  /** Create DataPort **/

  return RTC_RTC_OK;
}

/*
RTC_ReturnCode_t
Rtc_onFinalize(RTComp *obj)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onStartup(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onShutdown(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onActivated(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onDeactivated(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onExecute(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onAborting(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onError(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onReset(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onStateUpDate(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/*
RTC_ReturnCode_t
Rtc_onRateChanged(RTComp *obj, RTC_UniqueId ec_id)
{
  return RTC_RTC_OK;
}
*/

/* Init Procedure */
void
RtcInit(RTC_Manager* manager)
{
  RTC_Manager_registerFactory(manager, rtc_spec, Rtc_create, Rtc_delete );
}

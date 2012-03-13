#include "SeqIn.h"
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
    "implementation_id", "SeqIn",
    "type_name",         "SeqIn",
    "description",       "Sequence input component",
    "version",           "1.0",
    "vendor",            "Noriaki Ando, AIST",
    "category",          "example",
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
  RTComp *res = (RTComp *)RtORB_calloc(1, sizeof(RTComp), "Create SeqIn...");
  res->m_private = (RTC_Member *)RtORB_calloc(1, sizeof(RTC_Member), "Create SeqIn member...");

  /** Set function pointers of RTC's activity **/
  res->onInitialize = Rtc_onInitialize;
  /*
  res->onFinalize = Rtc_onFinalize;
  res->onStartup = Rtc_onStartup;
  res->onShutdown = Rtc_onShutdown;
  res->onActivated = Rtc_onActivated;
  res->onDeactivated = Rtc_onDeactivated;
  */
  res->onExecute = Rtc_onExecute;
  /*
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
    /* TimedShortSeq */
  private->m_tmShortSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmShortSeq", "RTC_TimedShortSeq");
  if (private->m_tmShortSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmShortSeq = (RTC_TimedShortSeq*)private->m_tmShortSeqIn->m_value;

    /* TimedLongSeq */
  private->m_tmLongSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmLongSeq", "RTC_TimedLongSeq");
  if (private->m_tmLongSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmLongSeq = (RTC_TimedLongSeq*)private->m_tmLongSeqIn->m_value;

    /* TimedUShortSeq */
  private->m_tmUShortSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmUShortSeq", "RTC_TimedUShortSeq");
  if (private->m_tmUShortSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmUShortSeq = (RTC_TimedUShortSeq*)private->m_tmUShortSeqIn->m_value;

    /* TimedULongSeq */
  private->m_tmULongSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmULongSeq", "RTC_TimedULongSeq");
  if (private->m_tmULongSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmULongSeq = (RTC_TimedULongSeq*)private->m_tmULongSeqIn->m_value;

    /* TimedFloatSeq */
  private->m_tmFloatSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmFloatSeq", "RTC_TimedFloatSeq");
  if (private->m_tmFloatSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmFloatSeq = (RTC_TimedFloatSeq*)private->m_tmFloatSeqIn->m_value;

    /* TimedDoubleSeq */
  private->m_tmDoubleSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmDoubleSeq", "RTC_TimedDoubleSeq");
  if (private->m_tmDoubleSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmDoubleSeq = (RTC_TimedDoubleSeq*)private->m_tmDoubleSeqIn->m_value;

    /* TimedCharSeq */
  private->m_tmCharSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmCharSeq", "RTC_TimedCharSeq");
  if (private->m_tmCharSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmCharSeq = (RTC_TimedCharSeq*)private->m_tmCharSeqIn->m_value;

    /* TimedBooleanSeq */
  private->m_tmBooleanSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmBooleanSeq", "RTC_TimedBooleanSeq");
  if (private->m_tmBooleanSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmBooleanSeq = (RTC_TimedBooleanSeq*)private->m_tmBooleanSeqIn->m_value;

    /* TimedOctetSeq */
  private->m_tmOctetSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmOctetSeq", "RTC_TimedOctetSeq");
  if (private->m_tmOctetSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmOctetSeq = (RTC_TimedOctetSeq*)private->m_tmOctetSeqIn->m_value;

    /* TimedStringSeq */
  private->m_tmStringSeqIn = RTC_InPort_create(obj->m_rtobjRef, "tmStringSeq", "RTC_TimedStringSeq");
  if (private->m_tmStringSeqIn == NULL) return RTC_RTC_ERROR;
  else private->m_tmStringSeq = (RTC_TimedStringSeq*)private->m_tmStringSeqIn->m_value;

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


RTC_ReturnCode_t
Rtc_onExecute(RTComp *obj, RTC_UniqueId ec_id)
{
  int i;
  int length = -1;

  /** Get Private Member **/
  RTC_Member *private = (RTC_Member*)obj->m_private;

    /* TimedShortSeq */
  if (RTC_InPort_isNew(private->m_tmShortSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmShortSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmShortSeqIn, (&private->m_tmShortSeq->data), "data");
      printf("<TimedShortSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%d]",private->m_tmShortSeq->data._buffer[i]);
      printf("\n");

    }
  }

    /* TimedLongSeq */
  if (RTC_InPort_isNew(private->m_tmLongSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmLongSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmLongSeqIn, (&private->m_tmLongSeq->data), "data");
      printf("<TimedLongSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%d]",private->m_tmLongSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedUShortSeq */
  if (RTC_InPort_isNew(private->m_tmUShortSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmUShortSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmUShortSeqIn, (&private->m_tmUShortSeq->data), "data");
      printf("<TimedUShortSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%d]",private->m_tmUShortSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedULongSeq */
  if (RTC_InPort_isNew(private->m_tmULongSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmULongSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmULongSeqIn, (&private->m_tmULongSeq->data), "data");
      printf("<TimedULongSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%d]",private->m_tmULongSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedFloatSeq */
  if (RTC_InPort_isNew(private->m_tmFloatSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmFloatSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmFloatSeqIn, (&private->m_tmFloatSeq->data), "data");
      printf("<TimedFloatSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%f]",private->m_tmFloatSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedDoubleSeq */
  if (RTC_InPort_isNew(private->m_tmDoubleSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmDoubleSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmDoubleSeqIn, (&private->m_tmDoubleSeq->data), "data");
      printf("<TimedDoubleSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%lf]",private->m_tmDoubleSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedCharSeq */
  if (RTC_InPort_isNew(private->m_tmCharSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmCharSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmCharSeqIn, (&private->m_tmCharSeq->data), "data");
      printf("<TimedCharSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%c]",private->m_tmCharSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedBooleanSeq */
  if (RTC_InPort_isNew(private->m_tmBooleanSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmBooleanSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmBooleanSeqIn, (&private->m_tmBooleanSeq->data), "data");
      printf("<TimedBooleanSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%d]",private->m_tmBooleanSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedOctetSeq */
  if (RTC_InPort_isNew(private->m_tmOctetSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmOctetSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmOctetSeqIn, (&private->m_tmOctetSeq->data), "data");
      printf("<TimedOctetSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%c]",private->m_tmOctetSeq->data._buffer[i]);
      printf("\n");
    }
  }

    /* TimedStringSeq */
  if (RTC_InPort_isNew(private->m_tmStringSeqIn) > 0) {
    if(RTC_InPort_read(private->m_tmStringSeqIn) > 0) {
      length = RTC_InPort_getSeqLength(private->m_tmStringSeqIn, (&private->m_tmStringSeq->data), "data");
      printf("<TimedStringSeq>(Len:%d)",length);
      for (i = 0; i < length; i++) printf("\t[%s]",private->m_tmStringSeq->data._buffer[i]);
      printf("\n");
    }
  }

  return RTC_RTC_OK;
}


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

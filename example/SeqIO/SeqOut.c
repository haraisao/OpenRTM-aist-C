#include "SeqOut.h"
#include <stdio.h>
#include <stdlib.h>

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
    "implementation_id", "SeqOut",
    "type_name",         "SeqOut",
    "description",       "Sequence output component",
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
  RTComp *res = (RTComp *)RtORB_calloc(1, sizeof(RTComp), "Create SeqOut...");
  res->m_private = (RTC_Member *)RtORB_calloc(1, sizeof(RTC_Member), "Create SeqOut member...");

  /** Set function pointers of RTC's activity **/
  res->onInitialize = Rtc_onInitialize;
  res->onFinalize = Rtc_onFinalize;
  /*
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
  private->m_tmShortSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmShortSeq", TC_RTC_TimedShortSeq);
  if (private->m_tmShortSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmShortSeq = (RTC_TimedShortSeq*)private->m_tmShortSeqOut->m_value;

    /* TimedLongSeq */
  private->m_tmLongSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmLongSeq", TC_RTC_TimedLongSeq);
  if (private->m_tmLongSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmLongSeq = (RTC_TimedLongSeq*)private->m_tmLongSeqOut->m_value;

    /* TimedUShortSeq */
  private->m_tmUShortSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmUShortSeq", TC_RTC_TimedUShortSeq);
  if (private->m_tmUShortSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmUShortSeq = (RTC_TimedUShortSeq*)private->m_tmUShortSeqOut->m_value;

    /* TimedULongSeq */
  private->m_tmULongSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmULongSeq", TC_RTC_TimedULongSeq);
  if (private->m_tmULongSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmULongSeq = (RTC_TimedULongSeq*)private->m_tmULongSeqOut->m_value;

    /* TimedFloatSeq */
  private->m_tmFloatSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmFloatSeq", TC_RTC_TimedFloatSeq);
  if (private->m_tmFloatSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmFloatSeq = (RTC_TimedFloatSeq*)private->m_tmFloatSeqOut->m_value;

    /* TimedDoubleSeq */
  private->m_tmDoubleSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmDoubleSeq", TC_RTC_TimedDoubleSeq);
  if (private->m_tmDoubleSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmDoubleSeq = (RTC_TimedDoubleSeq*)private->m_tmDoubleSeqOut->m_value;

    /* TimedCharSeq */
  private->m_tmCharSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmCharSeq", TC_RTC_TimedCharSeq);
  if (private->m_tmCharSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmCharSeq = (RTC_TimedCharSeq*)private->m_tmCharSeqOut->m_value;

    /* TimedBooleanSeq */
  private->m_tmBooleanSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmBooleanSeq", TC_RTC_TimedBooleanSeq);
  if (private->m_tmBooleanSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmBooleanSeq = (RTC_TimedBooleanSeq*)private->m_tmBooleanSeqOut->m_value;

    /* TimedOctetSeq */
  private->m_tmOctetSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmOctetSeq", TC_RTC_TimedOctetSeq);
  if (private->m_tmOctetSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmOctetSeq = (RTC_TimedOctetSeq*)private->m_tmOctetSeqOut->m_value;

    /* TimedStringSeq */
  private->m_tmStringSeqOut = RTC_OutPort_create(obj->m_rtobjRef, "tmStringSeq", TC_RTC_TimedStringSeq);
  if (private->m_tmStringSeqOut == NULL) return RTC_RTC_ERROR;
  else private->m_tmStringSeq = (RTC_TimedStringSeq*)private->m_tmStringSeqOut->m_value;

  /* set Sequence length */
  RTC_OutPort_setSeqLength(private->m_tmShortSeqOut, 3, (&private->m_tmShortSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmLongSeqOut, 3, (&private->m_tmLongSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmUShortSeqOut, 3, (&private->m_tmUShortSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmULongSeqOut, 3, (&private->m_tmULongSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmFloatSeqOut, 3, (&private->m_tmFloatSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmDoubleSeqOut, 3, (&private->m_tmDoubleSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmCharSeqOut, 3, (&private->m_tmCharSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmBooleanSeqOut, 3, (&private->m_tmBooleanSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmOctetSeqOut, 3, (&private->m_tmOctetSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmStringSeqOut, 3, (&private->m_tmStringSeq->data), "data");

  /* get Sequence length (DEBUG) */
  printf(" [Sequence length] = %d\n"
         ,RTC_OutPort_getSeqLength(private->m_tmLongSeqOut, (&private->m_tmLongSeq->data), "data"));

  return RTC_RTC_OK;
}


RTC_ReturnCode_t
Rtc_onFinalize(RTComp *obj)
{

  RTC_Member *private = (RTC_Member*)obj->m_private;

  /* reset Sequence length to "0" */
  RTC_OutPort_setSeqLength(private->m_tmShortSeqOut, 0, (&private->m_tmShortSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmLongSeqOut, 0, (&private->m_tmLongSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmUShortSeqOut, 0, (&private->m_tmUShortSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmULongSeqOut, 0, (&private->m_tmULongSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmFloatSeqOut, 0, (&private->m_tmFloatSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmDoubleSeqOut, 0, (&private->m_tmDoubleSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmCharSeqOut, 0, (&private->m_tmCharSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmBooleanSeqOut, 0, (&private->m_tmBooleanSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmOctetSeqOut, 0, (&private->m_tmOctetSeq->data), "data");
  RTC_OutPort_setSeqLength(private->m_tmStringSeqOut, 0, (&private->m_tmStringSeq->data), "data");

  return RTC_RTC_OK;
}


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
  /** Get Private Member **/
  RTC_Member *private = (RTC_Member*)obj->m_private;

  /** Make data **/
  static int counter;
  if (++counter > 10) counter = 0;
  CORBA_char c = (counter%2 == 0) ? 'A' : 'a';
  CORBA_char c1 = (counter%2 == 0) ? 'B' : 'b';
  CORBA_char c2 = (counter%2 == 0) ? 'C' : 'c';
  CORBA_boolean b = (counter%2 == 0) ? 0 : 1;
  CORBA_boolean b1 = (counter%2 == 0) ? 0 : 2;
  CORBA_boolean b2 = (counter%2 == 0) ? 0 : 3;
  CORBA_octet o = (counter%2 == 0) ? 'X' : 'x';
  CORBA_octet o1 = (counter%2 == 0) ? 'Y' : 'y';
  CORBA_octet o2 = (counter%2 == 0) ? 'Z' : 'z';
  CORBA_string s = (counter%2 == 0) ? "ABCDEFG" : "abcdefg";
  CORBA_string s1 = (counter%2 == 0) ? "HIJKLMN" : "hijklmn";
  CORBA_string s2 = (counter%2 == 0) ? "OPQRSTU" : "opqrstu";

    /* TimedShortSeq */
  private->m_tmShortSeq->tm.sec = private->m_tmShortSeq->tm.nsec = counter;
  private->m_tmShortSeq->data._buffer[0] = counter * (-10) - 1;
  private->m_tmShortSeq->data._buffer[1] = counter * (-10) - 2;
  private->m_tmShortSeq->data._buffer[2] = counter * (-10) - 3;

    /* TimedLongSeq */
  private->m_tmLongSeq->tm.sec = private->m_tmLongSeq->tm.nsec = counter;
  if ((counter % 2) == 0) {
    RTC_OutPort_setSeqLength(private->m_tmLongSeqOut, 5, (&private->m_tmLongSeq->data), "data");
    private->m_tmLongSeq->data._buffer[0] = counter * (-10) - 4;
    private->m_tmLongSeq->data._buffer[1] = counter * (-10) - 5;
    private->m_tmLongSeq->data._buffer[2] = counter * (-10) - 6;
    private->m_tmLongSeq->data._buffer[3] = counter * (-10) - 7;
    private->m_tmLongSeq->data._buffer[4] = counter * (-10) - 8;
  } else {
    RTC_OutPort_setSeqLength(private->m_tmLongSeqOut, 3, (&private->m_tmLongSeq->data), "data");
    private->m_tmLongSeq->data._buffer[0] = counter * (-10) - 4;
    private->m_tmLongSeq->data._buffer[1] = counter * (-10) - 5;
    private->m_tmLongSeq->data._buffer[2] = counter * (-10) - 6;
  }

    /* TimedUShortSeq */
  private->m_tmUShortSeq->tm.sec = private->m_tmUShortSeq->tm.nsec = counter;
  private->m_tmUShortSeq->data._buffer[0] = counter * 10 + 1;
  private->m_tmUShortSeq->data._buffer[1] = counter * 10 + 2;
  private->m_tmUShortSeq->data._buffer[2] = counter * 10 + 3;

    /* TimedULongSeq */
  private->m_tmULongSeq->tm.sec = private->m_tmULongSeq->tm.nsec = counter;
  private->m_tmULongSeq->data._buffer[0] = counter * 10 + 4;
  private->m_tmULongSeq->data._buffer[1] = counter * 10 + 5;
  private->m_tmULongSeq->data._buffer[2] = counter * 10 + 6;

    /* TimedFloatSeq */
  private->m_tmFloatSeq->tm.sec = private->m_tmFloatSeq->tm.nsec = counter;
  private->m_tmFloatSeq->data._buffer[0] = counter * 0.1 + 0.01;
  private->m_tmFloatSeq->data._buffer[1] = counter * 0.1 + 0.02;
  private->m_tmFloatSeq->data._buffer[2] = counter * 0.1 + 0.03;

    /* TimedDoubleSeq */
  private->m_tmDoubleSeq->tm.sec = private->m_tmDoubleSeq->tm.nsec = counter;
  private->m_tmDoubleSeq->data._buffer[0] = counter * 0.01 + 0.001;
  private->m_tmDoubleSeq->data._buffer[1] = counter * 0.01 + 0.002;
  private->m_tmDoubleSeq->data._buffer[2] = counter * 0.01 + 0.003;

    /* TimedCharSeq */
  private->m_tmCharSeq->tm.sec = private->m_tmCharSeq->tm.nsec = counter;
  private->m_tmCharSeq->data._buffer[0] = c;
  private->m_tmCharSeq->data._buffer[1] = c1;
  private->m_tmCharSeq->data._buffer[2] = c2;

    /* TimedBooleanSeq */
  private->m_tmBooleanSeq->tm.sec = private->m_tmBooleanSeq->tm.nsec = counter;
  private->m_tmBooleanSeq->data._buffer[0] = b;
  private->m_tmBooleanSeq->data._buffer[1] = b1;
  private->m_tmBooleanSeq->data._buffer[2] = b2;

    /* TimedOctetSeq */
  private->m_tmOctetSeq->tm.sec = private->m_tmOctetSeq->tm.nsec = counter;
  private->m_tmOctetSeq->data._buffer[0] = o;
  private->m_tmOctetSeq->data._buffer[1] = o1;
  private->m_tmOctetSeq->data._buffer[2] = o2;

    /* TimedStringSeq */
  private->m_tmStringSeq->tm.sec = private->m_tmStringSeq->tm.nsec = counter;
  private->m_tmStringSeq->data._buffer[0] = s;
  private->m_tmStringSeq->data._buffer[1] = s1;
  private->m_tmStringSeq->data._buffer[2] = s2;


  /** Debug write **/
  printf("===============[counter:%02d]=====================\n",counter);

  printf("[TimedShortSeq] data[0]=%d\tdata[1]=%d\tdata[2]=%d\n"
              ,private->m_tmShortSeq->data._buffer[0]
              ,private->m_tmShortSeq->data._buffer[1]
              ,private->m_tmShortSeq->data._buffer[2]);

  printf("[TimedLongSeq] ");
  int i;
  int length = RTC_OutPort_getSeqLength(private->m_tmLongSeqOut, (&private->m_tmLongSeq->data), "data");
  for (i = 0; i < length; i++) printf("data[%d]=%d\t",i,private->m_tmLongSeq->data._buffer[i]);
  printf("\n");

  printf("[TimedUShortSeq] data[0]=%d\tdata[1]=%d\tdata[2]=%d\n"
              ,private->m_tmUShortSeq->data._buffer[0]
              ,private->m_tmUShortSeq->data._buffer[1]
              ,private->m_tmUShortSeq->data._buffer[2]);

  printf("[TimedULongSeq] data[0]=%d\tdata[1]=%d\tdata[2]=%d\n"
              ,private->m_tmULongSeq->data._buffer[0]
              ,private->m_tmULongSeq->data._buffer[1]
              ,private->m_tmULongSeq->data._buffer[2]);

  printf("[TimedFloatSeq] data[0]=%f\tdata[1]=%f\tdata[2]=%f\n"
              ,private->m_tmFloatSeq->data._buffer[0]
              ,private->m_tmFloatSeq->data._buffer[1]
              ,private->m_tmFloatSeq->data._buffer[2]);

  printf("[TimedDoubleSeq] data[0]=%lf\tdata[1]=%lf\tdata[2]=%lf\n"
              ,private->m_tmDoubleSeq->data._buffer[0]
              ,private->m_tmDoubleSeq->data._buffer[1]
              ,private->m_tmDoubleSeq->data._buffer[2]);

  printf("[TimedCharSeq] data[0]=%c\tdata[1]=%c\tdata[2]=%c\n"
              ,private->m_tmCharSeq->data._buffer[0]
              ,private->m_tmCharSeq->data._buffer[1]
              ,private->m_tmCharSeq->data._buffer[2]);

  printf("[TimedBooleanSeq] data[0]=%d\tdata[1]=%d\tdata[2]=%d\n"
              ,private->m_tmBooleanSeq->data._buffer[0]
              ,private->m_tmBooleanSeq->data._buffer[1]
              ,private->m_tmBooleanSeq->data._buffer[2]);

  printf("[TimedOctetSeq] data[0]=%c\tdata[1]=%c\tdata[2]=%c\n"
              ,private->m_tmOctetSeq->data._buffer[0]
              ,private->m_tmOctetSeq->data._buffer[1]
              ,private->m_tmOctetSeq->data._buffer[2]);

  printf("[TimedStringSeq] data[0]=%s\tdata[1]=%s\tdata[2]=%s\n"
              ,private->m_tmStringSeq->data._buffer[0]
              ,private->m_tmStringSeq->data._buffer[1]
              ,private->m_tmStringSeq->data._buffer[2]);

  printf("--------------------------------------------------\n\n");

  /** Write(Send) Data **/
  RTC_OutPort_write(private->m_tmShortSeqOut);
  RTC_OutPort_write(private->m_tmLongSeqOut);
  RTC_OutPort_write(private->m_tmUShortSeqOut);
  RTC_OutPort_write(private->m_tmULongSeqOut);
  RTC_OutPort_write(private->m_tmFloatSeqOut);
  RTC_OutPort_write(private->m_tmDoubleSeqOut);
  RTC_OutPort_write(private->m_tmCharSeqOut);
  RTC_OutPort_write(private->m_tmBooleanSeqOut);
  RTC_OutPort_write(private->m_tmOctetSeqOut);
  RTC_OutPort_write(private->m_tmStringSeqOut);

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

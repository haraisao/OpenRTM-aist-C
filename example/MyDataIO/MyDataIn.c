#include "MyDataIn.h"
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
    "implementation_id", "MyDataIn",
    "type_name",         "MyDataIn",
    "description",       "MyData input component",
    "version",           "1.0",
    "vendor",            "Yusuke Nakajima, AIST",
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
  RTComp *res = (RTComp *)RtORB_calloc(1, sizeof(RTComp), "Create MyDataIn...");
  res->m_private = (RTC_Member *)RtORB_calloc(1, sizeof(RTC_Member), "Create MyDataIn member...");

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
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct2");
  private->m_in2In = RTC_InPort_create(obj->m_rtobjRef, "in2", "RTC_TimedLong");

  if (private->m_inIn == NULL)
  {
    return RTC_RTC_ERROR;
  } else {
    /* Set value's pointer */
    private->m_in = (MyData_MyStruct2*)private->m_inIn->m_value;
  }

  if (private->m_in2In == NULL)
  {
    return RTC_RTC_ERROR;
  } else {
    private->m_in2 = (RTC_TimedLong*)private->m_in2In->m_value;
  }

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
  /** Get Private Member **/
  RTC_Member *private = (RTC_Member*)obj->m_private;

/*========= [DataPort1] =========================*/

  /* Check New data */
  if (RTC_InPort_isNew(private->m_inIn) > 0)
  {
    if (RTC_InPort_read(private->m_inIn) < 0) return RTC_RTC_ERROR;

    /* MyData_MyStruct2 */
    int i;
    int length = -1;
    length = RTC_InPort_getSeqLength(private->m_inIn, (&private->m_in->mystseq), "mystseq");

    fprintf(stdout, "<GET> sh = %d \n",private->m_in->sh);

    for(i=0; i<length; i++) {
      fprintf(stdout, "<GET> <mystseq>{ [%d] str=%s <myst>{lon=%d dou=%lf str=%s sh=%d ch=%c oc=%c boo=%c} dou=%lf ch=%c sh=%d } \n"
                    ,i
                    ,private->m_in->mystseq._buffer[i].str
                    ,private->m_in->mystseq._buffer[i].myst.lon
                    ,private->m_in->mystseq._buffer[i].myst.dou
                    ,private->m_in->mystseq._buffer[i].myst.str
                    ,private->m_in->mystseq._buffer[i].myst.sh
                    ,private->m_in->mystseq._buffer[i].myst.ch
                    ,private->m_in->mystseq._buffer[i].myst.oc
                    ,private->m_in->mystseq._buffer[i].myst.boo
                    ,private->m_in->mystseq._buffer[i].dou
                    ,private->m_in->mystseq._buffer[i].ch
                    ,private->m_in->mystseq._buffer[i].sh);
    }
    fprintf(stdout, "<GET> dou = %lf  \n\n",private->m_in->dou);
  }


/*========= [DataPort2] =========================*/

  /* Check New data */
  if (RTC_InPort_isNew(private->m_in2In) > 0)
  {
    if (RTC_InPort_read(private->m_in2In) < 0) return RTC_RTC_ERROR;
    /* RTC_TimedLong */
    fprintf(stdout, "<Port2> <GET> {Time:%d[s] %d[ns]} data=%d\n"
            ,private->m_in2->tm.sec, private->m_in2->tm.nsec ,private->m_in2->data);
    fprintf(stdout, "\n"); 
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

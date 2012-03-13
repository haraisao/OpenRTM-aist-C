#include "MyDataOut.h"
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
    "implementation_id", "MyDataOut",
    "type_name",         "MyDataOut",
    "description",       "MyData output component",
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
  RTComp *res = (RTComp *)RtORB_calloc(1, sizeof(RTComp), "Create MyDataOut...");
  res->m_private = (RTC_Member *)RtORB_calloc(1, sizeof(RTC_Member), "Create MyDataOut member...");

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
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct2");
  private->m_out2Out = RTC_OutPort_create(obj->m_rtobjRef, "out2", "RTC_TimedLong");

  if (private->m_outOut == NULL)
  {
    return RTC_RTC_ERROR;

  } else {
    /* Set value's pointer */
    private->m_out = (MyData_MyStruct2*)private->m_outOut->m_value;
  }

  if (private->m_out2Out == NULL)
  {
    return RTC_RTC_ERROR;
  } else {
    private->m_out2 = (RTC_TimedLong*)private->m_out2Out->m_value;
  }

  /* set Sequence length */
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)(&private->m_out->mystseq), "mystseq");
  printf("[DEBUG] <mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mystseq), "mystseq"));

  return RTC_RTC_OK;
}


RTC_ReturnCode_t
Rtc_onFinalize(RTComp *obj)
{
  RTC_Member *private = (RTC_Member*)obj->m_private;

  RTC_OutPort_setSeqLength(private->m_outOut, 0, (void*)(&private->m_out->mystseq), "mystseq");

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

  static int counter;
  if (++counter > 10) counter = 0;

/*========= [DataPort1] =========================*/
  /* MyData_MyStruct2 */
  int i;

  /* short data */
  private->m_out->sh = 10 * counter;
  fprintf(stdout, " sh = %d \n",private->m_out->sh);

  /* sequence<MyStruct1> data */
  for(i=0; i<3; i++) {

    if (counter%2 == 0) {
      private->m_out->mystseq._buffer[i].str = (i%2 == 0) ? "efghijklmnop" : "ABCD";
    } else {
      private->m_out->mystseq._buffer[i].str = (i%2 == 0) ? "ABCD" : "efghijklmnop";
    }

    private->m_out->mystseq._buffer[i].myst.lon = 4 * counter;
    private->m_out->mystseq._buffer[i].myst.dou = -0.4 * counter;
    private->m_out->mystseq._buffer[i].myst.str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
    private->m_out->mystseq._buffer[i].myst.sh = 2 * counter;
    private->m_out->mystseq._buffer[i].myst.ch = (counter%2 == 0) ? 'A' : 'a';
    private->m_out->mystseq._buffer[i].myst.oc = (counter%2 == 0) ? 'z' : 'Z';
    private->m_out->mystseq._buffer[i].myst.boo = (counter%2 == 0) ? 40 : 41;

    private->m_out->mystseq._buffer[i].dou = (i%2==0) ? 0.4*(counter+1+i) : -0.4*(counter+1+i);
    private->m_out->mystseq._buffer[i].ch = (counter%2 == 0) ? 'B' : 'b';
    private->m_out->mystseq._buffer[i].sh = (i%2==0) ? -2*(counter+1+i) : 2*(counter+1+i);

    fprintf(stdout, " <mystseq>{ [%d] str=%s <myst>{lon=%d dou=%lf str=%s sh=%d ch=%c oc=%c boo=%c} dou=%lf ch=%c sh=%d } \n"
                  ,i
                  ,private->m_out->mystseq._buffer[i].str
                  ,private->m_out->mystseq._buffer[i].myst.lon
                  ,private->m_out->mystseq._buffer[i].myst.dou
                  ,private->m_out->mystseq._buffer[i].myst.str
                  ,private->m_out->mystseq._buffer[i].myst.sh
                  ,private->m_out->mystseq._buffer[i].myst.ch
                  ,private->m_out->mystseq._buffer[i].myst.oc
                  ,private->m_out->mystseq._buffer[i].myst.boo
                  ,private->m_out->mystseq._buffer[i].dou
                  ,private->m_out->mystseq._buffer[i].ch
                  ,private->m_out->mystseq._buffer[i].sh);
  }

  /* double data */
  private->m_out->dou = 0.1 * counter;
  fprintf(stdout, " dou = %lf  \n\n",private->m_out->dou);

  /* Write data */
  if (RTC_OutPort_write(private->m_outOut) < 0) return RTC_RTC_ERROR;

/*========= [DataPort2] =========================*/

 /* RTC_TimedLong */
  private->m_out2->tm.sec = 0;
  private->m_out2->tm.nsec = 0;
  private->m_out2->data = counter * 1;

  /* Write data */
  if (RTC_OutPort_write(private->m_out2Out) < 0) return RTC_RTC_ERROR;

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

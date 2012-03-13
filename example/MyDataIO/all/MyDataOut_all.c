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
  manager->m_pComp = res;
  manager->m_pComp->m_rtobjRef = rtobj;
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
#if 0  /* [修正ポイント2] 使用するデータ型のポート生成処理のみコメントアウトを外す  */
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "RTC_TimedLong");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyDouble");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyULong");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyEnum");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyAny");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyLongSeq");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStringSeq");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStructSeq");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct1");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct2");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct3");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct4");
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct5");
#else
  private->m_outOut = RTC_OutPort_create(obj->m_rtobjRef, "out", "MyData_MyStruct1");
  private->m_out2Out = RTC_OutPort_create(obj->m_rtobjRef, "out2", "RTC_TimedLong");
#endif

  if (private->m_outOut == NULL)
  {
    return RTC_RTC_ERROR;

  } else {
    /* Set value's pointer */
#if 0 /* [修正ポイント3] 使用するデータ型のポインタセットのみコメントアウトを外す  */
    private->m_out = (RTC_TimedLong*)private->m_outOut->m_value;
    private->m_out = (MyData_MyDouble*)private->m_outOut->m_value;
    private->m_out = (MyData_MyULong*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStruct*)private->m_outOut->m_value;
    private->m_out = (MyData_MyEnum*)private->m_outOut->m_value;
    private->m_out = (MyData_MyAny*)private->m_outOut->m_value;
    private->m_out = (MyData_MyLongSeq*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStringSeq*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStructSeq*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStruct1*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStruct2*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStruct3*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStruct4*)private->m_outOut->m_value;
    private->m_out = (MyData_MyStruct5*)private->m_outOut->m_value;
#else
    private->m_out = (MyData_MyStruct1*)private->m_outOut->m_value;
#endif
  }

  if (private->m_out2Out == NULL)
  {
    return RTC_RTC_ERROR;
  } else {
    private->m_out2 = (RTC_TimedLong*)private->m_out2Out->m_value;
  }

  /* set Sequence length */ /* [修正ポイント4] 可変長データ型の使用の場合のみ、該当データ型のサイズセット処理のみコメントアウトを外す  */

#if 0  /* MyData_MyLongSeq( example of 'tk_alias') */
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)private->m_out, "");
  printf("[DEBUG] getSeqLen() = %d\n"
       ,RTC_OutPort_getSeqLength(private->m_outOut, (void*)private->m_out, ""));
#endif



#if 0  /* MyData_MyStringSeq( example of 'tk_alias') */
  RTC_OutPort_setSeqLength(private->m_outOut, 5, (void*)private->m_out, "");
  printf("[DEBUG] getSeqLen() = %d\n"
       ,RTC_OutPort_getSeqLength(private->m_outOut, (void*)private->m_out, ""));
#endif



#if 0  /* MyData_MyStructSeq( example of 'tk_alias') */
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)private->m_out, "");
  printf("[DEBUG] getSeqLen() = %d\n"
       ,RTC_OutPort_getSeqLength(private->m_outOut, (void*)private->m_out, ""));
#endif




#if 0  /* MyData_MyStruct2 */
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)(&private->m_out->mystseq), "mystseq");
  printf("[DEBUG] <mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mystseq), "mystseq"));
#endif




#if 0  /* MyData_MyStruct3 */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mystringseq), "mystringseq");
  printf("[DEBUG] <mystringseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mystringseq), "mystringseq"));
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)(&private->m_out->mylongseq), "mylongseq");
  printf("[DEBUG] <mylongseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mylongseq), "mylongseq"));
#endif




#if 0  /* MyData_MyStruct4 */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->myanyseq), "myanyseq");
  printf("[DEBUG] <myanyseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->myanyseq), "myanyseq"));
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)(&private->m_out->myenumseq), "myenumseq");
  printf("[DEBUG] <myenumseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->myenumseq), "myenumseq"));
#endif





#if 0  /* MyData_MyStruct5 */
/*
mystdumseq (sequence<MyStructDummy>)  {setLength(2)}  << A >>
  |------> _buffer[0] (MyStructDummy)
  |           |------->mystseq (sequence<MyStruct>)  {setLength(3)} << A-1 >>
  |                       |------> _buffer[0] (MyStruct)
  |                       |------> _buffer[1] (MyStruct)
  |                       |------> _buffer[2] (MyStruct)
  |------> _buffer[1] (MyStructDummy)
              |------->mystseq (sequence<MyStruct>)  {setLength(1)} << A-2 >>
                          |------> _buffer[0] (MyStruct)

mysttmpseq (sequence<MyStructTmp>)  {setLength(2)}  << B >>
  |------> _buffer[0] (MyStructTmp)
  |           |------->mystdumseq (sequence<MyStructDummy>)  {setLength(2)} << B-1-a >>
  |           |           |------> _buffer[0] (MyStructDummy)
  |           |           |            |------->mystseq (sequence<MyStruct>)  {setLength(2)} << B-1-a-1 >>
  |           |           |                        |------> _buffer[0] (MyStruct)
  |           |           |                        |------> _buffer[1] (MyStruct)
  |           |           |------> _buffer[1] (MyStructDummy)
  |           |                        |------->mystseq (sequence<MyStruct>)  {setLength(2)} << B-1-a-2 >>
  |           |                                    |------> _buffer[0] (MyStruct)
  |           |                                    |------> _buffer[1] (MyStruct)
  |           |
  |           |------->mslist (MyStructTmpList(alias))  {setLength(2)}  << B-1-b >>
  |                       |------> _buffer[0] (MyStructTmp0)
  |                       |            |------->mystringseq (MyStringSeq(alias))  {setLength(2)}  << B-1-b-1 >>
  |                       |                        |------> _buffer[0] (string)
  |                       |                        |------> _buffer[1] (string)
  |                       |------> _buffer[1] (MyStructTmp0)
  |                                    |------->mystringseq (MyStringSeq(alias))  {setLength(1)}  << B-1-b-2 >>
  |                                                |------> _buffer[0] (string)
  |
  |------> _buffer[1] (MyStructTmp)
              |------->mystdumseq (sequence<MyStructDummy>)  {setLength(2)} << B-2-a >>
              |           |------> _buffer[0] (MyStructDummy)
              |           |            |------->mystseq (sequence<MyStruct>)  {setLength(1)} << B-2-a-1 >>
              |           |                        |------> _buffer[0] (MyStruct)
              |           |------> _buffer[1] (MyStructDummy)
              |                        |------->mystseq (sequence<MyStruct>)  {setLength(1)} << B-2-a-2 >>
              |                                    |------> _buffer[0] (MyStruct)
              |
              |------->mslist (MyStructTmpList(alias))  {setLength(2)}  << B-2-b >>
                          |------> _buffer[0] (MyStructTmp0)
                          |            |------->mystringseq (MyStringSeq(alias))  {setLength(2)}  << B-2-b-1 >>
                          |                        |------> _buffer[0] (string)
                          |                        |------> _buffer[1] (string)
                          |------> _buffer[1] (MyStructTmp0)
                                       |------->mystringseq (MyStringSeq(alias))  {setLength(1)}  << b-2-b-2 >>
                                                   |------> _buffer[0] (string)
*/

    /* << A >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mystdumseq), "mystdumseq");
  printf("[DEBUG] <mystdumseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mystdumseq), "mystdumseq"));

    /* << A-1 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 3, (void*)(&private->m_out->mystdumseq._buffer[0].mystseq), "mystdumseq.mystseq");
  printf("[DEBUG] <mystdumseq[0].mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mystdumseq._buffer[0].mystseq), "mystdumseq.mystseq"));

    /* << A-2 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 1, (void*)(&private->m_out->mystdumseq._buffer[1].mystseq), "mystdumseq.mystseq");
  printf("[DEBUG] <mystdumseq[1].mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mystdumseq._buffer[1].mystseq), "mystdumseq.mystseq"));

    /* << B >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq), "mysttmpseq");
  printf("[DEBUG] <mysttmpseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq), "mysttmpseq"));

    /* << B-1-a >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[0].mystdumseq), "mysttmpseq.mystdumseq");
  printf("[DEBUG] <mysttmpseq[0].mystdumseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mystdumseq), "mysttmpseq.mystdumseq"));

    /* << B-1-a-1 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[0].mystdumseq._buffer[0].mystseq), "mysttmpseq.mystdumseq.mystseq");
  printf("[DEBUG] <mysttmpseq[0].mystdumseq[0].mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mystdumseq._buffer[0].mystseq), "mysttmpseq.mystdumseq.mystseq"));

    /* << B-1-a-2 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[0].mystdumseq._buffer[1].mystseq), "mysttmpseq.mystdumseq.mystseq");
  printf("[DEBUG] <mysttmpseq[0].mystdumseq[1].mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mystdumseq._buffer[1].mystseq), "mysttmpseq.mystdumseq.mystseq"));

    /* << B-1-b >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist), "mysttmpseq.mslist");
  printf("[DEBUG] <mysttmpseq[0].mslist> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist), "mysttmpseq.mslist"));

    /* << B-1-b-1 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist._buffer[0].mystringseq), "mysttmpseq.mslist.mystringseq");
  printf("[DEBUG] <mysttmpseq[0].mslist[0].mystringseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist._buffer[0].mystringseq), "mysttmpseq.mslist.mystringseq"));

    /* << B-1-b-2 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 1, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist._buffer[1].mystringseq), "mysttmpseq.mslist.mystringseq");
  printf("[DEBUG] <mysttmpseq[0].mslist[1].mystringseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist._buffer[1].mystringseq), "mysttmpseq.mslist.mystringseq"));

    /* << B-2-a >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[1].mystdumseq), "mysttmpseq.mystdumseq");
  printf("[DEBUG] <mysttmpseq[1].mystdumseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[1].mystdumseq), "mysttmpseq.mystdumseq"));

    /* << B-2-a-1 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 1, (void*)(&private->m_out->mysttmpseq._buffer[1].mystdumseq._buffer[0].mystseq), "mysttmpseq.mystdumseq.mystseq");
  printf("[DEBUG] <mysttmpseq[1].mystdumseq[0].mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[1].mystdumseq._buffer[0].mystseq), "mysttmpseq.mystdumseq.mystseq"));

    /* << B-2-a-2 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 1, (void*)(&private->m_out->mysttmpseq._buffer[1].mystdumseq._buffer[1].mystseq), "mysttmpseq.mystdumseq.mystseq");
  printf("[DEBUG] <mysttmpseq[1].mystdumseq[1].mystseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[1].mystdumseq._buffer[1].mystseq), "mysttmpseq.mystdumseq.mystseq"));

    /* << B-2-b >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[1].mslist), "mysttmpseq.mslist");
  printf("[DEBUG] <mysttmpseq[1].mslist> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[0].mslist), "mysttmpseq.mslist"));

    /* << B-2-b-1 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 2, (void*)(&private->m_out->mysttmpseq._buffer[1].mslist._buffer[0].mystringseq), "mysttmpseq.mslist.mystringseq");
  printf("[DEBUG] <mysttmpseq[1].mslist[0].mystringseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[1].mslist._buffer[0].mystringseq), "mysttmpseq.mslist.mystringseq"));

    /* << B-2-b-2 >> */
  RTC_OutPort_setSeqLength(private->m_outOut, 1, (void*)(&private->m_out->mysttmpseq._buffer[1].mslist._buffer[1].mystringseq), "mysttmpseq.mslist.mystringseq");
  printf("[DEBUG] <mysttmpseq[1].mslist[1].mystringseq> getSeqLen() = %d\n",RTC_OutPort_getSeqLength(private->m_outOut, (void*)(&private->m_out->mysttmpseq._buffer[1].mslist._buffer[1].mystringseq), "mysttmpseq.mslist.mystringseq"));

#endif

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

  static int counter;
  if (++counter > 10) counter = 0;
/*========= [DataPort1] =========================*/

  /* Set data */ /* [修正ポイント5] 使用するデータ型のデータセット処理のみコメントアウトを外す  */

#if 0 /* MyData_MyDouble */
  *(private->m_out) = 0.1 * counter;
  fprintf(stdout, "  dou=%lf\n",*(private->m_out));
#endif



#if 0 /* MyData_MyULong */
  *(private->m_out) = 3 * counter;
  fprintf(stdout, "  ulong=%d\n",*(private->m_out));
#endif



#if 0 /* MyData_MyStruct */
  private->m_out->lon = 4 * counter;
  private->m_out->dou = -0.4 * counter;
  private->m_out->str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->sh = 2 * counter;
  private->m_out->ch = (counter%2 == 0) ? 'A' : 'a';
  private->m_out->oc = (counter%2 == 0) ? 'z' : 'Z';
  private->m_out->boo = (counter%2 == 0) ? 40 : 41;
#endif



#if 0 /* MyData_MyEnum */
  if (counter%4 == 0) *(private->m_out) = MyData_SHORT_TYPE;
  else if (counter%4 == 1) *(private->m_out) = MyData_LONG_TYPE;
  else if (counter%4 == 2) *(private->m_out) = MyData_FLOAT_TYPE;
  else *(private->m_out) = MyData_DOUBLE_TYPE;
#endif



#if 0  /* MyData_MyAny */
  private->m_out->str = (counter%2 == 0) ? "ABCD" : "efghijklmnop";
  CORBA_any_alloc(&(private->m_out->anyval), TC_CORBA_string, 0);
  private->m_out->anyval._val->val_str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->anyval._release = (counter%2 == 0) ? 1 : 0;
#endif



#if 0 /* MyData_MyLongSeq */
  private->m_out->_buffer[0] = counter * 0;
  private->m_out->_buffer[1] = counter * 1;
  private->m_out->_buffer[2] = counter * 2;
#endif



#if 0 /* MyData_MyStringSeq */
  private->m_out->_buffer[0] = (counter%2 == 0) ? "ABCD" : "efghijklmnop";
  private->m_out->_buffer[1] = (counter%2 == 0) ? "EFGHIJKLMNOP" : "abcd";
  private->m_out->_buffer[2] = (counter%2 == 0) ? "012345" : "9876543210";
  private->m_out->_buffer[3] = (counter%2 == 0) ? "" : "";
  private->m_out->_buffer[4] = (counter%2 == 0) ? "a" : "b";
#endif



#if 0 /* MyData_MyStructSeq */
  private->m_out->_buffer[0].lon = 4 * counter;
  private->m_out->_buffer[0].dou = -0.4 * counter;
  private->m_out->_buffer[0].str = (counter%2 == 0) ? "1bcd" : "1FGHIJKLMNOP";
  private->m_out->_buffer[0].sh = 2 * counter;
  private->m_out->_buffer[0].ch = (counter%2 == 0) ? 'A' : 'a';
  private->m_out->_buffer[0].boo = (counter%2 == 0) ? 40 : 41;
  private->m_out->_buffer[1].lon = 5 * counter;
  private->m_out->_buffer[1].dou = -0.5 * counter;
  private->m_out->_buffer[1].str = (counter%2 == 0) ? "2bcd" : "2FGHIJKLMNOP";
  private->m_out->_buffer[1].sh = 3 * counter;
  private->m_out->_buffer[1].ch = (counter%2 == 0) ? 'B' : 'b';
  private->m_out->_buffer[1].boo = (counter%2 == 0) ? 37 : 38;
  private->m_out->_buffer[2].lon = 6 * counter;
  private->m_out->_buffer[2].dou = -0.6 * counter;
  private->m_out->_buffer[2].str = (counter%2 == 0) ? "3bcd" : "3FGHIJKLMNOP";
  private->m_out->_buffer[2].sh = 5 * counter;
  private->m_out->_buffer[2].ch = (counter%2 == 0) ? 'C' : 'c';
  private->m_out->_buffer[2].boo = (counter%2 == 0) ? 42 : 43;
#endif



#if 1  /* MyData_MyStruct1 */
  private->m_out->str = (counter%2 == 0) ? "ABCD" : "efghijklmnop";
  private->m_out->myst.lon = 4 * counter;
  private->m_out->myst.dou = -0.4 * counter;
  private->m_out->myst.str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->myst.sh = 2 * counter;
  private->m_out->myst.ch = (counter%2 == 0) ? 'A' : 'a';
  private->m_out->myst.oc = (counter%2 == 0) ? 'z' : 'Z';
  private->m_out->myst.boo = (counter%2 == 0) ? 40 : 41;
  private->m_out->dou = 0.4 * counter;
  private->m_out->ch = (counter%2 == 0) ? 'B' : 'b';
  private->m_out->sh = -2 * counter;
#endif



#if 0  /* MyData_MyStruct2 */
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

#endif



#if 0  /* MyData_MyStruct3 */
  private->m_out->mystringseq._buffer[0] = (counter%2 == 0) ? "ABCD" : "efghijklmnop";
  private->m_out->mystringseq._buffer[1] = (counter%2 == 0) ? "OPQRSTUVWXYZ" : "wxyz";
  private->m_out->mydouble = 0.1 * counter;
  private->m_out->dou = -0.1 * counter;
  private->m_out->mylongseq._buffer[0] = counter * 0;
  private->m_out->mylongseq._buffer[1] = counter * 1;
  private->m_out->mylongseq._buffer[2] = counter * 2;
#endif



#if 0  /* MyData_MyStruct4 */
    /* string */
  private->m_out->str = (counter%2 == 0) ? "ABCD" : "efghijklmnop";
    /* MyAny */
  private->m_out->myanydata.str = (counter%2 == 0) ? "ABCD" : "efghijklmnop";
  CORBA_any_alloc(&(private->m_out->myanydata.anyval), TC_CORBA_string, 0);
  private->m_out->myanydata.anyval._val->val_str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->myanydata.anyval._release = (counter%2 == 0) ? 1 : 0;
    /* sequence<MyAny> (2) */
  private->m_out->myanyseq._buffer[0].str = (counter%2 == 0) ? "EFGHIJKLMNOP" : "abcd";
  CORBA_any_alloc(&(private->m_out->myanyseq._buffer[0].anyval), TC_CORBA_string, 0);
  private->m_out->myanyseq._buffer[0].anyval._val->val_str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->myanyseq._buffer[0].anyval._release = (counter%2 == 0) ? 1 : 0;
  private->m_out->myanyseq._buffer[1].str = (counter%2 == 0) ? "OPQRSTUVWXYZ" : "wxyz";
  CORBA_any_alloc(&(private->m_out->myanyseq._buffer[1].anyval), TC_CORBA_string, 0);
  private->m_out->myanyseq._buffer[1].anyval._val->val_str = (counter%2 == 0) ? "OPQRSTUVWXYZ" : "wxyz";
  private->m_out->myanyseq._buffer[1].anyval._release = (counter%2 == 0) ? 0 : 1;
    /* MyEnum */
  if (counter%4 == 0) private->m_out->myenumdata = MyData_SHORT_TYPE;
  else if (counter%4 == 1) private->m_out->myenumdata = MyData_LONG_TYPE;
  else if (counter%4 == 2) private->m_out->myenumdata = MyData_FLOAT_TYPE;
  else private->m_out->myenumdata = MyData_DOUBLE_TYPE;
    /* string */
  private->m_out->strstr = (counter%2 == 0) ? "OPQRSTUVWXYZ" : "wxyz";
    /* sequence<MyEnum> (3) */
  if (counter%4 == 0) {
    private->m_out->myenumseq._buffer[0] = MyData_SHORT_TYPE;
    private->m_out->myenumseq._buffer[1] = MyData_LONG_TYPE;
    private->m_out->myenumseq._buffer[2] = MyData_FLOAT_TYPE;
  } else if (counter%4 == 1) {
    private->m_out->myenumseq._buffer[0] = MyData_LONG_TYPE;
    private->m_out->myenumseq._buffer[1] = MyData_FLOAT_TYPE;
    private->m_out->myenumseq._buffer[2] = MyData_DOUBLE_TYPE;
  } else if (counter%4 == 2) {
    private->m_out->myenumseq._buffer[0] = MyData_FLOAT_TYPE;
    private->m_out->myenumseq._buffer[1] = MyData_DOUBLE_TYPE;
    private->m_out->myenumseq._buffer[2] = MyData_SHORT_TYPE;
  } else {
    private->m_out->myenumseq._buffer[0] = MyData_DOUBLE_TYPE;
    private->m_out->myenumseq._buffer[1] = MyData_SHORT_TYPE;
    private->m_out->myenumseq._buffer[2] = MyData_LONG_TYPE;
  }
#endif



#if 0  /* MyData_MyStruct5 */
  int i,j,k;

  /* << A >> */
  for(i=0; i<2; i++) {
    for(j=0;j<3; j++) {
      if ((i == 1) && (j > 0)) break;
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].lon = 4 * (j+1) * counter;
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].dou = -0.4 * (j+1) * counter;
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].sh = 2 * (j+1) * counter;
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].ch = (counter%2 == 0) ? 'A' : 'a';
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].oc = (counter%2 == 0) ? 'z' : 'Z';
      private->m_out->mystdumseq._buffer[i].mystseq._buffer[j].boo = (counter%2 == 0) ? 40 : 41;
    }
    private->m_out->mystdumseq._buffer[i].mydouble = 0.4 * (i+1) * counter;
  }

  /* << B >> */
  for(i=0; i<2; i++) {
    private->m_out->mysttmpseq._buffer[i].mydouble = -0.4 * counter; 
    for(j=0;j<2; j++) {
      for(k=0;k<2; k++) {
        if ((i == 1) && (k > 0))  break;
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].lon = 4 * (k+1) * counter;
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].dou = -0.4 * (k+1) * counter;
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].sh = 2 * (k+1) * counter;
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].ch = (counter%2 == 0) ? 'A' : 'a';
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].oc = (counter%2 == 0) ? 'z' : 'Z';
        private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].boo = (counter%2 == 0) ? 40 : 41;
      }
      private->m_out->mysttmpseq._buffer[i].mystdumseq._buffer[j].mydouble = 0.4 * (j+1) * counter;
    }
  }    
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[0].str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[1].str = (counter%2 == 0) ? "EFGHIJKLMNOP" : "abcd";
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[0].str = (counter%2 == 0) ? "EFGHIjKLMNOP" : "abCd";
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[1].str = (counter%2 == 0) ? "abcD" : "EFgHIJKLMNOP";
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[0].mystringseq._buffer[0] = "AAAA";
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[0].mystringseq._buffer[1] = "zz";
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[1].mystringseq._buffer[0] = "aaa";
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[0].mystringseq._buffer[0] = "BBBBBBBBBBBBBB";
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[0].mystringseq._buffer[1] = "cc";
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[1].mystringseq._buffer[0] = "dddddddd";
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[0].dou = 0.4 * counter;
  private->m_out->mysttmpseq._buffer[0].mslist._buffer[1].dou = 0.8 * counter;
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[0].dou = -0.04 * counter;
  private->m_out->mysttmpseq._buffer[1].mslist._buffer[1].dou = -0.08 * counter;

  /* << Other >> */
  private->m_out->dou = 0.3 * counter;
  private->m_out->str = (counter%2 == 0) ? "abcd" : "EFGHIJKLMNOP";
  private->m_out->sh = 3 * counter;
#endif

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

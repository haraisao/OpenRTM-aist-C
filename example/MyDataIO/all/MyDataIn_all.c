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
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "RTC_TimedLong");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyDouble");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyULong");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyEnum");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyAny");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyLongSeq");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStringSeq");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStructSeq");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct1");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct2");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct3");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct4");
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct5");
#else
  private->m_inIn = RTC_InPort_create(obj->m_rtobjRef, "in", "MyData_MyStruct1");
  private->m_in2In = RTC_InPort_create(obj->m_rtobjRef, "in2", "RTC_TimedLong");
#endif

  if (private->m_inIn == NULL)
  {
    return RTC_RTC_ERROR;
  } else {
    /* Set value's pointer */
#if 0  /* [修正ポイント3] 使用するデータ型のポインタセットのみコメントアウトを外す  */
    private->m_in = (RTC_TimedLong*)private->m_inIn->m_value;
    private->m_in = (MyData_MyDouble*)private->m_inIn->m_value;
    private->m_in = (MyData_MyULong*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStruct*)private->m_inIn->m_value;
    private->m_in = (MyData_MyEnum*)private->m_inIn->m_value;
    private->m_in = (MyData_MyAny*)private->m_inIn->m_value;
    private->m_in = (MyData_MyLongSeq*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStringSeq*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStructSeq*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStruct1*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStruct2*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStruct3*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStruct4*)private->m_inIn->m_value;
    private->m_in = (MyData_MyStruct5*)private->m_inIn->m_value;
#else
    private->m_in = (MyData_MyStruct1*)private->m_inIn->m_value;
#endif
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

  /* Check New data */  /* [修正ポイント5] 使用するデータ型のデータ出力処理のみコメントアウトを外す  */
  if (RTC_InPort_isNew(private->m_inIn) > 0)
  {
    if (RTC_InPort_read(private->m_inIn) < 0) return RTC_RTC_ERROR;

#if 0 /* MyData_MyDouble */
  fprintf(stdout, "  dou=%lf\n",*(private->m_in));
#endif



#if 0 /* MyData_MyULong */
  fprintf(stdout, "  ulong=%d\n",*(private->m_in));
#endif



#if 0  /* MyData_MyStruct */
    fprintf(stdout, "  str=%s sh=%d dou=%lf ch=%c oc=%c boo=%c lon=%d\n",private->m_in->str,private->m_in->sh,private->m_in->dou,private->m_in->ch,private->m_in->oc,private->m_in->boo,private->m_in->lon);
#endif



#if 0 /* MyData_MyEnum */
  fprintf(stdout, "<GET>  MyData_MyEnum=%d\n",*(private->m_in));
#endif



#if 0  /* MyData_MyAny */
  fprintf(stdout, "<GET>  str=%s [Any->tc]=%s [Any->val->val_str]=%s [Any->release]=%d\n",private->m_in->str,  private->m_in->anyval._type->repository_id, private->m_in->anyval._val->val_str, private->m_in->anyval._release);
#endif



#if 0  /* MyData_MyLongSeq */
    fprintf(stdout, "data[0]=%ld data[1]=%ld data[2]=%ld\n"
            ,private->m_in->_buffer[0],private->m_in->_buffer[1],private->m_in->_buffer[2]);
#endif



#if 0  /* MyData_MyStringSeq */
    fprintf(stdout, "data[0]=%s data[1]=%s data[2]=%s data[3]=%s data[4]=%s\n"
            ,private->m_in->_buffer[0],private->m_in->_buffer[1],private->m_in->_buffer[2],private->m_in->_buffer[3],private->m_in->_buffer[4]);
#endif



#if 0  /* MyData_MyStructSeq */
    fprintf(stdout, "<GET> [0]  str=%s sh=%d dou=%lf ch=%c oc=%c boo=%c lon=%d\n",private->m_in->_buffer[0].str,private->m_in->_buffer[0].sh,private->m_in->_buffer[0].dou,private->m_in->_buffer[0].ch,private->m_in->_buffer[0].oc,private->m_in->_buffer[0].boo,private->m_in->_buffer[0].lon);
    fprintf(stdout, "<GET> [1]  str=%s sh=%d dou=%lf ch=%c oc=%c boo=%c lon=%d\n",private->m_in->_buffer[1].str,private->m_in->_buffer[1].sh,private->m_in->_buffer[1].dou,private->m_in->_buffer[1].ch,private->m_in->_buffer[1].oc,private->m_in->_buffer[1].boo,private->m_in->_buffer[1].lon);
    fprintf(stdout, "<GET> [2]  str=%s sh=%d dou=%lf ch=%c oc=%c boo=%c lon=%d\n",private->m_in->_buffer[2].str,private->m_in->_buffer[2].sh,private->m_in->_buffer[2].dou,private->m_in->_buffer[2].ch,private->m_in->_buffer[2].oc,private->m_in->_buffer[2].boo,private->m_in->_buffer[2].lon);
#endif



#if 1  /* MyData_MyStruct1 */
  fprintf(stdout, "<GET>  str=%s dou=%lf ch=%c sh=%d\n",private->m_in->str, private->m_in->dou ,private->m_in->ch, private->m_in->sh);
  fprintf(stdout, "<GET>    [myst] str=%s sh=%d dou=%lf ch=%c oc=%c boo=%c lon=%d\n\n",private->m_in->myst.str,private->m_in->myst.sh,private->m_in->myst.dou,private->m_in->myst.ch,private->m_in->myst.oc,private->m_in->myst.boo,private->m_in->myst.lon);
#endif



#if 0  /* MyData_MyStruct2 */
  int i;

  fprintf(stdout, "<GET> sh = %d \n",private->m_in->sh);

  for(i=0; i<3; i++) {
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

#endif



#if 0  /* MyData_MyStruct3 */
  fprintf(stdout, "<GET>  str[0]=%s str[1]=%s mydou=%lf dou=%lf lon[0]=%d lon[1]=%d lon[2]=%d\n",private->m_in->mystringseq._buffer[0],private->m_in->mystringseq._buffer[1], private->m_in->mydouble, private->m_in->dou ,private->m_in->mylongseq._buffer[0] ,private->m_in->mylongseq._buffer[1] ,private->m_in->mylongseq._buffer[2]);
#endif



#if 0  /* MyData_MyStruct4 */
  fprintf(stdout, "<GET>  str=%s strstr=%s\n",private->m_in->str,private->m_in->strstr);
  fprintf(stdout, "<GET> [Any] str=%s [Any->tc]=%s [Any->val->val_str]=%s [Any->release]=%d\n",private->m_in->myanydata.str,  private->m_in->myanydata.anyval._type->repository_id, private->m_in->myanydata.anyval._val->val_str, private->m_in->myanydata.anyval._release);
  fprintf(stdout, "<GET> [Enum] myenumdata=%d\n",private->m_in->myenumdata);
  fprintf(stdout, "<GET>  [AnySeq][0] str=%s [Any->tc]=%s [Any->val->val_str]=%s [Any->release]=%d\n",private->m_in->myanyseq._buffer[0].str,  private->m_in->myanyseq._buffer[0].anyval._type->repository_id, private->m_in->myanyseq._buffer[0].anyval._val->val_str, private->m_in->myanyseq._buffer[0].anyval._release);
  fprintf(stdout, "<GET>  [AnySeq][1] str=%s [Any->tc]=%s [Any->val->val_str]=%s [Any->release]=%d\n",private->m_in->myanyseq._buffer[1].str,  private->m_in->myanyseq._buffer[1].anyval._type->repository_id, private->m_in->myanyseq._buffer[1].anyval._val->val_str, private->m_in->myanyseq._buffer[1].anyval._release);
  fprintf(stdout, "<GET>  [EnumSeq] myenumseq[0]=%d myenumseq[1]=%d myenumseq[2]=%d\n",private->m_in->myenumseq._buffer[0],private->m_in->myenumseq._buffer[1],private->m_in->myenumseq._buffer[2]);
  fprintf(stdout,"\n\n");
#endif



#if 0  /* MyData_MyStruct5 */
  int i,j,k;

  fprintf(stdout, " ****** <GET> {(MyStruct5)} ****** \n"); 
  /* << A >> */
  fprintf(stdout, " === <GET> {sequence<MyStructDummy> mystdumseq;} ===\n"); 
  for(i=0; i<2; i++) {
    for(j=0;j<3; j++) {
      if ((i == 1) && (j > 0)) break;
      fprintf(stdout, "   [%d][%d] mydouble=%lf <mystseq>{lon=%d dou=%lf str=%s sh=%d ch=%c oc=%c boo=%c}\n"
                    ,i,j
                    ,private->m_in->mystdumseq._buffer[i].mydouble
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].lon
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].dou
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].str
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].sh
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].ch
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].oc
                    ,private->m_in->mystdumseq._buffer[i].mystseq._buffer[j].boo);
    }
  }

  /* << B >> (sequence<MyStructTmp> mysttmpseq;) */
  fprintf(stdout, " === <GET> {sequence<MyStructTmp> mysttmpseq;} ===\n"); 
    /* (sequence<MyStructDummy> mystdumseq;) */
  for(i=0; i<2; i++) {
    for(j=0;j<2; j++) {
      for(k=0;k<2; k++) {
        if ((i == 1) && (k > 0)) break;
        fprintf(stdout, "   [%d][%d][%d] mydouble=%lf <mystseq>{lon=%d dou=%lf str=%s sh=%d ch=%c oc=%c boo=%c}\n"
                      ,i,j,k
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mydouble
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].lon
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].dou
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].str
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].sh
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].ch
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].oc
                      ,private->m_in->mysttmpseq._buffer[i].mystdumseq._buffer[j].mystseq._buffer[k].boo);
      }
    }
  }

    /* (MyDouble mydouble;)+(MyStructTmpList mslist;) */
  for(i=0; i<2; i++) {
    fprintf(stdout, "   [%d] mydouble=%lf <mystseq>{str[0]=%s str[1]=%s <strseq>{[0][0]=%s [0][1]=%s [1][0]=%s} dou[0]=%lf doub[1]=%lf}\n"
                  ,i
                  ,private->m_in->mysttmpseq._buffer[i].mydouble
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[0].str
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[1].str
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[0].mystringseq._buffer[0]
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[0].mystringseq._buffer[1]
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[1].mystringseq._buffer[0]
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[0].dou
                  ,private->m_in->mysttmpseq._buffer[i].mslist._buffer[1].dou );
  }

  /* << Other >>  */
  fprintf(stdout, " === <GET> [Other] {dou=%lf str=%s sh=%d} ===\n",private->m_in->dou, private->m_in->str ,private->m_in->sh);

  fprintf(stdout, "\n"); 
#endif

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

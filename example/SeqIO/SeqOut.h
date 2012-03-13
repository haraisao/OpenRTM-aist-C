#ifndef RTC_H
#define RTC_H

#include <rtm/OpenRTM.h>
#include <stdio.h>

typedef struct RTComponent_Member_struct 
{
  /* This is private member value of [RTComp] structure. */

  /* Please insert user's parameter here. */

  /* DataPort declaration */
  RTC_TimedShortSeq    *m_tmShortSeq;
  RTC_TimedLongSeq     *m_tmLongSeq;
  RTC_TimedUShortSeq   *m_tmUShortSeq;
  RTC_TimedULongSeq    *m_tmULongSeq;
  RTC_TimedFloatSeq    *m_tmFloatSeq;
  RTC_TimedDoubleSeq   *m_tmDoubleSeq;
  RTC_TimedCharSeq     *m_tmCharSeq;
  RTC_TimedBooleanSeq  *m_tmBooleanSeq;
  RTC_TimedOctetSeq    *m_tmOctetSeq;
  RTC_TimedStringSeq   *m_tmStringSeq;

  RTC_OutPort *m_tmShortSeqOut;
  RTC_OutPort *m_tmLongSeqOut; 
  RTC_OutPort *m_tmUShortSeqOut;
  RTC_OutPort *m_tmULongSeqOut;
  RTC_OutPort *m_tmFloatSeqOut;
  RTC_OutPort *m_tmDoubleSeqOut;
  RTC_OutPort *m_tmCharSeqOut;
  RTC_OutPort *m_tmBooleanSeqOut;
  RTC_OutPort *m_tmOctetSeqOut;
  RTC_OutPort *m_tmStringSeqOut;

} RTC_Member;


#endif // RTC_H

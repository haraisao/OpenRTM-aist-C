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

  RTC_InPort *m_tmShortSeqIn;
  RTC_InPort *m_tmLongSeqIn; 
  RTC_InPort *m_tmUShortSeqIn;
  RTC_InPort *m_tmULongSeqIn;
  RTC_InPort *m_tmFloatSeqIn;
  RTC_InPort *m_tmDoubleSeqIn;
  RTC_InPort *m_tmCharSeqIn;
  RTC_InPort *m_tmBooleanSeqIn;
  RTC_InPort *m_tmOctetSeqIn;
  RTC_InPort *m_tmStringSeqIn;

} RTC_Member;


#endif // RTC_H

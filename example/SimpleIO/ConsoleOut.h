#ifndef RTC_H
#define RTC_H

#include <rtm/OpenRTM.h>
#include <stdio.h>

typedef struct RTComponent_Member_struct 
{
  /* This is private member value of [RTComp] structure. */

  /* Please insert user's parameter here. */

  /* DataPort declaration */
  RTC_TimedLong *m_in;
  RTC_InPort *m_inIn;

} RTC_Member;


#endif // RTC_H

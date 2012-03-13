#ifndef RTC_H
#define RTC_H

#include <rtm/OpenRTM.h>
#include <stdio.h>
/*--- [Add] ---*/
#include "idl/MyDataType.h" 

typedef struct RTComponent_Member_struct 
{
  /* This is private member value of [RTComp] structure. */

  /* Please insert user's parameter here. */

  /* DataPort declaration */
  MyData_MyStruct2  *m_in;
  RTC_TimedLong     *m_in2;

  /* InPort */
  RTC_InPort *m_inIn;
  RTC_InPort *m_in2In;

} RTC_Member;


#endif // RTC_H

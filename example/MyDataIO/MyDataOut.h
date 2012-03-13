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
  MyData_MyStruct2  *m_out;
  RTC_TimedLong     *m_out2;

  /* OutPort */
  RTC_OutPort *m_outOut;
  RTC_OutPort *m_out2Out;

} RTC_Member;


#endif // RTC_H

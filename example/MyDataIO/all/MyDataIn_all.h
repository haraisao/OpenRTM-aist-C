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

#if 0  /* [修正ポイント1] 使用するデータ型のポインタのみコメントアウトを外す  */
  /* DataPort declaration */
  RTC_TimedLong *m_in;
  /* User Original Data Types */
  MyData_MyDouble          *m_in;
  MyData_MyULong           *m_in;
  MyData_MyStruct          *m_in;
  MyData_MyEnum            *m_in;
  MyData_MyAny             *m_in;
  MyData_MyLongSeq         *m_in;
  MyData_MyStringSeq       *m_in;
  MyData_MyStructSeq       *m_in;
  MyData_MyStruct1         *m_in;
  MyData_MyStruct2         *m_in;
  MyData_MyStruct3         *m_in;
  MyData_MyStruct4         *m_in;
  MyData_MyStruct5         *m_in;
#else
  MyData_MyStruct1         *m_in;  /* DataPort1用 */
  RTC_TimedLong  *m_in2;           /* DataPort2用 */
#endif

  /* InPort */
  RTC_InPort *m_inIn;  /* DataPort1用 */
  RTC_InPort *m_in2In; /* DataPort2用 */

} RTC_Member;


#endif // RTC_H

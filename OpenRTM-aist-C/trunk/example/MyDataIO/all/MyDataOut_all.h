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
  RTC_TimedLong *m_out;
  /* User Original Data Types */
  MyData_MyDouble          *m_out;
  MyData_MyULong           *m_out;
  MyData_MyStruct          *m_out;
  MyData_MyEnum            *m_out;
  MyData_MyAny             *m_out;
  MyData_MyLongSeq         *m_out;
  MyData_MyStringSeq       *m_out;
  MyData_MyStructSeq       *m_out;
  MyData_MyStruct1         *m_out;
  MyData_MyStruct2         *m_out;
  MyData_MyStruct3         *m_out;
  MyData_MyStruct4         *m_out;
  MyData_MyStruct5         *m_out;
#else
  MyData_MyStruct1         *m_out;  /* DataPort1用 */
  RTC_TimedLong  *m_out2;           /* DataPort2用 */
#endif

  /* OutPort */
  RTC_OutPort *m_outOut;  /* DataPort1用 */
  RTC_OutPort *m_out2Out; /* DataPort2用 */

} RTC_Member;


#endif // RTC_H

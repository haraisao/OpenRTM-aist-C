/*



*/
#include <rtm/OpenRTM.h>


SDOPackage_NVList * 
NVUtil_new()
{
  SDOPackage_NVList * res;
  res = ( SDOPackage_NVList *)malloc(sizeof(SDOPackage_NVList));
  memset(res, 0, sizeof(SDOPackage_NVList));
  return res;
}

void 
NVUtil_dump(SDOPackage_NVList nv)
{

  return;
}


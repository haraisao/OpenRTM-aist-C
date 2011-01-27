/*


*/

#ifndef RTM_MANAGER_H
#define RTM_MANAGER_H

#include <rtm/OpenRTM-aist.h>
#include <rtm/OpenRTM-aist-decls.h>

#define RTC_CREATED	0
#define RTC_INACTIVE	1
#define RTC_ACTIVE	2
#define RTC_RUNNING	3
#define RTC_ERROR	-1


typedef struct RTC_Manager_struct{
  void *private;
  ECMode_t mode;
  int32_t status;
  RTC_ReturnCode_t (*module_init_func)(struct RTC_Manager_struct *);

}RTC_Manager;


/**** Functions ****/
RTC_Manager * RTC_Manager_init(int argc, char **argv);
void RTC_Manager_setModuleInitProc(RTC_Manager *manager, 
     RTC_ReturnCode_t (*init_func)(RTC_Manager *manager));
void RTC_Manager_activateManager(RTC_Manager *manager);
void RTC_Manager_runManager(RTC_Manager *manager, ECMode_t mode);
void RTC_Manager_stopManager(RTC_Manager *manager);

void RTC_Manager_delete(RTC_Manager *manager);

CORBA_RTC_RTObject* RTC_Manager_createComponent(RTC_Manager *manager, const char *name);


void RTC_Manager_registerFactory(RTC_Manager *manager, RTC_Properties *profile,
      void *(*creat_func)(RTC_Manager *manager),void (*delete_func)(void **obj));



#endif /* RTM_MANAGER_H */

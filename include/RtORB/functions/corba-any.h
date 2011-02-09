/*

*/

#ifndef RTM_CORBA_ANY_H
#define RTM_CORBA_ANY_H

/*

*/
void CORBA_any_alloc(CORBA_any *any, CORBA_TypeCode tc, int32_t clear);

/*

*/
void CORBA_any_set_value_duplicate(CORBA_any *any, struct CORBA_TypeCode_struct *tc, char *data, int len);

/*

*/
void CORBA_any_set_value(CORBA_any *any, struct CORBA_TypeCode_struct *tc, char *data, int32_t len);

/*

*/
void CORBA_any_set_exception_value(CORBA_any *any, struct CORBA_TypeCode_struct * tc, void *value, CORBA_boolean release);

/*

*/
void CORBA_any_set_exception(CORBA_any *any, CORBA_any *src);

/*

*/
void * CORBA_any_get_value(CORBA_any* any);

/*

*/
void CORBA_any_clear(CORBA_any *any);

/*

*/
char * CORBA_any_get_encoded(CORBA_any *any, int32_t *len);


#endif

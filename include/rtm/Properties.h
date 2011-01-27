/*


*/

#ifndef RTM_PROPERTIES_H
#define RTM_PROPERTIES_H


typedef struct Properties_struct {
    char * name;
    char * value;
    char * default_value;
    const char * m_empty;

    struct Properties_struct *root;
    struct Properties_struct **leaf;
} RTC_Properties;

#endif /* RTM_PROPERTIES_H */


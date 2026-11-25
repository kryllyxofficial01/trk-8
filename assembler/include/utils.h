#ifndef __TRK8_UTILS_H
#define __TRK8_UTILS_H

#include <ctype.h>

#ifndef TRK8_MAX_BUFFER_LENGTH
    #define TRK8_MAX_BUFFER_LENGTH (1024)
#endif

void to_lowercase(char* string);

#endif
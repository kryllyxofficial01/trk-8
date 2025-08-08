#ifndef __TRK8_UTILS_H
#define __TRK8_UTILS_H

#include <stdio.h>

#ifndef TRK8_BIT_CHECK
    #define TRK8_BIT_CHECK(_value, _index) ((_value) & (1 << (_index)))
#endif

#ifndef TRK8_BIT_SET
    #define TRK8_BIT_SET(_value, _index) ((_value) |= (1 << (_index)))
#endif

#ifndef TRK8_BIT_UNSET
    #define TRK8_BIT_UNSET(_value, _index) ((_value) &= ~(1 << (_index)))
#endif

#endif
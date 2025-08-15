#ifndef __TRK8_UTILS_H
#define __TRK8_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef TRK8_BIT_CHECK
    #define TRK8_BIT_CHECK(_value, _index) ((_value) & (1 << (_index)))
#endif

#ifndef TRK8_BIT_SET
    #define TRK8_BIT_SET(_value, _index) ((_value) |= (1 << (_index)))
#endif

#ifndef TRK8_BIT_UNSET
    #define TRK8_BIT_UNSET(_value, _index) ((_value) &= ~(1 << (_index)))
#endif

#ifndef TRK8_WORD
    #define TRK8_WORD(_high, _low) ((_high << 8) | _low)
#endif

#ifndef TRK8_GET_LOW_BYTE
    #define TRK8_GET_LOW_BYTE(_value) (_value & 0xff)
#endif

#ifndef TRK8_GET_HIGH_BYTE
    #define TRK8_GET_HIGH_BYTE(_value) ((_value >> 8) & 0xff)
#endif

#endif
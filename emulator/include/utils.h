#ifndef __TRK8_UTILS_H
#define __TRK8_UTILS_H

#ifndef TRK8_MAKE_WORD
    #define TRK8_MAKE_WORD(_low, _high) ((_high << 8) | _low)
#endif

#ifndef TRK8_GET_LOW_BYTE
    #define TRK8_GET_LOW_BYTE(_value) (_value & 0xff)
#endif

#ifndef TRK8_GET_HIGH_BYTE
    #define TRK8_GET_HIGH_BYTE(_value) ((_value >> 8) & 0xff)
#endif

#endif
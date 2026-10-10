#ifndef __TRK8_UTILS_H
#define __TRK8_UTILS_H

#ifndef TRK8_MAKE_WORD
    #define TRK8_MAKE_WORD(_low, _high) (((_high) << 8) | (_low))
#endif

#ifndef TRK8_GET_LOW_BYTE
    #define TRK8_GET_LOW_BYTE(_value) ((_value) & 0xff)
#endif

#ifndef TRK8_GET_HIGH_BYTE
    #define TRK8_GET_HIGH_BYTE(_value) (((_value) >> 8) & 0xff)
#endif

#ifndef TRK8_BIT_GET
    #define TRK8_BIT_GET(_value, _index) (((_value) >> (_index)) & 0x01)
#endif

#ifndef TRK8_BIT_SET
    #define TRK8_BIT_SET(_value, _index) (_value) |= (0x01 << (_index))
#endif

#ifndef TRK8_BIT_UNSET
    #define TRK8_BIT_UNSET(_value, _index) (_value) &= ~(0x01 << (_index))
#endif

#endif
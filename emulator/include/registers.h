#ifndef __TRK8_REGISTERS_H
#define __TRK8_REGISTERS_H

#include "utils.h"

#ifndef TRK8_NEGATIVE_FLAG_INDEX
    #define TRK8_NEGATIVE_FLAG_INDEX (0)
#endif

#ifndef TRK8_CARRY_FLAG_INDEX
    #define TRK8_CARRY_FLAG_INDEX (1)
#endif

#ifndef TRK8_ZERO_FLAG_INDEX
    #define TRK8_ZERO_FLAG_INDEX (2)
#endif

#ifndef TRK8_NEGATIVE_FLAG_INITIAL_VALUE
    #define TRK8_NEGATIVE_FLAG_INITIAL_VALUE (0b0)
#endif

#ifndef TRK8_CARRY_FLAG_INITIAL_VALUE
    #define TRK8_CARRY_FLAG_INITIAL_VALUE (0b0)
#endif

#ifndef TRK8_ZERO_FLAG_INITIAL_VALUE
    #define TRK8_ZERO_FLAG_INITIAL_VALUE (0b0)
#endif

#ifndef TRK8_NEGATIVE_VALUE_BIT
    #define TRK8_NEGATIVE_VALUE_BIT (7)
#endif

#ifndef TRK8_CARRY_VALUE_BIT
    #define TRK8_CARRY_VALUE_BIT (8)
#endif

#ifndef TRK8_STACK_POINTER_INITIAL_VALUE
    #define TRK8_STACK_POINTER_INITIAL_VALUE (0xff)
#endif

#ifndef TRK8_ADDRESS_REGISTER_LOW_BYTE_INITIAL_VALUE
    #define TRK8_ADDRESS_REGISTER_LOW_BYTE_INITIAL_VALUE (0x00)
#endif

#ifndef TRK8_ADDRESS_REGISTER_HIGH_BYTE_INITIAL_VALUE
    #define TRK8_ADDRESS_REGISTER_HIGH_BYTE_INITIAL_VALUE (0x81)
#endif

typedef struct _TRK8_REGISTERS {
    struct _REGISTERS_GENERAL_PURPOSE {
        uint8_t a, b, c, d;
    } general_purpose;

    uint8_t stack_pointer;

    struct _REGISTERS_ADDRESS {
        uint8_t low; // al
        uint8_t high; // ah
    } address;

    unsigned int flags : 4;
} trk8_registers_t;

typedef enum _TRK8_REGISTER_IDS {
    TRK8_REGISTER_GP_A,
    TRK8_REGISTER_GP_B,
    TRK8_REGISTER_GP_C,
    TRK8_REGISTER_GP_D,

    TRK8_REGISTER_SP,

    TRK8_REGISTER_ADDRESS_LOW,
    TRK8_REGISTER_ADDRESS_HIGH
} register_id_t;

void registers_init(trk8_registers_t* registers);

uint8_t registers_get(const trk8_registers_t registers, register_id_t register_id);
void registers_set(trk8_registers_t* registers, register_id_t register_id, uint8_t value);

void registers_update_flags(trk8_registers_t* registers, uint16_t value);

void registers_debug_print(const trk8_registers_t registers);

#endif
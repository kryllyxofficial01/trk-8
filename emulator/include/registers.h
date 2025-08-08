#ifndef __TRK8_REGISTERS_H
#define __TRK8_REGISTERS_H

#include <stdint.h>

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

#ifndef TRK8_STACK_POINTER_INITIAL_VALUE
    #define TRK8_STACK_POINTER_INITIAL_VALUE (0xff)
#endif

#ifndef TRK8_NEGATIVE_VALUE_BIT
    #define TRK8_NEGATIVE_VALUE_BIT (7)
#endif

#ifndef TRK8_CARRY_VALUE_BIT
    #define TRK8_CARRY_VALUE_BIT (8)
#endif

typedef unsigned char uint4_t;

typedef struct _TRK8_REGISTERS {
    struct _REGISTERS_GENERAL_PURPOSE {
        uint8_t a, b, c, d;
    } general_purpose;

    uint8_t stack_pointer;

    uint4_t flags; // TODO: maybe use bit field?
} registers_t;

typedef enum _TRK8_REGISTER_IDS {
    TRK8_REGISTER_GP_A,
    TRK8_REGISTER_GP_B,
    TRK8_REGISTER_GP_C,
    TRK8_REGISTER_GP_D,

    TRK8_REGISTER_SP
} register_id_t;

void registers_init(registers_t* registers);

uint8_t registers_get(const registers_t registers, register_id_t register_id);
void registers_set(registers_t* registers, register_id_t register_id, uint8_t value);

void registers_update_flags(registers_t* registers, uint16_t value);

void registers_debug_print(const registers_t registers);

#endif
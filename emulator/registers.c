#include "include/registers.h"

void registers_init(trk8_registers_t* registers) {
    registers->general_purpose.a = 0x0;
    registers->general_purpose.b = 0x0;
    registers->general_purpose.c = 0x0;
    registers->general_purpose.d = 0x0;

    registers->stack_pointer = TRK8_STACK_POINTER_INITIAL_VALUE;

    registers->address.low = TRK8_ADDRESS_REGISTER_LOW_BYTE_INITIAL_VALUE;
    registers->address.high = TRK8_ADDRESS_REGISTER_HIGH_BYTE_INITIAL_VALUE;

    registers->flags = 0b0000;
    registers->flags |= TRK8_NEGATIVE_FLAG_INITIAL_VALUE << TRK8_NEGATIVE_FLAG_INDEX;
    registers->flags |= TRK8_CARRY_FLAG_INITIAL_VALUE << TRK8_CARRY_FLAG_INDEX;
    registers->flags |= TRK8_ZERO_FLAG_INITIAL_VALUE << TRK8_ZERO_FLAG_INDEX;
}

uint8_t registers_get(const trk8_registers_t registers, register_id_t register_id) {
    switch (register_id) {
        case TRK8_REGISTER_GP_A: return registers.general_purpose.a;
        case TRK8_REGISTER_GP_B: return registers.general_purpose.b;
        case TRK8_REGISTER_GP_C: return registers.general_purpose.c;
        case TRK8_REGISTER_GP_D: return registers.general_purpose.d;

        case TRK8_REGISTER_SP: return registers.stack_pointer;

        case TRK8_REGISTER_ADDRESS_LOW: return registers.address.low;
        case TRK8_REGISTER_ADDRESS_HIGH: return registers.address.high;
    }
}

void registers_set(trk8_registers_t* registers, register_id_t register_id, uint8_t value) {
    switch (register_id) {
        case TRK8_REGISTER_GP_A: registers->general_purpose.a = value; break;
        case TRK8_REGISTER_GP_B: registers->general_purpose.b = value; break;
        case TRK8_REGISTER_GP_C: registers->general_purpose.c = value; break;
        case TRK8_REGISTER_GP_D: registers->general_purpose.d = value; break;

        case TRK8_REGISTER_ADDRESS_LOW: registers->address.low = value; break;
        case TRK8_REGISTER_ADDRESS_HIGH: registers->address.high = value; break;
    }
}

void registers_update_flags(trk8_registers_t* registers, uint16_t value) {
    if (TRK8_BIT_CHECK(value, TRK8_NEGATIVE_VALUE_BIT)) {
        TRK8_BIT_SET(registers->flags, TRK8_NEGATIVE_FLAG_INDEX);
    }
    else {
        TRK8_BIT_UNSET(registers->flags, TRK8_NEGATIVE_FLAG_INDEX);
    }

    if (TRK8_BIT_CHECK(value, TRK8_CARRY_VALUE_BIT)) {
        TRK8_BIT_SET(registers->flags, TRK8_CARRY_FLAG_INDEX);
    }
    else {
        TRK8_BIT_UNSET(registers->flags, TRK8_CARRY_FLAG_INDEX);
    }

    if (value == 0) {
        TRK8_BIT_SET(registers->flags, TRK8_ZERO_FLAG_INDEX);
    }
    else {
        TRK8_BIT_UNSET(registers->flags, TRK8_ZERO_FLAG_INDEX);
    }
}
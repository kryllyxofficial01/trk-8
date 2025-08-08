#include "include/registers.h"

void registers_init(registers_t* registers) {
    registers->general_purpose.a = 0x0;
    registers->general_purpose.b = 0x0;
    registers->general_purpose.c = 0x0;
    registers->general_purpose.d = 0x0;

    registers->stack_pointer = TRK8_STACK_POINTER_INITIAL_VALUE;

    registers->flags = 0x0;
    registers->flags |= TRK8_NEGATIVE_FLAG_INITIAL_VALUE << TRK8_NEGATIVE_FLAG_INDEX;
    registers->flags |= TRK8_CARRY_FLAG_INITIAL_VALUE << TRK8_CARRY_FLAG_INDEX;
    registers->flags |= TRK8_ZERO_FLAG_INITIAL_VALUE << TRK8_ZERO_FLAG_INDEX;
}

uint8_t registers_get(const registers_t registers, register_id_t register_id) {
    switch (register_id) {
        case TRK8_REGISTER_GP_A: return registers.general_purpose.a;
        case TRK8_REGISTER_GP_B: return registers.general_purpose.b;
        case TRK8_REGISTER_GP_C: return registers.general_purpose.c;
        case TRK8_REGISTER_GP_D: return registers.general_purpose.d;

        case TRK8_REGISTER_SP: return registers.stack_pointer;
    }
}

void registers_set(registers_t* registers, register_id_t register_id, uint8_t value) {
    switch (register_id) {
        case TRK8_REGISTER_GP_A: registers->general_purpose.a = value; break;
        case TRK8_REGISTER_GP_B: registers->general_purpose.b = value; break;
        case TRK8_REGISTER_GP_C: registers->general_purpose.c = value; break;
        case TRK8_REGISTER_GP_D: registers->general_purpose.d = value; break;
    }

    registers_update_flags(registers, value);
}

void registers_update_flags(registers_t* registers, uint16_t value) {
    if (TRK8_BIT_CHECK(value, TRK8_NEGATIVE_VALUE_BIT)) {
        TRK8_BIT_SET(registers->flags, TRK8_NEGATIVE_FLAG_INDEX);

        printf("test\n");
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

void registers_debug_print(const registers_t registers) {
    printf("Register Values:\n");

    printf("\tA: %u\n", registers.general_purpose.a);
    printf("\tB: %u\n", registers.general_purpose.b);
    printf("\tC: %u\n", registers.general_purpose.c);
    printf("\tD: %u\n", registers.general_purpose.d);

    printf("\tSP: %u\n", registers.stack_pointer);
    printf("\tF: 0x%x\n", registers.flags);
}
#include "include/registers.h"

trk8_registers_t registers_init(void) {
    trk8_registers_t registers;

    registers_set(&registers, TRK8_REGISTER_A, 0x00);
    registers_set(&registers, TRK8_REGISTER_B, 0x00);
    registers_set(&registers, TRK8_REGISTER_C, 0x00);
    registers_set(&registers, TRK8_REGISTER_X, 0x00);

    registers_set(&registers, TRK8_REGISTER_SP, 0x00);

    registers_set(&registers, TRK8_REGISTER_F, 0x00);

    registers_set(&registers, TRK8_REGISTER_AL, 0x00);
    registers_set(&registers, TRK8_REGISTER_AH, 0x00);

    registers_set(&registers, TRK8_REGISTER_PCL, 0x00);
    registers_set(&registers, TRK8_REGISTER_PCH, 0x00);

    return registers;
}

uint8_t registers_get(const trk8_registers_t registers, const trk8_register_id_t register_id) {
    uint8_t value;

    switch (register_id) {
        case TRK8_REGISTER_A: value = registers.a; break;
        case TRK8_REGISTER_B: value = registers.b; break;
        case TRK8_REGISTER_C: value = registers.c; break;
        case TRK8_REGISTER_X: value = registers.x; break;

        case TRK8_REGISTER_SP: value = registers.sp; break;

        case TRK8_REGISTER_F: value = registers.f; break;

        case TRK8_REGISTER_AL: value = registers.al; break;
        case TRK8_REGISTER_AH: value = registers.ah; break;

        case TRK8_REGISTER_PCL: value = registers.pcl; break;
        case TRK8_REGISTER_PCH: value = registers.pch; break;
    }

    return value;
}

void registers_set(trk8_registers_t* registers, const trk8_register_id_t register_id, const uint8_t value) {
    switch (register_id) {
        case TRK8_REGISTER_A: registers->a = value; break;
        case TRK8_REGISTER_B: registers->b = value; break;
        case TRK8_REGISTER_C: registers->c = value; break;
        case TRK8_REGISTER_X: registers->x = value; break;

        case TRK8_REGISTER_SP: registers->sp = value; break;

        case TRK8_REGISTER_F: registers->f = value & 0x0f; break; // only take low nibble

        case TRK8_REGISTER_AL: registers->al = value; break;
        case TRK8_REGISTER_AH: registers->ah = value; break;

        case TRK8_REGISTER_PCL: registers->pcl = value; break;
        case TRK8_REGISTER_PCH: registers->pch = value; break;
    }
}

uint16_t registers_get_pc_word(const trk8_registers_t registers) {
    return TRK8_MAKE_WORD(
        registers_get(registers, TRK8_REGISTER_PCL),
        registers_get(registers, TRK8_REGISTER_PCH)
    );
}

void registers_increment_pc(trk8_registers_t* registers, uint16_t amount) {
    uint16_t program_counter = registers_get_pc_word(*registers);

    program_counter += amount;

    registers_set(registers, TRK8_REGISTER_PCL, TRK8_GET_LOW_BYTE(program_counter));
    registers_set(registers, TRK8_REGISTER_PCH, TRK8_GET_HIGH_BYTE(program_counter));
}
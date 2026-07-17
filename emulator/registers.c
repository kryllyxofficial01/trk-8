#include "include/registers.h"

trk8_registers_t registers_init(void) {
    trk8_registers_t registers;

    registers_set(&registers, TRK8_REGISTER_A, 0x00);
    registers_set(&registers, TRK8_REGISTER_B, 0x00);
    registers_set(&registers, TRK8_REGISTER_C, 0x00);
    registers_set(&registers, TRK8_REGISTER_X, 0x00);
    
    registers_set(&registers, TRK8_REGISTER_SP, 0x00);
    
    registers_set(&registers, TRK8_REGISTER_F, 0x0);
    
    registers_set(&registers, TRK8_REGISTER_AL, 0x00);
    registers_set(&registers, TRK8_REGISTER_AH, 0x00);
    
    registers_set(&registers, TRK8_REGISTER_PCL, 0x00);
    registers_set(&registers, TRK8_REGISTER_PCH, 0x00);

    return registers;
}

uint8_t registers_get(const trk8_registers_t registers, const trk8_register_id_t register_id) {
    uint8_t value;

    switch (register_id) {
        case TRK8_REGISTER_A: value = registers.a;
        case TRK8_REGISTER_B: value = registers.b;
        case TRK8_REGISTER_C: value = registers.c;
        case TRK8_REGISTER_X: value = registers.x;

        case TRK8_REGISTER_SP: value = registers.sp;

        case TRK8_REGISTER_F: value = registers.f;

        case TRK8_REGISTER_AL: value = registers.al;
        case TRK8_REGISTER_AH: value = registers.ah;

        case TRK8_REGISTER_PCL: value = registers.pcl;
        case TRK8_REGISTER_PCH: value = registers.pch;
    }

    return value;
}

void registers_set(trk8_registers_t* registers, const trk8_register_id_t register_id, const uint8_t value) {
    switch (register_id) {
        case TRK8_REGISTER_A: registers->a = value;
        case TRK8_REGISTER_B: registers->b = value;
        case TRK8_REGISTER_C: registers->c = value;
        case TRK8_REGISTER_X: registers->x = value;

        case TRK8_REGISTER_SP: registers->sp = value;

        case TRK8_REGISTER_F: registers->f = value & 0xf; // only use low nibble

        case TRK8_REGISTER_AL: registers->al = value;
        case TRK8_REGISTER_AH: registers->ah = value;

        case TRK8_REGISTER_PCL: registers->pcl = value;
        case TRK8_REGISTER_PCH: registers->pch = value;
    }
}

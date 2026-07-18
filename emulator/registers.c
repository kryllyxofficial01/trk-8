#include "include/registers.h"

trk8_registers_t registers_init(void) {
    trk8_registers_t registers;

    registers.a = 0x00;
    registers.b = 0x00;
    registers.c = 0x00;
    registers.x = 0x00;

    registers.sp = 0x00;

    registers.f = 0x0;

    registers.al = registers.ah = 0x00;

    registers.pcl = registers.pch = 0x00;

    return registers;
}

uint16_t registers_get_pc_word(const trk8_registers_t registers) {
    return TRK8_MAKE_WORD(registers.pcl, registers.pch);
}

void registers_increment_pc(trk8_registers_t* registers, uint16_t amount) {
    uint16_t program_counter = registers_get_pc_word(*registers);

    program_counter += amount;

    registers->pcl = TRK8_GET_LOW_BYTE(program_counter);
    registers->pch = TRK8_GET_HIGH_BYTE(program_counter);
}
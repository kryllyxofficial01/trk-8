#include "include/cpu.h"

int main(void) {
    #define PROGRAM_LENGTH (6)

    uint8_t program[PROGRAM_LENGTH] = {
        0x14, 0x00, 0xff, // mov %a, 0xff
        0x44, 0x00, 0x01  // adc %a, 0x01 (should enable the carry flag)
    };

    trk8_machine_t machine;

    trk8_init(&machine);

    memory_write_program(machine.memory, program, PROGRAM_LENGTH);

    cpu_run(&machine);
}

#include "include/cpu.h"

int main(void) {
    uint8_t program[3] = {
        0x14, 0x00, 0x80 // mov %a, 0x80
    };

    trk8_machine_t machine;

    trk8_init(&machine);

    memory_write_program(machine.memory, program, 3);

    cpu_run(&machine);
}
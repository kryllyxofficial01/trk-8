#include <stdlib.h>

#include "include/machine.h"

int main(void) {
    uint8_t program[] = {
        0b00001100, 0b00010001, // mov %a, 17
        0b00101000,             // push %a
        0b00110010              // pop %c
    };

    uint16_t program_length = sizeof(program) / sizeof(uint8_t);

    trk8_machine_t machine = machine_init();

    memory_load_program(&machine.memory, program, program_length);

    machine_run(&machine);

    return EXIT_SUCCESS;
}

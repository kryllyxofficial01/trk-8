#include <stdlib.h>

#include "include/machine.h"

int main(void) {
    uint8_t program[] = {
        0b00001100, 0b00010011, // mov %a, 19
        0b00001101, 0b00000110  // mov %b, 6
    };

    uint16_t program_length = sizeof(program) / sizeof(uint8_t);

    trk8_machine_t machine = machine_init();

    memory_load_program(&machine.memory, program, program_length);

    machine_run(&machine);

    return EXIT_SUCCESS;
}

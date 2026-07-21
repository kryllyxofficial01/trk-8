#include <stdlib.h>

#include "include/machine.h"

int main(void) {
    uint8_t program[] = {
        0b00001100, 0b00000111, // mov %a, 7

        0b01100000,             // not
        0b00001000, 0b00000011, // mov %a, %x
        0b00001101, 0b00000001, // mov %b, 1
        0b01001000,             // adc
        0b00001001, 0b00000011, // mov %b, %x

        0b00001100, 0b00010011, // mov %a, 19

        0b01001000              // adc
    };

    uint16_t program_length = sizeof(program) / sizeof(uint8_t);

    trk8_machine_t machine = machine_init();

    memory_load_program(&machine.memory, program, program_length);

    machine_run(&machine);

    return EXIT_SUCCESS;
}

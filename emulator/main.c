#include <stdlib.h>

#include "include/machine.h"

int main(void) {
    uint8_t program[] = {
        0b10000001, 0b00001010, // mov %a, 10
        0b10000011, 0b00010100, // mov %b, 20
        0b00000010,             // adc
        0b01100011,             // push %x
        0b01110010,             // pop %c
        0b00001011              // hlt
    };

    uint16_t program_length = sizeof(program) / sizeof(uint8_t);

    trk8_machine_t machine = machine_init();

    memory_load_program(&machine.memory, program, program_length);

    machine_run(&machine);

    machine_print_state(machine.state);

    return EXIT_SUCCESS;
}

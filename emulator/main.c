#include <stdlib.h>

#include "include/machine.h"

int main(void) {
    uint8_t program[] = {
        0b00001100, 0b00010011, // mov %a, 19
        0b00001101, 0b00010001, // mov %b, 17
        0b00100000,             // xca
        0b10001100, 0b00000101, // stb 5
        0b10010010              // ldb %c
    };

    uint16_t program_length = sizeof(program) / sizeof(uint8_t);

    trk8_machine_t machine = machine_init();

    memory_load_program(&machine.memory, program, program_length);

    machine_run(&machine);

    printf("c: %u\n", registers_get(machine.state.registers, TRK8_REGISTER_C));

    return EXIT_SUCCESS;
}

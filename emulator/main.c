#include <stdlib.h>

#include "include/memory.h"

int main(void) {
    uint8_t program[] = {
        0b00001100, 0b00010011 // mov %a, 19
    };

    uint16_t program_length = sizeof(program) / sizeof(uint8_t);

    trk8_memory_t memory = memory_init();

    memory_load_program(&memory, program, program_length);

    memory_dump(memory, 0, program_length);

    return EXIT_SUCCESS;
}

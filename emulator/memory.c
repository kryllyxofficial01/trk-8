#include "include/memory.h"

void memory_init(trk8_memory_t* total_memory, uint8_t* program_memory, const uint16_t program_memory_length) {
    for (uint16_t i = 0; i < TRK8_PROGRAM_MEMORY_LENGTH; i++) {
        total_memory->program_memory[i] = 0x0;
    }

    for (uint16_t i = 0; i < TRK8_STACK_LENGTH; i++) {
        total_memory->stack[i] = 0x0;
    }

    if (program_memory_length > TRK8_PROGRAM_MEMORY_LENGTH) {
        // TODO: handle this somehow
    }

    for (uint16_t i = 0; i < program_memory_length; i++) {
        total_memory->program_memory[i] = program_memory[i];
    }

    // zero out whatever the program memory doesn't fill
    for (int i = TRK8_PROGRAM_MEMORY_LENGTH; i >= program_memory_length; i--) {
        total_memory->program_memory[i] = 0x0;
    }

    // signify where the program ends
    total_memory->program_memory[program_memory_length] = TRK8_PROGRAM_MEMORY_EOP_BYTE;

    // ensure we start where the program memory does
    total_memory->program_counter = TRK8_PROGRAM_MEMORY_START;
}
#include "include/memory.h"

trk8_memory_t memory_init(void) {
    trk8_memory_t memory;

    for (uint16_t i = 0; i < TRK8_PROGRAM_MEMORY_LENGTH; i++) {
        memory.program_memory[i] = 0x00;
    }

    for (uint16_t i = 0; i < TRK8_STACK_LENGTH; i++) {
        memory.stack[i] = 0x00;
    }

    for (uint16_t i = 0; i < TRK8_GENERAL_PURPOSE_LENGTH; i++) {
        memory.general_purpose[i] = 0x00;
    }

    return memory;
}

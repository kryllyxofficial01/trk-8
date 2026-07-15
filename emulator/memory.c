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

void memory_load_program(trk8_memory_t* memory, const uint8_t* program, const uint16_t program_length) {
    for (uint16_t i = 0; i < program_length; i++) {
        memory->program_memory[i] = program[i];
    }
}

uint8_t memory_read_byte(const trk8_memory_t memory, const uint16_t address) {
    if (address >= TRK8_PROGRAM_MEMORY_START && address <= TRK8_PROGRAM_MEMORY_END) {
        return memory.program_memory[address];
    }
    else if (address >= TRK8_STACK_START && address <= TRK8_STACK_END) {
        return memory.stack[address];
    }
    else if (address >= TRK8_GENERAL_PURPOSE_START && address <= TRK8_GENERAL_PURPOSE_END) {
        return memory.general_purpose[address];
    }

    return 0x00;
}

void memory_dump(const trk8_memory_t memory, const uint16_t start_address, const uint16_t end_address) {
    for (uint16_t i = start_address; i <= end_address; i++) {
        printf("[0x%02x]= 0x%02x\n", i, memory_read_byte(memory, i));
    }
}

#include "include/memory.h"

void memory_init(trk8_memory_t* total_memory, uint8_t* program_memory, const uint16_t program_memory_length) {
    for (uint16_t i = 0; i < TRK8_PROGRAM_MEMORY_LENGTH; i++) {
        total_memory->program_memory[i] = 0x0;
    }

    for (uint16_t i = 0; i < TRK8_STACK_LENGTH; i++) {
        total_memory->stack[i] = 0x0;
    }

    if (program_memory_length > TRK8_PROGRAM_MEMORY_LENGTH) {
        // TODO: handle oversized program memory
        return;
    }

    for (uint16_t i = 0; i < TRK8_PROGRAM_MEMORY_LENGTH; i++) {
        total_memory->program_memory[i] = (i < program_memory_length) ? program_memory[i] : 0x0;
    }

    if (program_memory_length <= TRK8_PROGRAM_MEMORY_LENGTH - 1) {
        total_memory->program_memory[program_memory_length] = TRK8_PROGRAM_MEMORY_EOP_BYTE;
    }

    total_memory->program_counter[0] = TRK8_GET_LOW_BYTE(TRK8_PROGRAM_MEMORY_START);
    total_memory->program_counter[1] = TRK8_GET_HIGH_BYTE(TRK8_PROGRAM_MEMORY_START);
}

uint8_t memory_fetch_byte(const trk8_memory_t memory, const uint16_t address) {
    if (address >= TRK8_PROGRAM_MEMORY_START && address <= TRK8_PROGRAM_MEMORY_END) {
        return memory.program_memory[address - TRK8_PROGRAM_MEMORY_START];
    }
    else if (address >= TRK8_STACK_START && address <= TRK8_STACK_END) {
        return memory.stack[address - TRK8_STACK_START];
    }
    else if (address >= TRK8_GENERAL_PURPOSE_MEMORY_START && address <= TRK8_GENERAL_PURPOSE_MEMORY_END) {
        return memory.general_purpose[address - TRK8_GENERAL_PURPOSE_MEMORY_START];
    }
    else if (address >= TRK8_PROGRAM_COUNTER_START && address <= TRK8_PROGRAM_COUNTER_END) {
        return memory.program_counter[TRK8_PROGRAM_COUNTER_START - address];
    }
    else {
        // TODO: handle out of range memory address
    }
}

void memory_write_byte(trk8_memory_t* memory, const uint16_t address, const uint8_t data) {
    if (address >= TRK8_PROGRAM_MEMORY_START && address <= TRK8_PROGRAM_MEMORY_END) {
        memory->program_memory[address - TRK8_PROGRAM_MEMORY_START] = data;
    }
    else if (address >= TRK8_STACK_START && address <= TRK8_STACK_END) {
        memory->stack[address - TRK8_STACK_START] = data;
    }
    else if (address >= TRK8_GENERAL_PURPOSE_MEMORY_START && address <= TRK8_GENERAL_PURPOSE_MEMORY_END) {
        memory->general_purpose[address - TRK8_GENERAL_PURPOSE_MEMORY_START] = data;
    }
    else if (address >= TRK8_PROGRAM_COUNTER_START && address <= TRK8_PROGRAM_COUNTER_END) {
        memory->stack[address - TRK8_PROGRAM_COUNTER_START] = data;
    }
    else {
        // TODO: handle out of range memory address
    }
}

void memory_set_program_counter(trk8_memory_t* memory, const uint16_t address) {
    memory->program_counter[0] = TRK8_GET_LOW_BYTE(address);
    memory->program_counter[1] = TRK8_GET_HIGH_BYTE(address);
}

void memory_increment_program_counter(trk8_memory_t* memory, const uint8_t amount) {
    uint16_t new_pc_value = TRK8_WORD(
        memory->program_counter[1],
        memory->program_counter[0]
    );

    new_pc_value += amount;

    memory_set_program_counter(memory, new_pc_value);
}

uint16_t memory_get_program_counter(const trk8_memory_t memory) {
    return TRK8_WORD(
        memory.program_counter[1],
        memory.program_counter[0]
    );
}
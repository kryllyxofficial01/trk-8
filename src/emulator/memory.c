#include "include/memory.h"

void mem_init(uint8_t* memory) {
    for (int i; i < MAX_MEM_SIZE; i++) {
        memory[i] = 0;
    }
}

uint8_t mem_fetch(uint8_t* memory, uint16_t address) {
    return memory[address];
}

void mem_store(uint8_t* memory, uint16_t address, uint8_t data) {
    memory[address] = data;
}
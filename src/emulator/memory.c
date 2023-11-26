#include "include/memory.h"

#include <stdio.h>

void mem_init(uint8_t* memory, char** binary) {
    for (int i = 0; i < MAX_MEM_SIZE; i++) {
        memory[i] = 0;
    }

    int i = 0;
    while (binary[i] != NULL) {
        memory[i] = strtol(binary[i], NULL, 2);

        i++;
    }
}

uint8_t mem_fetch(uint8_t* memory, uint16_t address) {
    return memory[address];
}

void mem_store(uint8_t* memory, uint16_t address, uint8_t data) {
    memory[address] = data;
}
#include "include/memory.h"

void mem_init(uint8_t* memory, const char* binary) {
    for (int i = 0; i < MAX_MEM_SIZE; i++) {
        memory[i] = 0;
    }

    char* bin = strtok(binary, "\n");
    int bin_idx = 0;
    while (bin != NULL) {
        memory[bin_idx++] = strtol(bin, NULL, 2);
        bin = strtok(NULL, "\n");
    }
}

uint8_t mem_fetch(uint8_t* memory, uint16_t address) {
    return memory[address];
}

void mem_store(uint8_t* memory, uint16_t address, uint8_t data) {
    memory[address] = data;
}
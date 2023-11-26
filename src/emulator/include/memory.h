#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEM_SIZE UINT16_MAX

#define PRGM_MEM_END 0x7fff
#define STACK_OFFSET 0x8000

#define PC_HIGH 0xfffe
#define PC_LOW 0xffff

void mem_init(uint8_t* memory, char** binary);
uint8_t mem_fetch(uint8_t* memory, uint16_t address);
void mem_store(uint8_t* memory, uint16_t address, uint8_t data);

#endif
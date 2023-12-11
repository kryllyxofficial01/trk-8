#ifndef __REGISTERS_H
#define __REGISTERS_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "memory.h"

#define ZERO_FLAG_OFFSET 7
#define CARRY_FLAG_OFFSET 6
#define NEGATIVE_FLAG_OFFSET 5

typedef struct REGISTERS {
    struct {
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
    } general_purpose;

    uint8_t stack_pointer;
    uint8_t flags;
} registers_t;

enum registers {
    REGA, REGB, REGC, REGD, REGSP, REGF
};

void reset_registers(registers_t* registers);

uint8_t get_register(registers_t* registers, uint8_t id);
void update_register(registers_t* registers, uint8_t id, uint8_t value);

uint16_t get_pc(uint8_t* memory);
void update_pc(uint8_t* memory, uint16_t program_counter);

void stack_push(registers_t* registers, uint8_t* memory, uint8_t value);
uint8_t stack_pop(registers_t* registers, uint8_t* memory);

void update_flags(registers_t* registers, int value);

#endif
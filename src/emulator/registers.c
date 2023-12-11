#include "include/registers.h"

void reset_registers(registers_t* registers) {
    registers->general_purpose.a = 0;
    registers->general_purpose.b = 0;
    registers->general_purpose.c = 0;
    registers->general_purpose.d = 0;

    registers->stack_pointer = 0xff;
    registers->flags = 0;
}

uint8_t get_register(registers_t* registers, uint8_t id) {
    switch (id) {
        case REGA: return registers->general_purpose.a; break;
        case REGB: return registers->general_purpose.b; break;
        case REGC: return registers->general_purpose.c; break;
        case REGD: return registers->general_purpose.d; break;
        case REGSP: return registers->stack_pointer; break;
        case REGF: return registers->flags; break;
    }
}

void update_register(registers_t* registers, uint8_t id, uint8_t value) {
    switch (id) {
        case REGA: registers->general_purpose.a = value; break;
        case REGB: registers->general_purpose.b = value; break;
        case REGC: registers->general_purpose.c = value; break;
        case REGD: registers->general_purpose.d = value; break;
        case REGSP: registers->stack_pointer = value; break;
        case REGF: registers->flags = value; break;
    }
}

uint16_t get_pc(uint8_t* memory) {
    return mem_fetch(memory, PC_LOW) | (
        mem_fetch(memory, PC_HIGH) << 8
    );
}

void update_pc(uint8_t* memory, uint16_t program_counter) {
    mem_store(memory, PC_HIGH, program_counter >> 8);
    mem_store(memory, PC_LOW, program_counter & 0xff);
}

void stack_push(registers_t* registers, uint8_t* memory, uint8_t value) {
    mem_store(memory, STACK_OFFSET+(registers->stack_pointer--), value);
}

uint8_t stack_pop(registers_t* registers, uint8_t* memory) {
    return mem_fetch(memory, STACK_OFFSET+(++registers->stack_pointer));
}

void update_flags(registers_t* registers, int value) {
    if (value == 0) {
        registers->flags |= 1 << ZERO_FLAG_OFFSET;
    }
    else {
        registers->flags &= ~(1 << ZERO_FLAG_OFFSET);
    }

    if (value > UINT8_MAX) {
        registers->flags |= 1 << CARRY_FLAG_OFFSET;
    }
    else {
        registers->flags &= ~(1 << CARRY_FLAG_OFFSET);
    }

    if (value < 0) {
        registers->flags |= 1 << NEGATIVE_FLAG_OFFSET;
    }
    else {
        registers->flags &= ~(1 << NEGATIVE_FLAG_OFFSET);
    }
}

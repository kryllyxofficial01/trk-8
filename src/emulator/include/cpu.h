#ifndef __CPU_H
#define __CPU_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "registers.h"
#include "memory.h"

enum instructions {
    NOP,
    MOV_REG, MOV_IMM,
    STB_REG, STB_IMM,
    LDB_REG, LDB_IMM,
    PUSH_REG, PUSH_IMM,
    POP,
    ADD_REG, ADD_IMM,
    SUB_REG, SUB_IMM,
    MUL_REG, MUL_IMM,
    DIV_REG, DIV_IMM,
    AND_REG, AND_IMM,
    OR_REG, OR_IMM,
    NOT,
    XOR_REG, XOR_IMM,
    CMP_REG, CMP_IMM,
    JMP, JZ, JC, JN,
    HLT,
    ASM_EOF = 255
};

void cpu_run_program(registers_t* registers, uint8_t* memory);

void cpu_mov(registers_t* registers, uint8_t* memory, uint8_t variant);

void cpu_stb(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_ldb(registers_t* registers, uint8_t* memory, uint8_t variant);

void cpu_push(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_pop(registers_t* registers, uint8_t* memory);

void cpu_add(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_sub(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_mul(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_div(registers_t* registers, uint8_t* memory, uint8_t variant);

void cpu_and(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_or(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_not(registers_t* registers, uint8_t* memory);
void cpu_xor(registers_t* registers, uint8_t* memory, uint8_t variant);

void cpu_cmp(registers_t* registers, uint8_t* memory, uint8_t variant);
void cpu_jmp(registers_t* registers, uint8_t* memory);
void cpu_jz(registers_t* registers, uint8_t* memory);
void cpu_jc(registers_t* registers, uint8_t* memory);
void cpu_jn(registers_t* registers, uint8_t* memory);

void cpu_hlt();

#endif
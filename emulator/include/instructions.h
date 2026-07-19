#ifndef __TRK8_INSTRUCTIONS_H
#define __TRK8_INSTRUCTIONS_H

#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "memory.h"
#include "opcode.h"

#ifndef TRK8_INSTRUCTION_DECL
    #define TRK8_INSTRUCTION_DECL(_mnemonic, ...) void instruction_##_mnemonic(__VA_ARGS__)
#endif

#ifndef TRK8_INSTRUCTIONS
    #define TRK8_INSTRUCTIONS(_decl, ...) \
        _decl(nop, __VA_ARGS__); \
        _decl(mov, __VA_ARGS__); \
        _decl(xsp, __VA_ARGS__); \
        _decl(xcf, __VA_ARGS__); \
        _decl(xca, __VA_ARGS__); \
        _decl(stb, __VA_ARGS__); \
        _decl(ldb, __VA_ARGS__); \
        _decl(push, __VA_ARGS__); \
        _decl(pop, __VA_ARGS__); \
        _decl(adc, __VA_ARGS__); \
        _decl(and, __VA_ARGS__); \
        _decl(or, __VA_ARGS__); \
        _decl(not, __VA_ARGS__); \
        _decl(cmp, __VA_ARGS__); \
        _decl(jmp, __VA_ARGS__); \
        _decl(bne, __VA_ARGS__); \
        _decl(bca, __VA_ARGS__); \
        _decl(bze, __VA_ARGS__); \
        _decl(hlt, __VA_ARGS__)
#endif

void execute_data_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode);
void execute_arithmetic_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode);
void execute_memory_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode);
void execute_misc_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode);

TRK8_INSTRUCTIONS(
    TRK8_INSTRUCTION_DECL,

    trk8_registers_t* registers,
    trk8_memory_t* memory,
    bool has_immediate,
    const trk8_register_id_t first_register_id
);

#endif
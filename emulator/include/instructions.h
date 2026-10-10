#ifndef __TRK8_INSTRUCTIONS_H
#define __TRK8_INSTRUCTIONS_H

#include <stdint.h>
#include <stdbool.h>

#include "registers.h"
#include "memory.h"
#include "opcode.h"

#ifndef TRK8_EXECUTE_OPCODE_CATEGORY_DECL
    #define TRK8_EXECUTE_OPCODE_CATEGORY_DECL(_category, ...) void execute_##_category##_opcode(__VA_ARGS__)
#endif

#ifndef TRK8_INSTRUCTION_DECL
    #define TRK8_INSTRUCTION_DECL(_mnemonic, ...) void instruction_##_mnemonic(__VA_ARGS__)
#endif

#ifndef TRK8_EXECUTE_OPCODE_CATEGORIES
    #define TRK8_EXECUTE_OPCODE_CATEGORIES(_decl, ...) \
        _decl(no_operands, __VA_ARGS__); \
        _decl(one_operand, __VA_ARGS__); \
        _decl(two_operands, __VA_ARGS__); \
        _decl(has_16bit_operand, __VA_ARGS__)
#endif

#ifndef TRK8_INSTRUCTIONS_NO_OPERANDS
    #define TRK8_INSTRUCTIONS_NO_OPERANDS(_decl, ...) \
        _decl(nop, __VA_ARGS__); \
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

#ifndef TRK8_INSTRUCTIONS_ONE_OPERAND
    #define TRK8_INSTRUCTIONS_ONE_OPERAND(_decl, ...) \
        _decl(stb, __VA_ARGS__); \
        _decl(ldb, __VA_ARGS__); \
        _decl(push, __VA_ARGS__); \
        _decl(pop, __VA_ARGS__)
#endif

#ifndef TRK8_INSTRUCTIONS_TWO_OPERANDS
    #define TRK8_INSTRUCTIONS_TWO_OPERANDS(_decl, ...) \
        _decl(mov, __VA_ARGS__)
#endif

#ifndef TRK8_INSTRUCTIONS_HAS_16BIT_OPERAND
    #define TRK8_INSTRUCTIONS_HAS_16BIT_OPERAND(_decl, ...) \
        _decl(lda, __VA_ARGS__)
#endif

TRK8_EXECUTE_OPCODE_CATEGORIES(
    TRK8_EXECUTE_OPCODE_CATEGORY_DECL,

    trk8_registers_t* registers,
    trk8_memory_t* memory,
    const trk8_opcode_t opcode
);

TRK8_INSTRUCTIONS_NO_OPERANDS(
    TRK8_INSTRUCTION_DECL,

    trk8_registers_t* registers,
    trk8_memory_t* memory
);

TRK8_INSTRUCTIONS_ONE_OPERAND(
    TRK8_INSTRUCTION_DECL,

    trk8_registers_t* registers,
    trk8_memory_t* memory,
    const trk8_register_id_t register_id,
    const bool has_immediate_operand
);

TRK8_INSTRUCTIONS_TWO_OPERANDS(
    TRK8_INSTRUCTION_DECL,

    trk8_registers_t* registers,
    trk8_memory_t* memory,
    const trk8_register_id_t destination_register_id,
    const bool has_immediate_operand
);

TRK8_INSTRUCTIONS_HAS_16BIT_OPERAND(
    TRK8_INSTRUCTION_DECL,

    trk8_registers_t* registers,
    trk8_memory_t* memory
);

#endif
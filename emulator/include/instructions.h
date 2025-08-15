#ifndef __TRK8_INSTRUCTIONS_H
#define __TRK8_INSTRUCTIONS_H

#include "trk8.h"
#include "utils.h"

#ifndef TRK8_DECLARE_INSTRUCTION
    #define TRK8_DECLARE_INSTRUCTION(_instruction) \
        void trk8_##_instruction(trk8_machine_t* machine, uint8_t operands_type)
#endif

#ifndef TRK8_INSTRUCTIONS
    #define TRK8_INSTRUCTIONS(_decl) \
        _decl(nop); \
        _decl(mov); \
        _decl(lda); \
        _decl(stb); \
        _decl(ldb); \
        _decl(push); \
        _decl(pop); \
        _decl(add); \
        _decl(and); \
        _decl(or); \
        _decl(not); \
        _decl(cmp); \
        _decl(jmp); \
        _decl(jn); \
        _decl(jc); \
        _decl(jz); \
        _decl(hlt);
#endif

enum _TRK8_INSTRUCTION_INDEXES {
    TRK8_INSTRUCTION_NOP = 1, // tell C to start counting at 1 (because yes)
    TRK8_INSTRUCTION_MOV,
    TRK8_INSTRUCTION_LDA,
    TRK8_INSTRUCTION_STB,
    TRK8_INSTRUCTION_LDB,
    TRK8_INSTRUCTION_PUSH,
    TRK8_INSTRUCTION_POP,
    TRK8_INSTRUCTION_ADD,
    TRK8_INSTRUCTION_AND,
    TRK8_INSTRUCTION_OR,
    TRK8_INSTRUCTION_NOT,
    TRK8_INSTRUCTION_CMP,
    TRK8_INSTRUCTION_JMP,
    TRK8_INSTRUCTION_JN,
    TRK8_INSTRUCTION_JC,
    TRK8_INSTRUCTION_JZ,
    TRK8_INSTRUCTION_HLT
};

enum _TRK8_OPERANDS_TYPES {
    TRK8_OPERANDS_TYPE_NONE,
    TRK8_OPERANDS_TYPE_IMM8,
    TRK8_OPERANDS_TYPE_IMM16,
    TRK8_OPERANDS_TYPE_REGISTER,
    TRK8_OPERANDS_TYPE_REG_IMM8,
    TRK8_OPERANDS_TYPE_REG_IMM16,
    TRK8_OPERANDS_TYPE_REG_REG
};

TRK8_INSTRUCTIONS(TRK8_DECLARE_INSTRUCTION)

#endif
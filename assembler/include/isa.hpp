#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

enum class OperandType {
    OP_NONE,
    OP_REGISTER,
    OP_IMM8,
    OP_IMM16
};

struct InstructionEncoding {
    std::string mnemonic;
    uint8_t opcode;
    std::vector<OperandType> operands;
};

static inline const std::vector<InstructionEncoding> INSTRUCTIONS = {
    { "nop",  0x08, {} },
    
    { "mov",  0x14, { OperandType::OP_REGISTER, OperandType::OP_IMM8 } },
    { "mov",  0x16, { OperandType::OP_REGISTER, OperandType::OP_REGISTER } },

    { "lda",  0x1a, { OperandType::OP_IMM16 } },

    { "stb",  0x21, { OperandType::OP_IMM8 } },
    { "stb",  0x23, { OperandType::OP_REGISTER } },

    { "ldb",  0x2b, { OperandType::OP_REGISTER } },

    { "push", 0x31, { OperandType::OP_IMM8 } },
    { "push", 0x33, { OperandType::OP_REGISTER } },

    { "pop",  0x3b, { OperandType::OP_REGISTER } },

    { "add",  0x44, { OperandType::OP_REGISTER, OperandType::OP_IMM8 } },
    { "add",  0x46, { OperandType::OP_REGISTER, OperandType::OP_REGISTER } },

    { "and",  0x4c, { OperandType::OP_REGISTER, OperandType::OP_IMM8 } },
    { "and",  0x4e, { OperandType::OP_REGISTER, OperandType::OP_REGISTER } },

    { "or",   0x54, { OperandType::OP_REGISTER, OperandType::OP_IMM8 } },
    { "or",   0x56, { OperandType::OP_REGISTER, OperandType::OP_REGISTER } },

    { "not",  0x5b, { OperandType::OP_REGISTER } },

    { "cmp",  0x64, { OperandType::OP_REGISTER, OperandType::OP_IMM8 } },
    { "cmp",  0x66, { OperandType::OP_REGISTER, OperandType::OP_REGISTER } },

    { "jmp",  0x68, {} },

    { "jn",   0x70, {} },
    
    { "jc",   0x78, {} },

    { "jz",   0x80, {} },

    { "hlt",  0x88, {} },
};

static inline const std::unordered_map<std::string, uint8_t> REGISTERS = {
    { "a", 0x0 },
    { "b", 0x1 },
    { "c", 0x2 },
    { "d", 0x3 },

    { "sp", 0x4 },

    { "al", 0x5 },
    { "ah", 0x6 }
};

#ifndef __ASSEMBLER_H
#define __ASSEMBLER_H

#include "map.h"

#define PNEUMONICS (const char*[]) { \
    "nop", \
    "mov_reg", "mov_imm", \
    "stb_reg", "stb_imm", \
    "ldb_reg", "ldb_imm", \
    "push_reg", "push_imm", \
    "pop", \
    "add_reg", "add_imm", \
    "sub_reg", "sub_imm", \
    "mul_reg", "mul_imm", \
    "div_reg", "div_imm", \
    "and_reg", "and_imm", \
    "or_reg", "or_imm", \
    "not", \
    "xor_reg", "xor_imm", \
    "cmp_reg", "cmp_imm", \
    "jmp", "jz", "jc", "jn", \
    "hlt", NULL \
} \

map_t* assembler_get_opcodes();

#endif
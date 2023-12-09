#ifndef __ASSEMBLER_H
#define __ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "utils.h"
#include "map.h"

#define MNEMONICS (const char*[]) { \
    "nop", \
    "mov_reg", "mov_imm", \
    "lda_reg", "lda_imm", \
    "stb", \
    "ldb", \
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
}

#define REGISTERS (const char*[]) { \
    "a", "b", "c", "d", "sp", "f", NULL \
}

#define HAS_VARIANTS (const char*[]) { \
    "mov", "lda", "ldb", "push", \
    "add", "sub", "mul", "div", \
    "and", "or", "xor", "cmp", NULL \
}

char* assembler_assemble(token_t* tokens);

map_t* assembler_get_opcodes();
map_t* assembler_get_register_ids();
map_t* assembler_get_variant_offsets();

#endif
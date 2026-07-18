#ifndef __TRK8_INSTRUCTIONS_H
#define __TRK8_INSTRUCTIONS_H

#include <stdint.h>
#include <stdbool.h>

#include "registers.h"

typedef enum _TRK8_INSTRUCTION_CATEGORY {
    TRK8_INST_CAT_DATA,
    TRK8_INST_CAT_ARITHMETIC,
    TRK8_INST_CAT_MEMORY,
    TRK8_INST_CAT_MISC
} trk8_inst_cat_t;

typedef enum _TRK8_DATA_INSTRUCTION_ID {
    TRK8_DATA_INST_MOV = 1,
    TRK8_DATA_INST_XSP,
    TRK8_DATA_INST_XCF,
    TRK8_DATA_INST_XCA,
    TRK8_DATA_INST_PUSH,
    TRK8_DATA_INST_POP
} trk8_data_inst_id_t;

typedef enum _TRK8_ARITHMETIC_INSTRUCTION_ID {
    TRK8_ARITH_INST_ADC = 1,
    TRK8_ARITH_INST_AND,
    TRK8_ARITH_INST_OR,
    TRK8_ARITH_INST_NOT,
    TRK8_ARITH_INST_CMP
} trk8_arith_inst_id_t;

typedef enum _TRK8_MEMORY_INSTRUCTION_ID {
    TRK8_MEMORY_INST_STB = 1,
    TRK8_MEMORY_INST_LDB,
    TRK8_MEMORY_INST_JMP,
    TRK8_MEMORY_INST_BNE,
    TRK8_MEMORY_INST_BCA,
    TRK8_MEMORY_INST_BZE
} trk8_memory_inst_id_t;

typedef enum _TRK8_MISC_INSTRUCTION_ID {
    TRK8_MISC_INST_NOP = 1,
    TRK8_MISC_INST_HLT
} trk8_misc_inst_id_t;

typedef struct _TRK8_OPCODE {
    trk8_inst_cat_t category;

    union _OPCODE_INSTRUCTRION_ID {
        trk8_data_inst_id_t data_id;
        trk8_arith_inst_id_t arithmetic_id;
        trk8_memory_inst_id_t memory_id;
        trk8_misc_inst_id_t misc_id;
    } instruction_id;

    bool has_immediate;

    trk8_register_id_t first_register_id;
} trk8_opcode_t;

trk8_opcode_t parse_opcode(uint8_t opcode);

#endif
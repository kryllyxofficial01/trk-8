#ifndef __TRK8_OPCODE_H
#define __TRK8_OPCODE_H

#include "registers.h"

typedef enum _TRK8_OPCODE_CATEGORY {
    TRK8_OPCODE_CATEGORY_NO_OPERANDS,
    TRK8_OPCODE_CATEGORY_ONE_OPERAND,
    TRK8_OPCODE_CATEGORY_TWO_OPERANDS
} trk8_opc_category_t;

typedef enum _TRK8_OPCODE_ARGUMENTS_NO_OPERANDS_INSTRUCTION_ID {
    TRK8_INSTRUCTION_ID_NOP = 1,
    TRK8_INSTRUCTION_ID_ADC,
    TRK8_INSTRUCTION_ID_AND,
    TRK8_INSTRUCTION_ID_OR,
    TRK8_INSTRUCTION_ID_NOT,
    TRK8_INSTRUCTION_ID_CMP,
    TRK8_INSTRUCTION_ID_JMP,
    TRK8_INSTRUCTION_ID_BNE,
    TRK8_INSTRUCTION_ID_BCA,
    TRK8_INSTRUCTION_ID_BZE,
    TRK8_INSTRUCTION_ID_HLT
} trk8_opc_args_no_operands_inst_id_t;

typedef enum _TRK8_OPCODE_ARGUMENTS_ONE_OPERAND_INSTRUCTION_ID {
    TRK8_INSTRUCTION_ID_STB,
    TRK8_INSTRUCTION_ID_LDB,
    TRK8_INSTRUCTION_ID_PUSH,
    TRK8_INSTRUCTION_ID_POP
} trk8_opc_args_one_operand_inst_id_t;

typedef enum _TRK8_OPCODE_ARGUMENTS_TWO_OPERANDS_INSTRUCTION_ID {
    TRK8_INSTRUCTION_ID_MOV
} trk8_opc_args_two_operands_inst_id_t;

typedef struct _TRK8_OPCODE_ARGUMENTS_NO_OPERANDS {
    trk8_opc_args_no_operands_inst_id_t instruction_id;
} trk8_opc_args_no_operands_t;

typedef struct _TRK8_OPCODE_ARGUMENTS_ONE_OPERAND {
    trk8_opc_args_one_operand_inst_id_t instruction_id;

    trk8_register_id_t register_id;

    bool has_immediate;
} trk8_opc_args_one_operand_t;

typedef struct _TRK8_OPCODE_ARGUMENTS_TWO_OPERANDS {
    trk8_opc_args_two_operands_inst_id_t instruction_id;

    trk8_register_id_t destination_register_id;

    bool has_immediate;

    union _TRK8_OPCODE_ARGUMENT_SOURCE {
        trk8_register_id_t source_register_id;

        uint8_t immediate;
    } source;
} trk8_opc_args_two_operands_t;

typedef struct _TRK8_OPCODE {
    trk8_opc_category_t category;

    union _TRK8_OPCODE_ARGUMENTS {
        trk8_opc_args_no_operands_t no_operands;
        trk8_opc_args_one_operand_t one_operand;
        trk8_opc_args_two_operands_t two_operands;
    } arguments;
} trk8_opcode_t;

#endif
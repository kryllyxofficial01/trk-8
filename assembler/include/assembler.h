#ifndef __TRK8_ASSEMBLER_H
#define __TRK8_ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "asm_line.h"
#include "utils.h"

#ifndef TRK8_INSTRUCTIONS_COUNT
    #define TRK8_INSTRUCTIONS_COUNT (17)
#endif

#ifndef TRK8_REGISTERS_COUNT
    #define TRK8_REGISTERS_COUNT (10)
#endif

#ifndef TRK8_INSTRUCTIONS_MAX_BYTE_COUNT
    #define TRK8_INSTRUCTIONS_MAX_BYTE_COUNT (3)
#endif

#ifndef TRK8_ONE_OPERAND_INSTRUCTION_HAS_IMMEDIATE
    #define TRK8_ONE_OPERAND_INSTRUCTION_HAS_IMMEDIATE (0b1111)
#endif

#ifndef TRK8_PADDING_BYTE
    #define TRK8_PADDING_BYTE (0b00000001)
#endif

typedef enum _TRK8_INSTRUCTION_CATEGORY {
    TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS,
    TRK8_INSTRUCTION_CATEGORY_ONE_OPERAND,
    TRK8_INSTRUCTION_CATEGORY_TWO_OPERANDS,
    TRK8_INSTRUCTION_CATEGORY_HAS_16BIT_OPERAND
} trk8_instruction_category_t;

typedef struct _TRK8_INSTRUCTION_INFO {
    char* mnemonic;

    uint8_t byte_count;

    trk8_instruction_category_t category;
    uint8_t category_internal_index;
} trk8_instruction_info_t;

typedef enum _TRK8_OPERAND_TYPE {
    TRK8_OPERAND_TYPE_REGISTER,
    TRK8_OPERAND_TYPE_IMM8,
    TRK8_OPERAND_TYPE_IMM16,
    TRK8_OPERAND_TYPE_LABEL
} trk8_operand_type_t;

typedef struct _TRK8_REGISTER_INDEX {
    char* symbolic_name;

    uint8_t index;
} trk8_register_index_t;

typedef struct _TRK8_IMMEDIATE_REPRESENTATION_LINE {
    uint16_t address;

    uint8_t byte_count;

    trk8_assembly_line_t* source;
} trk8_ir_line_t;

typedef struct _TRK8_SYMBOL_TABLE_ENTRY {
    char* name;

    uint16_t address;
} trk8_symbol_t;

typedef struct _TRK8_PASS1_RESULT {
    trk8_ir_line_t* ir_lines;
    uint16_t ir_line_count;

    trk8_symbol_t* symbol_table;
    uint16_t symbol_table_length;
} trk8_pass1_result_t;

bool assembler_run_pass1(trk8_assembly_line_t* lines, const uint16_t line_count, const uint16_t origin_address, trk8_pass1_result_t* pass1_result);
bool assembler_run_pass2(trk8_pass1_result_t* pass1_result, uint8_t** output, uint16_t* output_byte_count);

void assembler_free_pass1_result(trk8_pass1_result_t* pass1_result);

#endif
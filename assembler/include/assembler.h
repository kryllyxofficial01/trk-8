#ifndef __TRK8_ASSEMBLER_H
#define __TRK8_ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "asm_line.h"
#include "utils.h"

#ifndef TRK8_INSTRUCTIONS_COUNT
    #define TRK8_INSTRUCTIONS_COUNT (17)
#endif

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

typedef struct _TRK8_INSTRUCTION_BYTE_INFO {
    char* mnemonic;

    uint8_t byte_count;
} trk8_instruction_byte_info_t;

bool assembler_run_pass1(trk8_assembly_line_t* lines, const uint16_t line_count, const uint16_t origin_address, trk8_pass1_result_t* pass1_result);

void assembler_free_pass1_result(trk8_pass1_result_t* pass1_result);

#endif
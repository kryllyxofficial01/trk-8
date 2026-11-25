#ifndef __TRK8_PARSER_H
#define __TRK8_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

#include "utils.h"

#ifndef TRK8_INSTRUCTION_MAX_LENGTH
    #define TRK8_INSTRUCTION_MAX_LENGTH (1 << 10)
#endif

#ifndef TRK8_INSTRUCTION_MAX_OPERANDS
    #define TRK8_INSTRUCTION_MAX_OPERANDS (2)
#endif

#ifndef TRK8_MAX_BUFFER_LENGTH
    #define TRK8_MAX_BUFFER_LENGTH (1024)
#endif

typedef struct _TRK8_ASSEMBLY_LINE {
    char* mnemonic;

    char* operands[TRK8_INSTRUCTION_MAX_OPERANDS];
    uint8_t operand_count;
} trk8_assembly_line_t;

bool parser_parse_file(const char* filepath, trk8_assembly_line_t** lines, uint16_t* line_count);

#endif
#ifndef __TRK8_ASM_LINE_H
#define __TRK8_ASM_LINE_H

#include <stdint.h>

#ifndef TRK8_INSTRUCTION_MAX_OPERANDS
    #define TRK8_INSTRUCTION_MAX_OPERANDS (2)
#endif

typedef struct _TRK8_ASSEMBLY_LINE {
    char* mnemonic;

    char* operands[TRK8_INSTRUCTION_MAX_OPERANDS];
    uint8_t operand_count;

    uint16_t line_number;
} trk8_assembly_line_t;

#endif
#ifndef __TRK8_MEMORY_H
#define __TRK8_MEMORY_H

#include "utils.h"

#ifndef TRK8_PROGRAM_MEMORY_START
    #define TRK8_PROGRAM_MEMORY_START (0x0)
#endif

#ifndef TRK8_PROGRAM_MEMORY_END
    #define TRK8_PROGRAM_MEMORY_END (0x7fff)
#endif

#ifndef TRK8_STACK_START
    #define TRK8_STACK_START (0x8000)
#endif

#ifndef TRK8_STACK_END
    #define TRK8_STACK_END (0x80ff)
#endif

#ifndef TRK8_GENERAL_PURPOSE_MEMORY_START
    #define TRK8_GENERAL_PURPOSE_MEMORY_START (0x8100)
#endif

#ifndef TRK8_GENERAL_PURPOSE_MEMORY_END
    #define TRK8_GENERAL_PURPOSE_MEMORY_END (0xfffd)
#endif

#ifndef TRK8_PROGRAM_COUNTER_START
    #define TRK8_PROGRAM_COUNTER_START (0xfffe)
#endif

#ifndef TRK8_PROGRAM_COUNTER_END
    #define TRK8_PROGRAM_COUNTER_END (0xffff)
#endif

#ifndef TRK8_PROGRAM_MEMORY_LENGTH
    #define TRK8_PROGRAM_MEMORY_LENGTH ((TRK8_PROGRAM_MEMORY_END - TRK8_PROGRAM_MEMORY_START) + 1)
#endif

#ifndef TRK8_STACK_LENGTH
    #define TRK8_STACK_LENGTH ((TRK8_STACK_END - TRK8_STACK_START) + 1)
#endif

#ifndef TRK8_GENERAL_PURPOSE_MEMORY_LENGTH
    #define TRK8_GENERAL_PURPOSE_MEMORY_LENGTH ((TRK8_GENERAL_PURPOSE_MEMORY_END - TRK8_GENERAL_PURPOSE_MEMORY_START) + 1)
#endif

#ifndef TRK8_PROGRAM_COUNTER_LENGTH
    #define TRK8_PROGRAM_COUNTER_LENGTH ((TRK8_PROGRAM_COUNTER_END - TRK8_PROGRAM_COUNTER_START) + 1)
#endif

#ifndef TRK8_PROGRAM_MEMORY_EOP_BYTE
    /**
     * if the pc reaches this without any instruction to
     * claim it, then the program is finished executing
    */
    #define TRK8_PROGRAM_MEMORY_EOP_BYTE (0xff)
#endif

typedef struct _TRK8_MEMORY {
    uint8_t program_memory[TRK8_PROGRAM_MEMORY_LENGTH];
    uint8_t stack[TRK8_STACK_LENGTH];
    uint8_t general_purpose[TRK8_GENERAL_PURPOSE_MEMORY_LENGTH];
    uint8_t program_counter[TRK8_PROGRAM_COUNTER_LENGTH];
} trk8_memory_t;

void memory_init(trk8_memory_t* total_memory, uint8_t* program_memory, const uint16_t program_memory_length);

uint8_t memory_fetch_byte(const trk8_memory_t memory, const uint16_t address);
void memory_write_byte(trk8_memory_t* memory, const uint16_t address, const uint8_t data);

void memory_increment_program_counter(trk8_memory_t* memory, const uint8_t amount);

#endif
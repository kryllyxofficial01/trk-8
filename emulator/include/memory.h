#ifndef __TRK8_MEMORY_H
#define __TRK8_MEMORY_H

#include <stdio.h>
#include <stdint.h>

#ifndef TRK8_PROGRAM_MEMORY_START
    #define TRK8_PROGRAM_MEMORY_START (0x0000)
#endif

#ifndef TRK8_PROGRAM_MEMORY_END
    #define TRK8_PROGRAM_MEMORY_END (0x7fff)
#endif

#ifndef TRK8_PROGRAM_MEMORY_LENGTH
    #define TRK8_PROGRAM_MEMORY_LENGTH (TRK8_PROGRAM_MEMORY_END - TRK8_PROGRAM_MEMORY_START + 1)
#endif

#ifndef TRK8_STACK_START
    #define TRK8_STACK_START (0x8000)
#endif

#ifndef TRK8_STACK_END
    #define TRK8_STACK_END (0x80ff)
#endif

#ifndef TRK8_STACK_LENGTH
    #define TRK8_STACK_LENGTH (TRK8_STACK_END - TRK8_STACK_START + 1)
#endif

#ifndef TRK8_GENERAL_PURPOSE_START
    #define TRK8_GENERAL_PURPOSE_START (0x8100)
#endif

#ifndef TRK8_GENERAL_PURPOSE_END
    #define TRK8_GENERAL_PURPOSE_END (0xffff)
#endif

#ifndef TRK8_GENERAL_PURPOSE_LENGTH
    #define TRK8_GENERAL_PURPOSE_LENGTH (TRK8_GENERAL_PURPOSE_END - TRK8_GENERAL_PURPOSE_START + 1)
#endif

typedef struct _TRK8_MEMORY {
    uint8_t program_memory[TRK8_PROGRAM_MEMORY_LENGTH];
    uint8_t stack[TRK8_STACK_LENGTH];
    uint8_t general_purpose[TRK8_GENERAL_PURPOSE_LENGTH];
} trk8_memory_t;

inline trk8_memory_t memory_init(void);

void memory_load_program(trk8_memory_t* memory, const uint8_t* program, const uint16_t program_length);

uint8_t memory_read_byte(const trk8_memory_t memory, const uint16_t address);
void memory_write_byte(trk8_memory_t* memory, const uint16_t address, const uint8_t byte);

void memory_dump(const trk8_memory_t memory, const uint16_t start_address, const uint16_t end_address);

#endif

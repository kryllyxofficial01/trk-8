#ifndef __TRK8_H
#define __TRK8_H

#include "memory.h"
#include "registers.h"
#include "utils.h"

typedef enum _TRK8_STATES {
    TRK8_STATE_RUNNING,
    TRK8_STATE_HALTED
} trk8_state_t;

typedef struct _TRK8_MACHINE {
    trk8_memory_t* memory;
    trk8_registers_t* registers;

    trk8_state_t state;
} trk8_machine_t;

void trk8_init(trk8_machine_t* machine);

void trk8_print_state(const trk8_machine_t machine);

const char* trk8_get_state_as_string(const trk8_state_t state);

#endif
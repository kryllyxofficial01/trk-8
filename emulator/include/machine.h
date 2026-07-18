#ifndef __TRK8_MACHINE_STATE_H
#define __TRK8_MACHINE_STATE_H

#include <stdbool.h>

#include "registers.h"
#include "memory.h"
#include "utils.h"

typedef struct _TRK8_MACHINE_STATE {
    trk8_registers_t registers;

    bool halted;
} trk8_machine_state_t;

typedef struct _TRK8_MACHINE {
    trk8_machine_state_t state;

    trk8_memory_t memory;
} trk8_machine_t;

trk8_machine_t machine_init(void);
trk8_machine_state_t machine_state_init(void);

void machine_run(trk8_machine_t* machine);

#endif
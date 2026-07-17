#ifndef __TRK8_MACHINE_STATE_H
#define __TRK8_MACHINE_STATE_H

#include <stdbool.h>

#include "registers.h"

typedef struct _TRK8_MACHINE_STATE {
    trk8_registers_t registers;

    bool halted;
} trk8_machine_state_t;

inline trk8_machine_state_t machine_init(void) {
    trk8_machine_state_t machine_state;

    machine_state.registers = registers_init();

    machine_state.halted = false;

    return machine_state;
}

#endif

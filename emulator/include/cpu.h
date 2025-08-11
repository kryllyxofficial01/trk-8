#ifndef __TRK8_CPU_H
#define __TRK8_CPU_H

#include "memory.h"
#include "registers.h"
#include "instructions.h"
#include "utils.h"

void cpu_run(trk8_memory_t* memory, trk8_registers_t* registers);

#endif
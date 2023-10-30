#include <stdio.h>

#include "include/cpu.h"
#include "include/registers.h"
#include "include/memory.h"

int main(int argc, char const* argv[]) {
    registers_t registers;
    uint8_t memory[MAX_MEM_SIZE];

    reset_registers(&registers);
    mem_init(memory);

    cpu_run_program(&registers, memory);

    return 0;
}

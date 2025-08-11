#include "include/cpu.h"

int main(void) {
    uint8_t program[5] = { 0x14, 0x02, 0x19, 0x5b, 0x02 };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 5);
    registers_init(&registers);

    registers_debug_print(registers);

    cpu_run(&memory, &registers);
}
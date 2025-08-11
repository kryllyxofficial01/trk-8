#include "include/cpu.h"

int main(void) {
    uint8_t program[10] = { 0x14, 0x00, 0x19, 0x1a, 0x00, 0xff, 0x23, 0x00, 0x2b, 0x02 };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 10);
    registers_init(&registers);

    cpu_run(&memory, &registers);

    registers_debug_print(registers);
}
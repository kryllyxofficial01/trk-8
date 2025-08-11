#include "include/cpu.h"

int main(void) {
    uint8_t program[7] = { 0x14, 0x00, 0x19, 0x33, 0x00, 0x3b, 0x01 };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 7);
    registers_init(&registers);

    registers_debug_print(registers);

    cpu_run(&memory, &registers);
}
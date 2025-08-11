#include "include/cpu.h"

int main(void) {
    uint8_t program[6] = { 0x14, 0x00, 0x19, 0x16, 0x01, 0x00 };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 6);
    registers_init(&registers);

    cpu_run(&memory, &registers);

    registers_debug_print(registers);
}
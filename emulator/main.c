#include "include/cpu.h"

int main(void) {
    uint8_t program[9] = { 0x14, 0x00, 0x17, 0x14, 0x01, 0x19, 0x66, 0x00, 0x01 };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 9);
    registers_init(&registers);

    registers_debug_print(registers);

    cpu_run(&memory, &registers);
}
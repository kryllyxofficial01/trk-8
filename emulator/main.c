#include "include/cpu.h"

int main(void) {
    uint8_t program[8] = { 0x14, 0x00, 0x19, 0x1a, 0x00, 0xff, 0x23, 0x00 };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 8);
    registers_init(&registers);

    cpu_run(&memory, &registers);

    registers_debug_print(registers);

    printf("0x%x\n", memory_fetch_byte(memory, 0xff00));
}
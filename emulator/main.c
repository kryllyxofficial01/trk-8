#include "include/cpu.h"

int main(void) {
    uint8_t program[23] = {
        0x14, 0x00, 0x80, // mov %a, 0x80
        0x1a, 0x14, 0x00, // lda 0x0014
        0x70,             // jn
        0x14, 0x00, 0x17, // mov %a, 0x17
        0x14, 0x01, 0x19, // mov %b, 0x19
        0x66, 0x00, 0x01, // cmp %a, %b
        0x70,             // jn
        0x14, 0x02, 0x01, // mov %c, 0x01
        0x14, 0x03, 0x01  // mov %d, 0x01
    };

    trk8_memory_t memory;
    trk8_registers_t registers;

    memory_init(&memory, program, 23);
    registers_init(&registers);

    cpu_print_state(memory, registers);

    cpu_run(&memory, &registers);
}
#include "include/registers.h"
#include "include/memory.h"

int main(void) {
    trk8_registers_t registers;
    trk8_memory_t memory;

    registers_init(&registers);

    uint8_t program[1] = { 0x0 };

    memory_init(&memory, program, 1);
}
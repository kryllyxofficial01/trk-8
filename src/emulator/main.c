#include <stdio.h>

#include "include/cpu.h"
#include "include/registers.h"
#include "include/memory.h"

int main(int argc, char const* argv[]) {
    registers_t registers;
    uint8_t memory[MAX_MEM_SIZE];

    reset_registers(&registers);
    mem_init(memory);

    // mov @a 1
    memory[0] = MOV_IMM;
    memory[1] = 0;
    memory[2] = 1;

    // mov @b 1
    memory[3] = MOV_IMM;
    memory[4] = 1;
    memory[5] = 2;

    // sub @a @b
    memory[6] = SUB_REG;
    memory[7] = 0;
    memory[8] = 1;

    // jn 0xf
    memory[9] = JN;
    memory[10] = 0x00;
    memory[11] = 0xf;

    // add @a 1
    memory[12] = ADD_IMM;
    memory[13] = 0;
    memory[14] = 1;

    // add @a 2
    memory[15] = ADD_IMM;
    memory[16] = 0;
    memory[17] = 2;

    memory[18] = HLT;

    cpu_run_program(&registers, memory);

    printf("0x%x\n", registers.general_purpose.a);

    return 0;
}
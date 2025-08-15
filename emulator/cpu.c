#include "include/cpu.h"

void cpu_run(trk8_machine_t* machine) {
    while (memory_get_program_counter(*machine->memory) <= TRK8_PROGRAM_MEMORY_END) {
        if (machine->state == TRK8_STATE_HALTED) {
            break;
        }

        uint8_t opcode = memory_fetch_byte(
            *machine->memory,
            memory_get_program_counter(*machine->memory)
        );

        if (opcode == TRK8_PROGRAM_MEMORY_EOP_BYTE) {
            break;
        }

        trk8_print_state(*machine);

        uint8_t instruction_index = opcode >> 3; // top 5 bits
        uint8_t operands_type = opcode & 0b111; // bottom 3 bits

        switch (instruction_index) {
            case TRK8_INSTRUCTION_NOP: trk8_nop(machine, operands_type); break;
            case TRK8_INSTRUCTION_MOV: trk8_mov(machine, operands_type); break;
            case TRK8_INSTRUCTION_LDA: trk8_lda(machine, operands_type); break;
            case TRK8_INSTRUCTION_STB: trk8_stb(machine, operands_type); break;
            case TRK8_INSTRUCTION_LDB: trk8_ldb(machine, operands_type); break;
            case TRK8_INSTRUCTION_PUSH: trk8_push(machine, operands_type); break;
            case TRK8_INSTRUCTION_POP: trk8_pop(machine, operands_type); break;
            case TRK8_INSTRUCTION_ADD: trk8_add(machine, operands_type); break;
            case TRK8_INSTRUCTION_AND: trk8_and(machine, operands_type); break;
            case TRK8_INSTRUCTION_OR: trk8_or(machine, operands_type); break;
            case TRK8_INSTRUCTION_NOT: trk8_not(machine, operands_type); break;
            case TRK8_INSTRUCTION_CMP: trk8_cmp(machine, operands_type); break;
            case TRK8_INSTRUCTION_JMP: trk8_jmp(machine, operands_type); break;
            case TRK8_INSTRUCTION_JN: trk8_jn(machine, operands_type); break;
            case TRK8_INSTRUCTION_JC: trk8_jc(machine, operands_type); break;
            case TRK8_INSTRUCTION_JZ: trk8_jz(machine, operands_type); break;
            case TRK8_INSTRUCTION_HLT: trk8_hlt(machine, operands_type); break;
        }
    }

    printf("\nProgram finished at address 0x%04x\n\n", memory_get_program_counter(*machine->memory));

    machine->state = TRK8_STATE_HALTED;

    trk8_print_state(*machine);
}
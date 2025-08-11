#include "include/cpu.h"

void cpu_run(trk8_memory_t* memory, trk8_registers_t* registers) {
    while (memory_get_program_counter(*memory) <= TRK8_PROGRAM_MEMORY_END) {
        uint8_t opcode = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

        if (opcode == TRK8_PROGRAM_MEMORY_EOP_BYTE) {
            break;
        }

        uint8_t instruction_index = opcode >> 3;
        uint8_t operands_type = opcode & 0b111;

        switch (instruction_index) {
            case TRK8_INSTRUCTION_NOP: trk8_nop(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_MOV: trk8_mov(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_LDA: trk8_lda(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_STB: trk8_stb(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_LDB: trk8_ldb(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_PUSH: trk8_push(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_POP: trk8_pop(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_ADD: trk8_add(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_AND: trk8_and(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_OR: trk8_or(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_NOT: trk8_not(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_CMP: trk8_cmp(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_TSF: trk8_tsf(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_JMP: trk8_jmp(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_JZ: trk8_jz(memory, registers, operands_type); break;
            case TRK8_INSTRUCTION_HLT: trk8_hlt(memory, registers, operands_type); break;
        }
    }
}
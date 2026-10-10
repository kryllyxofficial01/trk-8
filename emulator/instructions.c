#include "include/instructions.h"

void execute_no_operands_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.no_operands_id) {
        case TRK8_INSTRUCTION_ID_NOP: instruction_nop(registers, memory); break;
        case TRK8_INSTRUCTION_ID_ADC: instruction_adc(registers, memory); break;
        case TRK8_INSTRUCTION_ID_AND: instruction_and(registers, memory); break;
        case TRK8_INSTRUCTION_ID_OR: instruction_or(registers, memory); break;
        case TRK8_INSTRUCTION_ID_NOT: instruction_not(registers, memory); break;
        case TRK8_INSTRUCTION_ID_CMP: instruction_cmp(registers, memory); break;
        case TRK8_INSTRUCTION_ID_JMP: instruction_jmp(registers, memory); break;
        case TRK8_INSTRUCTION_ID_BNE: instruction_bne(registers, memory); break;
        case TRK8_INSTRUCTION_ID_BCA: instruction_bca(registers, memory); break;
        case TRK8_INSTRUCTION_ID_BZE: instruction_bze(registers, memory); break;
        case TRK8_INSTRUCTION_ID_HLT: instruction_hlt(registers, memory); break;
    }
}

void execute_one_operand_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.one_operand_id) {
        case TRK8_INSTRUCTION_ID_STB: instruction_stb(registers, memory, opcode.register_id, opcode.has_immediate_operand); break;
        case TRK8_INSTRUCTION_ID_LDB: instruction_ldb(registers, memory, opcode.register_id, opcode.has_immediate_operand); break;
        case TRK8_INSTRUCTION_ID_PUSH: instruction_push(registers, memory, opcode.register_id, opcode.has_immediate_operand); break;
        case TRK8_INSTRUCTION_ID_POP: instruction_pop(registers, memory, opcode.register_id, opcode.has_immediate_operand); break;
    }
}

void execute_two_operands_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.two_operands_id) {
        case TRK8_INSTRUCTION_ID_MOV: instruction_mov(registers, memory, opcode.register_id, opcode.has_immediate_operand); break;
    }
}

void execute_has_16bit_operand_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.has_16bit_operand_id) {
        case TRK8_INSTRUCTION_ID_LDA: instruction_lda(registers, memory); break;
    }
}

void instruction_nop(trk8_registers_t* registers, trk8_memory_t* memory) {
    __asm__ __volatile__ ("nop");
}

void instruction_mov(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t destination_register_id, const bool has_immediate_operand) {
    registers_increment_pc(registers, 1);

    uint8_t source = memory_read_byte(*memory, registers_get_pc_word(*registers));

    if (has_immediate_operand) {
        registers_set(registers, destination_register_id, source);
    }
    else {
        registers_set(registers, destination_register_id, registers_get(*registers, source));
    }
}

void instruction_lda(trk8_registers_t* registers, trk8_memory_t* memory) {
    registers_increment_pc(registers, 1);

    registers_set(registers, TRK8_REGISTER_AL, memory_read_byte(*memory, registers_get_pc_word(*registers)));

    registers_increment_pc(registers, 1);

    registers_set(registers, TRK8_REGISTER_AH, memory_read_byte(*memory, registers_get_pc_word(*registers)));
}

void instruction_stb(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source;

    if (has_immediate_operand) {
        registers_increment_pc(registers, 1);

        source = memory_read_byte(*memory, registers_get_pc_word(*registers));
    }
    else {
        source = registers_get(*registers, register_id);
    }

    memory_write_byte(memory, registers_get_address_word(*registers), source);
}

void instruction_ldb(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source = memory_read_byte(*memory, registers_get_address_word(*registers));

    registers_set(registers, register_id, source);
}

void instruction_push(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source;

    if (has_immediate_operand) {
        registers_increment_pc(registers, 1);

        source = memory_read_byte(*memory, registers_get_pc_word(*registers));
    }
    else {
        source = registers_get(*registers, register_id);
    }

    memory_write_byte(memory, TRK8_STACK_START + registers_get(*registers, TRK8_REGISTER_SP), source);

    registers_set(registers, TRK8_REGISTER_SP, registers_get(*registers, TRK8_REGISTER_SP) - 1);
}

void instruction_pop(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source = memory_read_byte(*memory, TRK8_STACK_START + registers_get(*registers, TRK8_REGISTER_SP));

    registers_set(registers, register_id, source);

    registers_set(registers, TRK8_REGISTER_SP, registers_get(*registers, TRK8_REGISTER_SP) + 1);
}

void instruction_adc(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) + registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));
}

void instruction_and(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) & registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));
}

void instruction_or(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) | registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));
}

void instruction_not(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = ~registers_get(*registers, TRK8_REGISTER_A);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));
}

void instruction_cmp(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);
}

void instruction_jmp(trk8_registers_t* registers, trk8_memory_t* memory) {

}

void instruction_bne(trk8_registers_t* registers, trk8_memory_t* memory) {

}

void instruction_bca(trk8_registers_t* registers, trk8_memory_t* memory) {

}

void instruction_bze(trk8_registers_t* registers, trk8_memory_t* memory) {

}

void instruction_hlt(trk8_registers_t* registers, trk8_memory_t* memory) {

}
#include "include/instructions.h"

static inline void load_pc_with_address(trk8_registers_t* registers) {
    registers_set(registers, TRK8_REGISTER_PCL, registers_get(*registers, TRK8_REGISTER_AL));
    registers_set(registers, TRK8_REGISTER_PCH, registers_get(*registers, TRK8_REGISTER_AH));
}

bool execute_no_operands_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.no_operands_id) {
        case TRK8_INSTRUCTION_ID_NOP: return instruction_nop(registers, memory);
        case TRK8_INSTRUCTION_ID_ADC: return instruction_adc(registers, memory);
        case TRK8_INSTRUCTION_ID_AND: return instruction_and(registers, memory);
        case TRK8_INSTRUCTION_ID_OR: return instruction_or(registers, memory);
        case TRK8_INSTRUCTION_ID_NOT: return instruction_not(registers, memory);
        case TRK8_INSTRUCTION_ID_CMP: return instruction_cmp(registers, memory);
        case TRK8_INSTRUCTION_ID_JMP: return instruction_jmp(registers, memory);
        case TRK8_INSTRUCTION_ID_BNE: return instruction_bne(registers, memory);
        case TRK8_INSTRUCTION_ID_BCA: return instruction_bca(registers, memory);
        case TRK8_INSTRUCTION_ID_BZE: return instruction_bze(registers, memory);
        case TRK8_INSTRUCTION_ID_HLT: return instruction_hlt(registers, memory);
    }
}

bool execute_one_operand_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.one_operand_id) {
        case TRK8_INSTRUCTION_ID_STB: return instruction_stb(registers, memory, opcode.register_id, opcode.has_immediate_operand);
        case TRK8_INSTRUCTION_ID_LDB: return instruction_ldb(registers, memory, opcode.register_id, opcode.has_immediate_operand);
        case TRK8_INSTRUCTION_ID_PUSH: return instruction_push(registers, memory, opcode.register_id, opcode.has_immediate_operand);
        case TRK8_INSTRUCTION_ID_POP: return instruction_pop(registers, memory, opcode.register_id, opcode.has_immediate_operand);
    }
}

bool execute_two_operands_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.two_operands_id) {
        case TRK8_INSTRUCTION_ID_MOV: return instruction_mov(registers, memory, opcode.register_id, opcode.has_immediate_operand);
    }
}

bool execute_has_16bit_operand_opcode(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.has_16bit_operand_id) {
        case TRK8_INSTRUCTION_ID_LDA: return instruction_lda(registers, memory);
    }
}

bool instruction_nop(trk8_registers_t* registers, trk8_memory_t* memory) {
    __asm__ __volatile__ ("nop");

    return true;
}

bool instruction_mov(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t destination_register_id, const bool has_immediate_operand) {
    registers_increment_pc(registers, 1);

    uint8_t source = memory_read_byte(*memory, registers_get_pc_word(*registers));

    if (has_immediate_operand) {
        registers_set(registers, destination_register_id, source);
    }
    else {
        registers_set(registers, destination_register_id, registers_get(*registers, source));
    }

    return true;
}

bool instruction_lda(trk8_registers_t* registers, trk8_memory_t* memory) {
    registers_increment_pc(registers, 1);

    registers_set(registers, TRK8_REGISTER_AL, memory_read_byte(*memory, registers_get_pc_word(*registers)));

    registers_increment_pc(registers, 1);

    registers_set(registers, TRK8_REGISTER_AH, memory_read_byte(*memory, registers_get_pc_word(*registers)));

    return true;
}

bool instruction_stb(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source;

    if (has_immediate_operand) {
        registers_increment_pc(registers, 1);

        source = memory_read_byte(*memory, registers_get_pc_word(*registers));
    }
    else {
        source = registers_get(*registers, register_id);
    }

    memory_write_byte(memory, registers_get_address_word(*registers), source);

    return true;
}

bool instruction_ldb(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source = memory_read_byte(*memory, registers_get_address_word(*registers));

    registers_set(registers, register_id, source);

    return true;
}

bool instruction_push(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
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

    return true;
}

bool instruction_pop(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_register_id_t register_id, const bool has_immediate_operand) {
    uint8_t source = memory_read_byte(*memory, TRK8_STACK_START + registers_get(*registers, TRK8_REGISTER_SP));

    registers_set(registers, register_id, source);

    registers_set(registers, TRK8_REGISTER_SP, registers_get(*registers, TRK8_REGISTER_SP) + 1);

    return true;
}

bool instruction_adc(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) + registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));

    return true;
}

bool instruction_and(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) & registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));

    return true;
}

bool instruction_or(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) | registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));

    return true;
}

bool instruction_not(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = ~registers_get(*registers, TRK8_REGISTER_A);

    registers_update_flags(registers, result);

    registers_set(registers, TRK8_REGISTER_X, TRK8_GET_LOW_BYTE(result));

    return true;
}

bool instruction_cmp(trk8_registers_t* registers, trk8_memory_t* memory) {
    uint16_t result = registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, result);

    return true;
}

bool instruction_jmp(trk8_registers_t* registers, trk8_memory_t* memory) {
    load_pc_with_address(registers);

    registers_increment_pc(registers, -1);

    return true;
}

bool instruction_bne(trk8_registers_t* registers, trk8_memory_t* memory) {
    if (TRK8_BIT_GET(registers_get(*registers, TRK8_REGISTER_F), TRK8_FLAGS_NEGATIVE_BIT_INDEX)) {
        load_pc_with_address(registers);

        registers_increment_pc(registers, -1);
    }

    return true;
}

bool instruction_bca(trk8_registers_t* registers, trk8_memory_t* memory) {
    if (TRK8_BIT_GET(registers_get(*registers, TRK8_REGISTER_F), TRK8_FLAGS_CARRY_BIT_INDEX)) {
        load_pc_with_address(registers);

        registers_increment_pc(registers, -1);
    }

    return true;
}

bool instruction_bze(trk8_registers_t* registers, trk8_memory_t* memory) {
    if (TRK8_BIT_GET(registers_get(*registers, TRK8_REGISTER_F), TRK8_FLAGS_ZERO_BIT_INDEX)) {
        load_pc_with_address(registers);

        registers_increment_pc(registers, -1);
    }

    return true;
}

bool instruction_hlt(trk8_registers_t* registers, trk8_memory_t* memory) {
    return false;
}
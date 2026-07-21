#include "include/instructions.h"

void execute_data_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.data_id) {
        case TRK8_DATA_INST_MOV: instruction_mov(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_DATA_INST_XSP: instruction_xsp(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_DATA_INST_XCF: instruction_xcf(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_DATA_INST_XCA: instruction_xca(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_DATA_INST_PUSH: instruction_push(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_DATA_INST_POP: instruction_pop(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
    }
}

void execute_arithmetic_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.arithmetic_id) {
        case TRK8_ARITH_INST_ADC: instruction_adc(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_ARITH_INST_AND: instruction_and(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_ARITH_INST_OR: instruction_or(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_ARITH_INST_NOT: instruction_not(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_ARITH_INST_CMP: instruction_cmp(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
    }
}

void execute_memory_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.memory_id) {
        case TRK8_MEMORY_INST_STB: instruction_stb(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_MEMORY_INST_LDB: instruction_ldb(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_MEMORY_INST_JMP: instruction_jmp(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_MEMORY_INST_BNE: instruction_bne(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_MEMORY_INST_BCA: instruction_bca(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_MEMORY_INST_BZE: instruction_bze(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
    }
}

void execute_misc_instruction(trk8_registers_t* registers, trk8_memory_t* memory, const trk8_opcode_t opcode) {
    switch (opcode.instruction_id.misc_id) {
        case TRK8_MISC_INST_NOP: instruction_nop(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
        case TRK8_MISC_INST_HLT: instruction_hlt(registers, memory, opcode.has_immediate, opcode.first_register_id); break;
    }
}

void instruction_nop(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    asm volatile("nop");
}

void instruction_mov(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    registers_increment_pc(registers, 1);

    uint8_t second_operand = memory_read_byte(*memory, registers_get_pc_word(*registers));

    if (!has_immediate) {
        second_operand = registers_get(*registers, second_operand);
    }

    registers_set(registers, first_register_id, second_operand);
}

void instruction_xsp(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    registers_set(
        registers,
        TRK8_REGISTER_A,
        registers_get(*registers, TRK8_REGISTER_A) + registers_get(*registers, TRK8_REGISTER_SP)
    );

    registers_set(
        registers,
        TRK8_REGISTER_SP,
        registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_SP)
    );

    registers_set(
        registers,
        TRK8_REGISTER_A,
        registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_SP)
    );
}

void instruction_xcf(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    registers_set(
        registers,
        TRK8_REGISTER_A,
        registers_get(*registers, TRK8_REGISTER_A) + registers_get(*registers, TRK8_REGISTER_F)
    );

    registers_set(
        registers,
        TRK8_REGISTER_F,
        registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_F)
    );

    registers_set(
        registers,
        TRK8_REGISTER_A,
        registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_F)
    );
}

void instruction_xca(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    registers_set(
        registers,
        TRK8_REGISTER_A,
        registers_get(*registers, TRK8_REGISTER_A) + registers_get(*registers, TRK8_REGISTER_AL)
    );

    registers_set(
        registers,
        TRK8_REGISTER_AL,
        registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_AL)
    );

    registers_set(
        registers,
        TRK8_REGISTER_A,
        registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_AL)
    );

    registers_set(
        registers,
        TRK8_REGISTER_B,
        registers_get(*registers, TRK8_REGISTER_B) + registers_get(*registers, TRK8_REGISTER_AH)
    );

    registers_set(
        registers,
        TRK8_REGISTER_AH,
        registers_get(*registers, TRK8_REGISTER_B) - registers_get(*registers, TRK8_REGISTER_AH)
    );

    registers_set(
        registers,
        TRK8_REGISTER_B,
        registers_get(*registers, TRK8_REGISTER_B) - registers_get(*registers, TRK8_REGISTER_AH)
    );
}

void instruction_stb(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint16_t value;

    if (has_immediate) {
        registers_increment_pc(registers, 1);

        value = memory_read_byte(*memory, registers_get_pc_word(*registers));
    }
    else {
        value = registers_get(*registers, first_register_id);
    }

    memory_write_byte(memory, registers_get_address_word(*registers), value);
}

void instruction_ldb(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    registers_set(
        registers,
        first_register_id,
        memory_read_byte(*memory, registers_get_address_word(*registers))
    );
}

void instruction_push(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint8_t value;

    if (has_immediate) {
        registers_increment_pc(registers, 1);

        value = memory_read_byte(*memory, registers_get_pc_word(*registers));
    }
    else {
        value = registers_get(*registers, first_register_id);
    }

    memory_write_byte(memory, TRK8_STACK_START + registers_get(*registers, TRK8_REGISTER_SP), value);

    registers_set(registers, TRK8_REGISTER_SP, registers_get(*registers, TRK8_REGISTER_SP) - 1);
}

void instruction_pop(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    registers_set(registers, TRK8_REGISTER_SP, registers_get(*registers, TRK8_REGISTER_SP) + 1);

    registers_set(
        registers,
        first_register_id,
        memory_read_byte(*memory, TRK8_STACK_START + registers_get(*registers, TRK8_REGISTER_SP))
    );
}

void instruction_adc(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint8_t carry = TRK8_BIT_GET(
        registers_get(*registers, TRK8_REGISTER_F),
        TRK8_FLAGS_CARRY_BIT_INDEX
    );

    uint16_t value = registers_get(*registers, TRK8_REGISTER_A) + registers_get(*registers, TRK8_REGISTER_B) + carry;

    registers_set(registers, TRK8_REGISTER_X, (uint8_t) value);

    registers_update_flags(registers, value);
}

void instruction_and(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint8_t value = registers_get(*registers, TRK8_REGISTER_A) & registers_get(*registers, TRK8_REGISTER_B);

    registers_set(registers, TRK8_REGISTER_X, value);

    registers_update_flags(registers, value);
}

void instruction_or(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint8_t value = registers_get(*registers, TRK8_REGISTER_A) | registers_get(*registers, TRK8_REGISTER_B);

    registers_set(registers, TRK8_REGISTER_X, value);

    registers_update_flags(registers, value);
}

void instruction_not(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint8_t value = ~registers_get(*registers, TRK8_REGISTER_A);

    registers_set(registers, TRK8_REGISTER_X, value);

    registers_update_flags(registers, value);
}

void instruction_cmp(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {
    uint8_t value = registers_get(*registers, TRK8_REGISTER_A) - registers_get(*registers, TRK8_REGISTER_B);

    registers_update_flags(registers, value);
}

void instruction_jmp(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {

}

void instruction_bne(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {

}

void instruction_bca(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {

}

void instruction_bze(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {

}

void instruction_hlt(trk8_registers_t* registers, trk8_memory_t* memory, bool has_immediate, const trk8_register_id_t first_register_id) {

}
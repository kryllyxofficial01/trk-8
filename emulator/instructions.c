#include "include/instructions.h"

void trk8_nop(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {
    memory_increment_program_counter(memory, 1);
}

void trk8_mov(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {
    memory_increment_program_counter(memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_REG_IMM8: {
            uint8_t register_id = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

            memory_increment_program_counter(memory, 1);

            uint8_t data = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

            registers_set(registers, register_id, data);

            break;
        }

        case TRK8_OPERANDS_TYPE_REG_REG: {
            uint8_t destination_id = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

            memory_increment_program_counter(memory, 1);

            uint8_t source_id = memory_fetch_byte(*memory, memory_get_program_counter(*memory));
            uint8_t source_data = registers_get(*registers, source_id);

            registers_set(registers, destination_id, source_data);

            break;
        }
    }

    memory_increment_program_counter(memory, 1);
}

void trk8_lda(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {
    memory_increment_program_counter(memory, 1);

    registers->address.low = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

    memory_increment_program_counter(memory, 1);

    registers->address.high = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

    memory_increment_program_counter(memory, 1);
}

void trk8_stb(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {
    uint16_t address = TRK8_WORD(
        registers->address.high,
        registers->address.low
    );

    memory_increment_program_counter(memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_IMM8: {
            uint8_t data = memory_fetch_byte(*memory, memory_get_program_counter(*memory));

            memory_write_byte(memory, address, data);

            break;
        }

        case TRK8_OPERANDS_TYPE_REGISTER: {
            uint8_t register_id = memory_fetch_byte(*memory, memory_get_program_counter(*memory));
            uint8_t register_data = registers_get(*registers, register_id);

            memory_write_byte(memory, address, register_data);

            break;
        }
    }

    memory_increment_program_counter(memory, 1);
}

void trk8_ldb(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_push(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_pop(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_add(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_and(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_or(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_not(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_cmp(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_tsf(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_jmp(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_jz(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}

void trk8_hlt(trk8_memory_t* memory, trk8_registers_t* registers, uint8_t operands_type) {

}
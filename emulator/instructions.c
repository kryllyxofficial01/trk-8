#include "include/instructions.h"

void trk8_nop(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);
}

void trk8_mov(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_REG_IMM8: {
            uint8_t register_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            memory_increment_program_counter(machine->memory, 1);

            uint8_t data = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            registers_set(machine->registers, register_id, data);

            registers_update_flags(machine->registers, data);

            break;
        }

        case TRK8_OPERANDS_TYPE_REG_REG: {
            uint8_t destination_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            memory_increment_program_counter(machine->memory, 1);

            uint8_t source_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t source_data = registers_get(*machine->registers, source_id);

            registers_set(machine->registers, destination_id, source_data);

            registers_update_flags(machine->registers, source_data);

            break;
        }
    }

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_lda(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    registers_set(
        machine->registers,
        TRK8_REGISTER_ADDRESS_LOW,
        memory_fetch_byte(
            *machine->memory,
            memory_get_program_counter(*machine->memory)
        )
    );

    memory_increment_program_counter(machine->memory, 1);

    registers_set(
        machine->registers,
        TRK8_REGISTER_ADDRESS_HIGH,
        memory_fetch_byte(
            *machine->memory,
            memory_get_program_counter(*machine->memory)
        )
    );

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_stb(trk8_machine_t* machine, uint8_t operands_type) {
    uint8_t address_low = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_LOW);
    uint8_t address_high = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_HIGH);

    uint16_t address = TRK8_WORD(address_high, address_low);

    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_IMM8: {
            uint8_t data = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            memory_write_byte(machine->memory, address, data);

            break;
        }

        case TRK8_OPERANDS_TYPE_REGISTER: {
            uint8_t register_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t register_data = registers_get(*machine->registers, register_id);

            memory_write_byte(machine->memory, address, register_data);

            break;
        }
    }

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_ldb(trk8_machine_t* machine, uint8_t operands_type) {
    uint8_t address_low = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_LOW);
    uint8_t address_high = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_HIGH);

    uint16_t address = TRK8_WORD(address_high, address_low);

    memory_increment_program_counter(machine->memory, 1);

    uint8_t register_id = memory_fetch_byte(
        *machine->memory,
        memory_get_program_counter(*machine->memory)
    );

    uint8_t data = memory_fetch_byte(*machine->memory, address);

    registers_set(machine->registers, register_id, data);

    registers_update_flags(machine->registers, data);

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_push(trk8_machine_t* machine, uint8_t operands_type) {
    uint8_t stack_pointer = registers_get(*machine->registers, TRK8_REGISTER_SP);

    uint16_t stack_address = TRK8_STACK_START + stack_pointer;

    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_IMM8: {
            uint8_t data = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            memory_write_byte(machine->memory, stack_address, data);
        }

        case TRK8_OPERANDS_TYPE_REGISTER: {
            uint8_t register_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t register_data = registers_get(*machine->registers, register_id);

            memory_write_byte(machine->memory, stack_address, register_data);
        }
    }

    registers_set(machine->registers, TRK8_REGISTER_SP, stack_pointer - 1);

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_pop(trk8_machine_t* machine, uint8_t operands_type) {
    uint8_t stack_pointer = registers_get(*machine->registers, TRK8_REGISTER_SP);

    uint16_t stack_address = TRK8_STACK_START + stack_pointer;

    memory_increment_program_counter(machine->memory, 1);

    uint8_t register_id = memory_fetch_byte(
        *machine->memory,
        memory_get_program_counter(*machine->memory)
    );

    uint8_t data = memory_fetch_byte(*machine->memory, stack_address);

    registers_set(machine->registers, register_id, data);

    registers_update_flags(machine->registers, data);

    registers_set(machine->registers, TRK8_REGISTER_SP, stack_pointer + 1);

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_add(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_REG_IMM8: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_value = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint16_t sum = left_operand_value + right_operand_value;

            registers_set(machine->registers, left_operand_id, sum);

            registers_update_flags(machine->registers, sum);

            break;
        }

        case TRK8_OPERANDS_TYPE_REG_REG: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t right_operand_value = registers_get(*machine->registers, right_operand_id);

            uint16_t sum = left_operand_value + right_operand_value;

            registers_set(machine->registers, left_operand_id, sum);

            registers_update_flags(machine->registers, sum);

            break;
        }
    }

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_and(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_REG_IMM8: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_value = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint16_t result = left_operand_value & right_operand_value;

            registers_set(machine->registers, left_operand_id, result);

            registers_update_flags(machine->registers, result);

            break;
        }

        case TRK8_OPERANDS_TYPE_REG_REG: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t right_operand_value = registers_get(*machine->registers, right_operand_id);

            uint16_t result = left_operand_value & right_operand_value;

            registers_set(machine->registers, left_operand_id, result);

            registers_update_flags(machine->registers, result);

            break;
        }
    }

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_or(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_REG_IMM8: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_value = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint16_t result = left_operand_value | right_operand_value;

            registers_set(machine->registers, left_operand_id, result);

            registers_update_flags(machine->registers, result);

            break;
        }

        case TRK8_OPERANDS_TYPE_REG_REG: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t right_operand_value = registers_get(*machine->registers, right_operand_id);

            uint16_t result = left_operand_value | right_operand_value;

            registers_set(machine->registers, left_operand_id, result);

            registers_update_flags(machine->registers, result);

            break;
        }
    }

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_not(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    uint8_t register_id = memory_fetch_byte(
        *machine->memory,
        memory_get_program_counter(*machine->memory)
    );
    uint8_t value = registers_get(*machine->registers, register_id);

    uint8_t result = ~value;

    registers_set(machine->registers, register_id, result);

    registers_update_flags(machine->registers, result);

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_cmp(trk8_machine_t* machine, uint8_t operands_type) {
    memory_increment_program_counter(machine->memory, 1);

    switch (operands_type) {
        case TRK8_OPERANDS_TYPE_REG_IMM8: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_value = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            registers_update_flags(machine->registers, left_operand_value - right_operand_value);

            break;
        }

        case TRK8_OPERANDS_TYPE_REG_REG: {
            uint8_t left_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t left_operand_value = registers_get(*machine->registers, left_operand_id);

            memory_increment_program_counter(machine->memory, 1);

            uint8_t right_operand_id = memory_fetch_byte(
                *machine->memory,
                memory_get_program_counter(*machine->memory)
            );

            uint8_t right_operand_value = registers_get(*machine->registers, right_operand_id);

            registers_update_flags(machine->registers, left_operand_value - right_operand_value);

            break;
        }
    }

    memory_increment_program_counter(machine->memory, 1);
}

void trk8_jmp(trk8_machine_t* machine, uint8_t operands_type) {
    uint8_t address_low = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_LOW);
    uint8_t address_high = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_HIGH);

    uint16_t address = TRK8_WORD(address_high, address_low);

    memory_set_program_counter(machine->memory, address);
}

void trk8_jn(trk8_machine_t* machine, uint8_t operands_type) {
    if (TRK8_BIT_CHECK(machine->registers->flags, TRK8_NEGATIVE_FLAG_INDEX)) {
        uint8_t address_low = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_LOW);
        uint8_t address_high = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_HIGH);

        uint16_t address = TRK8_WORD(address_high, address_low);

        memory_set_program_counter(machine->memory, address);
    }
    else {
        memory_increment_program_counter(machine->memory, 1);
    }
}

void trk8_jc(trk8_machine_t* machine, uint8_t operands_type) {
    if (TRK8_BIT_CHECK(machine->registers->flags, TRK8_CARRY_FLAG_INDEX)) {
        uint8_t address_low = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_LOW);
        uint8_t address_high = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_HIGH);

        uint16_t address = TRK8_WORD(address_high, address_low);

        memory_set_program_counter(machine->memory, address);
    }
    else {
        memory_increment_program_counter(machine->memory, 1);
    }
}

void trk8_jz(trk8_machine_t* machine, uint8_t operands_type) {
    if (TRK8_BIT_CHECK(machine->registers->flags, TRK8_ZERO_FLAG_INDEX)) {
        uint8_t address_low = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_LOW);
        uint8_t address_high = registers_get(*machine->registers, TRK8_REGISTER_ADDRESS_HIGH);

        uint16_t address = TRK8_WORD(address_high, address_low);

        memory_set_program_counter(machine->memory, address);
    }
    else {
        memory_increment_program_counter(machine->memory, 1);
    }
}

void trk8_hlt(trk8_machine_t* machine, uint8_t operands_type) {
    machine->state = TRK8_STATE_HALTED;
}
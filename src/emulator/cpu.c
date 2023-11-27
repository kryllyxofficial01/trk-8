#include "include/cpu.h"

void cpu_run_program(registers_t* registers, uint8_t* memory) {
    uint16_t program_counter;

    while ((program_counter = get_pc(memory)) <= PRGM_MEM_END) {
        uint8_t opcode = mem_fetch(memory, program_counter);

        if (opcode == ASM_EOF) {
            break;
        }

        switch (opcode) {
            case NOP: break;

            case MOV_REG: cpu_mov(registers, memory, MOV_REG); break;
            case MOV_IMM: cpu_mov(registers, memory, MOV_IMM); break;

            case STB_REG: cpu_stb(registers, memory, STB_REG); break;
            case STB_IMM: cpu_stb(registers, memory, STB_IMM); break;

            case LDB_REG: cpu_ldb(registers, memory, LDB_REG); break;
            case LDB_IMM: cpu_ldb(registers, memory, LDB_IMM); break;

            case PUSH_REG: cpu_push(registers, memory, PUSH_REG); break;
            case PUSH_IMM: cpu_push(registers, memory, PUSH_IMM); break;

            case POP: cpu_pop(registers, memory); break;

            case ADD_REG: cpu_add(registers, memory, ADD_REG); break;
            case ADD_IMM: cpu_add(registers, memory, ADD_IMM); break;

            case SUB_REG: cpu_sub(registers, memory, SUB_REG); break;
            case SUB_IMM: cpu_sub(registers, memory, SUB_IMM); break;

            case MUL_REG: cpu_mul(registers, memory, MUL_REG); break;
            case MUL_IMM: cpu_mul(registers, memory, MUL_IMM); break;

            case DIV_REG: cpu_div(registers, memory, DIV_REG); break;
            case DIV_IMM: cpu_div(registers, memory, DIV_IMM); break;

            case AND_REG: cpu_div(registers, memory, AND_REG); break;
            case AND_IMM: cpu_div(registers, memory, AND_IMM); break;

            case OR_REG: cpu_div(registers, memory, OR_REG); break;
            case OR_IMM: cpu_div(registers, memory, OR_IMM); break;

            case NOT: cpu_not(registers, memory); break;

            case XOR_REG: cpu_xor(registers, memory, XOR_REG); break;
            case XOR_IMM: cpu_xor(registers, memory, XOR_IMM); break;

            case CMP_REG: cpu_cmp(registers, memory, CMP_REG); break;
            case CMP_IMM: cpu_cmp(registers, memory, CMP_IMM); break;

            case JMP: cpu_jmp(registers, memory); break;
            case JZ: cpu_jz(registers, memory); break;
            case JC: cpu_jc(registers, memory); break;
            case JN: cpu_jn(registers, memory); break;

            case HLT: cpu_hlt(); break;
        }

        update_pc(memory, get_pc(memory)+1);
    }
}

void cpu_mov(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t destination = mem_fetch(memory, get_pc(memory)+1);
    uint8_t source = mem_fetch(memory, get_pc(memory)+2);

    uint8_t value;
    if (variant == MOV_REG) {
        value = get_register(registers, source);
    }
    else if (variant == MOV_IMM) {
        value = source;
    }

    update_register(registers, destination, value);

    update_pc(memory, get_pc(memory)+2);
}

void cpu_stb(registers_t* registers, uint8_t* memory, uint8_t variant) {
    size_t offset;

    if (variant == STB_REG) {
        uint8_t destination = mem_fetch(memory, get_pc(memory)+1);
        uint8_t source = mem_fetch(memory, get_pc(memory)+2);

        uint8_t address = get_register(registers, destination);
        memory[address] = get_register(registers, source);

        offset = 2;
    }
    else if (variant == STB_IMM) {
        uint8_t destination_high = mem_fetch(memory, get_pc(memory)+1);
        uint8_t destination_low = mem_fetch(memory, get_pc(memory)+2);
        uint8_t source = mem_fetch(memory, get_pc(memory)+3);

        uint16_t destination = destination_low | (
            destination_high << 8
        );

        memory[destination] = get_register(registers, source);

        offset = 3;
    }

    update_pc(memory, get_pc(memory)+offset);
}

void cpu_ldb(registers_t* registers, uint8_t* memory, uint8_t variant) {
    size_t offset;

    uint8_t destination = mem_fetch(memory, get_pc(memory)+1);
    if (variant == LDB_REG) {
        uint8_t source = mem_fetch(memory, get_pc(memory)+2);

        uint8_t address = get_register(registers, source);
        update_register(registers, destination, memory[address]);

        offset = 2;
    }
    else if (variant == LDB_IMM) {
        uint8_t source_high = mem_fetch(memory, get_pc(memory)+2);
        uint8_t source_low = mem_fetch(memory, get_pc(memory)+3);

        uint16_t source = source_low | (
            source_high << 8
        );

        update_register(registers, destination, memory[source]);

        offset = 3;
    }

    update_pc(memory, get_pc(memory)+offset);
}

void cpu_push(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t source = mem_fetch(memory, get_pc(memory)+1);

    uint8_t value;
    if (variant == PUSH_REG) {
        value = get_register(registers, source);
        stack_push(registers, memory, value);
    }
    else if (variant == PUSH_IMM) {
        value = source;
    }

    stack_push(registers, memory, value);

    update_pc(memory, get_pc(memory)+1);
}

void cpu_pop(registers_t* registers, uint8_t* memory) {
    uint8_t destination = mem_fetch(memory, get_pc(memory)+1);

    update_register(
        registers, destination,
        stack_pop(registers, memory)
    );

    update_pc(memory, get_pc(memory)+1);
}

void cpu_add(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == ADD_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value += operandY_val;
    }
    else if (variant == ADD_IMM) {
        value += operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_sub(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == SUB_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value -= operandY_val;
    }
    else if (variant == SUB_IMM) {
        value -= operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_mul(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == MUL_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value *= operandY_val;
    }
    else if (variant == MUL_IMM) {
        value *= operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_div(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == DIV_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value /= operandY_val;
    }
    else if (variant == DIV_IMM) {
        value /= operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_and(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == AND_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value &= operandY_val;
    }
    else if (variant == AND_IMM) {
        value &= operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_or(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == OR_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value |= operandY_val;
    }
    else if (variant == OR_IMM) {
        value |= operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_not(registers_t* registers, uint8_t* memory) {
    uint8_t operand = mem_fetch(memory, get_pc(memory)+1);

    int value = ~get_register(registers, operand);

    update_flags(registers, value);
    update_register(
        registers, operand,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+1);
}

void cpu_xor(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == XOR_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value ^= operandY_val;
    }
    else if (variant == XOR_IMM) {
        value ^= operandY;
    }

    update_flags(registers, value);
    update_register(
        registers, operandX,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory)+2);
}

void cpu_cmp(registers_t* registers, uint8_t* memory, uint8_t variant) {
   uint8_t operandX = mem_fetch(memory, get_pc(memory)+1);
    uint8_t operandY = mem_fetch(memory, get_pc(memory)+2);

    int value = get_register(registers, operandX);
    if (variant == CMP_REG) {
        uint8_t operandY_val = get_register(registers, operandY);

        value -= operandY_val;
    }
    else if (variant == CMP_IMM) {
        value -= operandY;
    }

    update_flags(registers, value);

    update_pc(memory, get_pc(memory)+2);
}

void cpu_jmp(registers_t* registers, uint8_t* memory) {
    uint8_t address_high = mem_fetch(memory, get_pc(memory)+1);
    uint8_t address_low = mem_fetch(memory, get_pc(memory)+2);

    update_pc(memory, (address_low | (address_high << 8))-1);
}

void cpu_jz(registers_t* registers, uint8_t* memory) {
    uint8_t address_high = mem_fetch(memory, get_pc(memory)+1);
    uint8_t address_low = mem_fetch(memory, get_pc(memory)+2);

    if ((registers->flags >> ZERO_FLAG_OFFSET) & 1) {
        update_pc(memory, (address_low | (address_high << 8))-1);
    }
}

void cpu_jc(registers_t* registers, uint8_t* memory) {
    uint8_t address_high = mem_fetch(memory, get_pc(memory)+1);
    uint8_t address_low = mem_fetch(memory, get_pc(memory)+2);

    if ((registers->flags >> CARRY_FLAG_OFFSET) & 1) {
        update_pc(memory, (address_low | (address_high << 8))-1);
    }
}

void cpu_jn(registers_t* registers, uint8_t* memory) {
    uint8_t address_high = mem_fetch(memory, get_pc(memory)+1);
    uint8_t address_low = mem_fetch(memory, get_pc(memory)+2);

    if ((registers->flags >> NEGATIVE_FLAG_OFFSET) & 1) {
        update_pc(memory, (address_low | (address_high << 8))-1);
    }
}

void cpu_hlt() {
    exit(0);
}
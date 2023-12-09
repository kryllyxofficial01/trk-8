#include "include/cpu.h"

void cpu_run_program(registers_t* registers, uint8_t* memory) {
    uint16_t program_counter;

    while ((program_counter = get_pc(memory)) <= PRGM_MEM_END) {
        uint8_t opcode = mem_fetch(memory, program_counter);

        if (opcode == ASM_EOF) break;

        switch (opcode) {
            case NOP: break;

            case MOV_REG: cpu_mov(registers, memory, MOV_REG); break;
            case MOV_IMM: cpu_mov(registers, memory, MOV_IMM); break;

            case LDA_REG: cpu_lda(registers, memory, LDA_REG); break;
            case LDA_IMM: cpu_lda(registers, memory, LDA_IMM); break;

            case STB: cpu_stb(registers, memory); break;
            case LDB: cpu_ldb(registers, memory); break;

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
    uint8_t destination = mem_fetch(memory, get_pc(memory) + 1);

    uint8_t value;
    int offset;
    if (variant == MOV_REG) {
        value = get_register(
            registers,
            mem_fetch(memory, get_pc(memory) + 2)
        );

        offset = 2;
    }
    else if (variant == MOV_IMM) {
        value = mem_fetch(memory, get_pc(memory) + 3);

        offset = 3;
    }

    update_register(registers, destination, value);

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_lda(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t address_high = mem_fetch(memory, get_pc(memory) + 1);
    uint8_t address_low = mem_fetch(memory, get_pc(memory) + 2);

    update_register(registers, REGA, address_high);
    update_register(registers, REGB, address_low);

    update_pc(memory, get_pc(memory) + 2);
}

void cpu_stb(registers_t* registers, uint8_t* memory) {
    uint8_t source = mem_fetch(memory, get_pc(memory) + 1);

    uint16_t address = registers->general_purpose.b | (
        registers->general_purpose.a << 8
    );

    memory[address] = get_register(registers, source);

    update_pc(memory, get_pc(memory) + 1);
}

void cpu_ldb(registers_t* registers, uint8_t* memory) {
    uint8_t destination = mem_fetch(memory, get_pc(memory) + 1);

    uint16_t address = registers->general_purpose.b | (
        registers->general_purpose.a << 8
    );

    update_register(registers, destination, memory[address]);

    update_pc(memory, get_pc(memory) + 1);
}

void cpu_push(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t source = mem_fetch(memory, get_pc(memory) + 1);

    uint8_t value;
    if (variant == PUSH_REG) {
        value = get_register(registers, source);
        stack_push(registers, memory, value);
    }
    else if (variant == PUSH_IMM) {
        value = source;
    }

    stack_push(registers, memory, value);

    update_pc(memory, get_pc(memory) + 1);
}

void cpu_pop(registers_t* registers, uint8_t* memory) {
    uint8_t destination = mem_fetch(memory, get_pc(memory) + 1);

    update_register(
        registers, destination,
        stack_pop(registers, memory)
    );

    update_pc(memory, get_pc(memory) + 1);
}

void cpu_add(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == ADD_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value += get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == ADD_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value += operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_sub(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == SUB_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value -= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == SUB_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value -= operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_mul(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == MUL_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value *= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == MUL_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value *= operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_div(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == DIV_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value /= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == DIV_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value /= operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_and(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == AND_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value &= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == AND_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value &= operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_or(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == OR_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value |= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == OR_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value |= operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_not(registers_t* registers, uint8_t* memory) {
    uint8_t operand = mem_fetch(memory, get_pc(memory) + 1);

    int value = ~get_register(registers, operand);

    update_flags(registers, value);
    update_register(
        registers, operand,
        (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + 1);
}

void cpu_xor(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == XOR_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value ^= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == XOR_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value ^= operand_y;

        offset = 3;
    }

    update_flags(registers, value);
    update_register(
        registers, operand_x, (uint8_t)value
    );

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_cmp(registers_t* registers, uint8_t* memory, uint8_t variant) {
    uint8_t operand_x = mem_fetch(memory, get_pc(memory) + 1);

    int value = get_register(registers, operand_x);
    int offset;
    if (variant == CMP_REG) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 2);

        value -= get_register(registers, operand_y);

        offset = 2;
    }
    else if (variant == CMP_IMM) {
        uint8_t operand_y = mem_fetch(memory, get_pc(memory) + 3);

        value -= operand_y;

        offset = 3;
    }

    update_flags(registers, value);

    update_pc(memory, get_pc(memory) + offset);
}

void cpu_jmp(registers_t* registers, uint8_t* memory) {
    uint16_t address = registers->general_purpose.b | (
        registers->general_purpose.a << 8
    );

    update_pc(memory, address - 1);
}

void cpu_jz(registers_t* registers, uint8_t* memory) {
    uint16_t address = registers->general_purpose.b | (
        registers->general_purpose.a << 8
    );

    if ((registers->flags >> ZERO_FLAG_OFFSET) & 1) {
        update_pc(memory, address - 1);
    }
}

void cpu_jc(registers_t* registers, uint8_t* memory) {
    uint16_t address = registers->general_purpose.b | (
        registers->general_purpose.a << 8
    );

    if ((registers->flags >> CARRY_FLAG_OFFSET) & 1) {
        update_pc(memory, address - 1);
    }
}

void cpu_jn(registers_t* registers, uint8_t* memory) {
    uint16_t address = registers->general_purpose.b | (
        registers->general_purpose.a << 8
    );

    if ((registers->flags >> NEGATIVE_FLAG_OFFSET) & 1) {
        update_pc(memory, address - 1);
    }
}

void cpu_hlt() {
    exit(0);
}
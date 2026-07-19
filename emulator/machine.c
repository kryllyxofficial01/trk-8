#include "include/machine.h"

trk8_machine_t machine_init(void) {
    trk8_machine_t machine;

    machine.state = machine_state_init();

    machine.memory = memory_init();
}

trk8_machine_state_t machine_state_init(void) {
    trk8_machine_state_t machine_state;

    machine_state.registers = registers_init();

    machine_state.registers.pcl = TRK8_GET_LOW_BYTE(TRK8_PROGRAM_MEMORY_START);
    machine_state.registers.pch = TRK8_GET_HIGH_BYTE(TRK8_PROGRAM_MEMORY_START);

    machine_state.halted = false;

    return machine_state;
}

void machine_run(trk8_machine_t* machine) {
    while (!machine->state.halted) {
        uint8_t opcode = memory_read_byte(
            machine->memory,
            registers_get_pc_word(machine->state.registers)
        );

        if (opcode == 0x00) {
            machine->state.halted = true;

            continue;
        }

        trk8_opcode_t instruction_opcode = parse_opcode(opcode);

        execute_opcode(machine, instruction_opcode);

        registers_increment_pc(&machine->state.registers, 1);
    }
}

trk8_opcode_t parse_opcode(uint8_t opcode) {
    trk8_opcode_t instruction_opcode;

    uint8_t category = (opcode >> 6) & 0x03;
    uint8_t instruction_id = (opcode >> 3) & 0x07;
    uint8_t has_immediate = (opcode >> 2) & 0x01;
    uint8_t first_register_id = opcode & 0x03;

    switch (category) {
        case TRK8_INST_CAT_DATA: {
            instruction_opcode.category = TRK8_INST_CAT_DATA;
            instruction_opcode.instruction_id.data_id = instruction_id;

            break;
        }

        case TRK8_INST_CAT_ARITHMETIC: {
            instruction_opcode.category = TRK8_INST_CAT_ARITHMETIC;
            instruction_opcode.instruction_id.arithmetic_id = instruction_id;

            break;
        }

        case TRK8_INST_CAT_MEMORY: {
            instruction_opcode.category = TRK8_INST_CAT_MEMORY;
            instruction_opcode.instruction_id.memory_id = instruction_id;

            break;
        }

        case TRK8_INST_CAT_MISC: {
            instruction_opcode.category = TRK8_INST_CAT_MISC;
            instruction_opcode.instruction_id.misc_id = instruction_id;

            break;
        }
    }

    instruction_opcode.has_immediate = has_immediate;

    instruction_opcode.first_register_id = first_register_id;

    return instruction_opcode;
}

void execute_opcode(trk8_machine_t* machine, trk8_opcode_t opcode) {
    switch (opcode.category) {
        case TRK8_INST_CAT_DATA: execute_data_instruction(&machine->state.registers, &machine->memory, opcode); break;
        case TRK8_INST_CAT_ARITHMETIC: execute_arithmetic_instruction(&machine->state.registers, &machine->memory, opcode); break;
        case TRK8_INST_CAT_MEMORY: execute_memory_instruction(&machine->state.registers, &machine->memory, opcode); break;
        case TRK8_INST_CAT_MISC: execute_misc_instruction(&machine->state.registers, &machine->memory, opcode); break;
    }
}
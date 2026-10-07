#include "include/machine.h"

static inline trk8_opcode_t parse_opcode(uint8_t opcode) {
    trk8_opcode_t instruction_opcode;

    instruction_opcode.category = opcode & TRK8_OPCODE_CATEGORY_MASK;

    switch (instruction_opcode.category) {
        case TRK8_OPCODE_CATEGORY_NO_OPERANDS: {
            instruction_opcode.instruction_id.no_operands_id = opcode & TRK8_OPCODE_NO_OPERANDS_INSTRUCTION_ID_MASK;

            break;
        }

        case TRK8_OPCODE_CATEGORY_ONE_OPERAND: {
            instruction_opcode.instruction_id.one_operand_id = opcode & TRK8_OPCODE_ONE_OPERAND_INSTRUCTION_ID_MASK;

            uint8_t source_register_id = opcode & TRK8_OPCODE_ONE_OPERAND_SOURCE_REGISTER_ID_MASK;

            instruction_opcode.has_immediate_operand = source_register_id == TRK8_OPCODE_ONE_OPERAND_IMMEDIATE_VALUE_SOURCE;

            instruction_opcode.register_id = instruction_opcode.has_immediate_operand ? 0 : source_register_id;

            break;
        }

        case TRK8_OPCODE_CATEGORY_TWO_OPERANDS: {
            instruction_opcode.instruction_id.two_operands_id = opcode & TRK8_OPCODE_TWO_OPERANDS_INSTRUCTION_ID_MASK;

            instruction_opcode.register_id = opcode & TRK8_OPCODE_TWO_OPERANDS_DESTINATION_REGISTER_ID_MASK;

            instruction_opcode.has_immediate_operand = opcode & TRK8_OPCODE_TWO_OPERANDS_HAS_IMMEDIATE_OPERAND_MASK;

            break;
        }
    }

    return instruction_opcode;
}

static inline void execute_opcode(trk8_machine_t* machine, trk8_opcode_t opcode) {

}

trk8_machine_t machine_init(void) {
    trk8_machine_t machine;

    machine.state = machine_state_init();

    machine.memory = memory_init();

    return machine;
}

trk8_machine_state_t machine_state_init(void) {
    trk8_machine_state_t machine_state;

    machine_state.registers = registers_init();

    registers_set(&machine_state.registers, TRK8_REGISTER_SP, 0xff);

    registers_set(
        &machine_state.registers,
        TRK8_REGISTER_PCL,
        TRK8_GET_LOW_BYTE(TRK8_PROGRAM_MEMORY_START)
    );

    registers_set(
        &machine_state.registers,
        TRK8_REGISTER_PCH,
        TRK8_GET_HIGH_BYTE(TRK8_PROGRAM_MEMORY_START)
    );

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
#include "include/machine.h"

static inline trk8_opcode_t parse_opcode(uint8_t opcode) {
    trk8_opcode_t instruction_opcode;

    uint8_t category = opcode >> 6;

    switch (category) {
        case TRK8_OPCODE_CATEGORY_NO_OPERANDS: {
            instruction_opcode.category = category;

            instruction_opcode.arguments.no_operands.instruction_id = opcode & 0b00111111;

            break;
        }

        case TRK8_OPCODE_CATEGORY_ONE_OPERAND: {
            instruction_opcode.category = category;

            instruction_opcode.arguments.one_operand.instruction_id = opcode & 0b00110000;

            uint8_t register_id = opcode & 0b00001111;

            if (register_id == 0b1111) {
                instruction_opcode.arguments.one_operand.has_immediate = true;

                // set the register index to one that doesnt match to anything
                instruction_opcode.arguments.one_operand.register_id = 0b1110;
            }
            else {
                instruction_opcode.arguments.one_operand.register_id = register_id;
            }

            break;
        }

        case TRK8_OPCODE_CATEGORY_TWO_OPERANDS: {
            instruction_opcode.category = category;

            instruction_opcode.arguments.two_operands.instruction_id = opcode & 0b00100000;

            instruction_opcode.arguments.two_operands.destination_register_id = opcode & 0b00011110;

            instruction_opcode.arguments.two_operands.has_immediate = opcode & 0b00000001;

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
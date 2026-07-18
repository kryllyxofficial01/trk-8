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

        registers_increment_pc(&machine->state.registers, 1);
    }
}
#include "include/trk8.h"

void trk8_init(trk8_machine_t* machine) {
    machine->memory = malloc(sizeof(trk8_memory_t));
    machine->registers = malloc(sizeof(trk8_registers_t));

    memory_init(machine->memory);
    registers_init(machine->registers);

    machine->state = TRK8_STATE_RUNNING;
}

void trk8_print_state(const trk8_machine_t machine) {
    printf("Register Values:\n");

    printf("\tA: 0x%02x\n", machine.registers->general_purpose.a);
    printf("\tB: 0x%02x\n", machine.registers->general_purpose.b);
    printf("\tC: 0x%02x\n", machine.registers->general_purpose.c);
    printf("\tD: 0x%02x\n", machine.registers->general_purpose.d);

    printf("\tSP: 0x%02x\n", machine.registers->stack_pointer);

    printf("\tAddress: 0x%04x\n", TRK8_WORD(machine.registers->address.high, machine.registers->address.low));

    printf("\tF: 0x%02x\n", machine.registers->flags);

    printf("\tPC: 0x%04x\n", memory_get_program_counter(*machine.memory));

    printf("\nCPU State: '%s'\n", trk8_get_state_as_string(machine.state));

    printf("\n====================================\n");
}

const char* trk8_get_state_as_string(const trk8_state_t state) {
    switch (state) {
        case TRK8_STATE_RUNNING: return "Running";
        case TRK8_STATE_HALTED: return "Halted";
    }

    return "???";
}
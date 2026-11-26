#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "include/machine.h"

static inline uint8_t* load_file(const char* filename, uint16_t* program_length) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        fprintf(stderr, "Failed to open '%s'\n", filename);

        return NULL;
    }

    fseek(file, 0, SEEK_END);

    long file_size = ftell(file);

    rewind(file);

    if (file_size < 0) {
        fprintf(stderr, "Failed to get size of '%s'\n", filename);

        fclose(file);

        return NULL;
    }

    uint8_t* buffer = (uint8_t*) malloc(file_size);

    if (!buffer) {
        fprintf(stderr, "Failed to create program buffer\n", filename);

        fclose(file);

        return NULL;
    }

    uint16_t bytes_read = fread(buffer, 1, file_size, file);

    fclose(file);

    *program_length = bytes_read;

    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <path to binary file> --ps/--nps\n", argv[0]);

        return EXIT_FAILURE;
    }

    bool print_stack;

    if (strcmp(argv[2], "--ps") == 0) {
        print_stack = true;
    }
    else if (strcmp(argv[2], "--nps") == 0) {
        print_stack = false;
    }
    else {
        fprintf(stderr, "Invalid argument '%s'\n", argv[2]);

        return EXIT_FAILURE;
    }

    uint16_t program_length;

    uint8_t* program = load_file(argv[1], &program_length);

    if (!program) {
        return EXIT_FAILURE;
    }

    trk8_machine_t machine = machine_init();

    memory_load_program(&machine.memory, program, program_length);

    machine_run(&machine);

    machine_print_state(machine, print_stack);

    return EXIT_SUCCESS;
}

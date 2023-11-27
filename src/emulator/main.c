#include <stdio.h>
#include <string.h>

#include "include/cpu.h"
#include "include/registers.h"
#include "include/memory.h"
#include "include/utils.h"

#define MAX_STRING_SIZE 2048

int main(int argc, const char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    char* binary[(PRGM_MEM_END + 1) * 8];

    char line[MAX_STRING_SIZE];
    int instruction_idx = 0;
    while (fgets(line, sizeof(line), file)) {
        if (str_ends_with(line, "\n")) {
            strcpy(line, strtok(line, "\n"));
        }

        binary[instruction_idx] = malloc(MAX_STRING_SIZE);
        strcpy(binary[instruction_idx], line);

        instruction_idx++;
    }
    binary[instruction_idx] = NULL;

    fclose(file);

    registers_t registers;
    uint8_t memory[MAX_MEM_SIZE];

    reset_registers(&registers);
    mem_init(memory, binary);

    cpu_run_program(&registers, memory);

    printf("%i\n", registers.general_purpose.a);

    return 0;
}

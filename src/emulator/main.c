#include <stdio.h>
#include <string.h>

#include "include/cpu.h"
#include "include/registers.h"
#include "include/memory.h"

int main(int argc, const char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    char binary[(PRGM_MEM_END+1) * 8];
    char line[2048];
    uint16_t i = 0;
    while (fgets(line, sizeof(line), file)) {
        strcat(binary, line);
    }

    fclose(file);

    registers_t registers;
    uint8_t memory[MAX_MEM_SIZE];

    reset_registers(&registers);
    mem_init(memory, binary);

    cpu_run_program(&registers, memory);

    return 0;
}

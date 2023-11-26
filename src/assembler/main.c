#include <stdio.h>
#include <stdint.h>

#include "include/lexer.h"
#include "include/assembler.h"
#include "include/token.h"
#include "include/utils.h"

int main(int argc, const char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    char* lines[PRGM_MEM_SIZE];

    char line[MAX_STRING_SIZE];
    int instruction_idx = 0;
    while (fgets(line, sizeof(line), file)) {
        if (str_ends_with(line, "\r\n")) {
            strcpy(line, strtok(line, "\r\n"));
        }

        lines[instruction_idx] = malloc(MAX_STRING_SIZE);
        strcpy(lines[instruction_idx], line);

        instruction_idx++;
    }
    lines[instruction_idx] = NULL;

    fclose(file);

    char* bin_file_path = argv[1];
    strcat(bin_file_path, ".bin");

    FILE* bin_file = fopen(bin_file_path, "w");

    for (int idx = 0; idx < instruction_idx; idx++) {
        token_t* tokens = lexer_lex(lines[idx]);
        char* binary = assembler_assemble(tokens);

        fprintf(bin_file, "%s", binary);
    }

    fclose(bin_file);

    for (int i = 0; i < instruction_idx; i++) {
        free(lines[i]);
    }

    return 0;
}
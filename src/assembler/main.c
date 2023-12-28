#include <stdio.h>
#include <stdint.h>

#include "include/lexer.h"
#include "include/assembler.h"
#include "include/token.h"
#include "include/utils.h"

int main(int argc, const char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    char* bin_file_path = argv[1];
    strcat(bin_file_path, ".bin");

    char* lines[PRGM_MEM_SIZE];
    char line[MAX_STRING_SIZE];
    int instruction_idx = 0;
    while (fgets(line, sizeof(line), file)) {
        #ifdef _WIN32
        const char* newline = "\r\n";
        #elif unix
        const char* newline = "\n";
        #endif

        if (strcmp(line, newline) && line[0] != ';') {
            if (str_ends_with(line, newline)) {
                strcpy(line, strtok(line, newline));
            }

            strtrim(line);

            lines[instruction_idx] = malloc(MAX_STRING_SIZE);
            strcpy(lines[instruction_idx], line);

            instruction_idx++;
        }
    }
    lines[instruction_idx] = NULL;

    FILE* bin_file = fopen(bin_file_path, "w");
    for (int idx = 0; idx < instruction_idx; idx++) {
        token_t* tokens = lexer_lex(lines[idx]);
        char* binary = assembler_assemble(tokens);

        fprintf(bin_file, "%s", binary);
    }

    for (int i = 0; i < instruction_idx; i++) {
        free(lines[i]);
    }

    fclose(file);
    fclose(bin_file);

    return 0;
}
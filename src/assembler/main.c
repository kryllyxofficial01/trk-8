#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <linux/limits.h>

#include "include/lexer.h"
#include "include/assembler.h"
#include "include/token.h"
#include "include/utils.h"

int main(int argc, const char* argv[]) {
    char filepath[PATH_MAX];
    if (!realpath(argv[1], filepath)) {
        printf("\x1b[31mError: Invalid filepath '%s'\x1b[0m\n", argv[1]);
        exit(-1);
    }

    FILE* file = fopen(filepath, "r");

    char* bin_file_path = filepath;
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
    for (int i = 0; i < instruction_idx; i++) {
        token_t* tokens = lexer_lex(lines[i]);
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
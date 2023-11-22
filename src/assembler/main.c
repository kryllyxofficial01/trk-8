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
    uint16_t i = 0;
    while (fgets(line, sizeof(line), file)) {
        lines[i++] = line;
    }
    lines[i] = 0;

    fclose(file);

    char* bin_file_path = argv[1];
    strcat(bin_file_path, ".bin");

    FILE* bin_file = fopen(bin_file_path, "w");

    i = 0;
    while (lines[i] != NULL) {
        token_t* tokens = lexer_lex(lines[i]);
        char* binary = assembler_assemble(tokens);

        fprintf(bin_file, "%s", binary);

        i++;
    }

    fclose(bin_file);

    return 0;
}
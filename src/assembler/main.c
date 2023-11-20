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

    i = 0;
    while (lines[i] != NULL) {
        token_t* tokens = lexer_lex(lines[i]);

        char* binary = assembler_assemble(tokens);

        i++;
    }

    return 0;
}
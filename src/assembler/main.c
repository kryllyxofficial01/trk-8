#include <stdio.h>
#include <stdint.h>

#include "include/lexer.h"
#include "include/assembler.h"
#include "include/token.h"
#include "include/utils.h"

int main(int argc, const char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    char* lines[PRGM_MEM_SIZE];

    char line[2048];
    uint16_t i = 0;
    while (fgets(line, sizeof(line), file)) {
        lines[i++] = line;
    }
    lines[i] = 0;

    i = 0;
    while (lines[i] != NULL) {
        token_t* tokens = lexer_lex(lines[i]);

        i++;
    }

    map_t* opcodes = assembler_get_opcodes();

    printf("%u\n", map_get(opcodes, "sub_reg"));

    return 0;
}
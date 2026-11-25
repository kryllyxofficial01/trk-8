#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to .trk8 file>\n", argv[0]);

        return EXIT_FAILURE;
    }

    trk8_assembly_line_t* lines;
    uint16_t line_count = 0;

    if (!parser_parse_file(argv[1], &lines, &line_count)) {
        fprintf(stderr, "Failed to parse '%s'\n", argv[1]);

        return EXIT_FAILURE;
    }

    for (uint16_t i = 0; i < line_count; i++) {
        printf("%s\n", lines[i].mnemonic);

        for (uint8_t j = 0; j < lines[i].operand_count; j++) {
            printf("'%s'\n", lines[i].operands[j]);
        }

        printf("\n");
    }

    return EXIT_SUCCESS;
}
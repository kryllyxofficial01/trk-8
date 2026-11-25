#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"
#include "include/assembler.h"

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

    trk8_pass1_result_t pass1_result;

    if (!assembler_run_pass1(lines, line_count, 0x0000, &pass1_result)) {
        fprintf(stderr, "Failed to assemble '%s'\n", argv[1]);

        return EXIT_FAILURE;
    }

    for (uint16_t i = 0; i < pass1_result.symbol_table_length; i++) {
        printf(
            "%s -> 0x%04X\n",
            pass1_result.symbol_table[i].name,
            (unsigned int) pass1_result.symbol_table[i].address
        );
    }

    return EXIT_SUCCESS;
}
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
        fprintf(stderr, "Failed to assemble '%s' on first pass\n", argv[1]);

        return EXIT_FAILURE;
    }

    uint8_t* output;
    uint16_t output_byte_count = 0;

    if (!assembler_run_pass2(&pass1_result, &output, &output_byte_count)) {
        fprintf(stderr, "Failed to assemble '%s' on second pass\n", argv[1]);

        return EXIT_FAILURE;
    }

    for (uint16_t i = 0; i < output_byte_count; i++) {
        printf("0x%02x\n", output[i]);
    }

    free(output);

    return EXIT_SUCCESS;
}
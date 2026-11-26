#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "include/parser.h"
#include "include/assembler.h"

static bool output_to_binary(const char* filepath, const uint8_t* bytes, uint16_t byte_count) {
    if (!filepath || !bytes || byte_count < 0) {
        return false;
    }

    FILE* file = fopen(filepath, "wb");

    if (!file) {
        fprintf(stderr, "error: unable to open output file '%s'\n", filepath);

        return false;
    }

    if (fwrite(bytes, 1, byte_count, file) != byte_count) {
        fprintf(stderr, "error: unable to write program to output file '%s'\n", filepath);

        fclose(file);

        return false;
    }

    fclose(file);

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <path to input (.trk8) file> <path to output file>\n", argv[0]);

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

    if (!output_to_binary(argv[2], output, output_byte_count)) {
        fprintf(stderr, "Failed to write binary to output file\n", argv[1]);

        return EXIT_FAILURE;
    }

    free(output);

    return EXIT_SUCCESS;
}
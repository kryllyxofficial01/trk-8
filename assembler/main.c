#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path to .trk8 file>\n", argv[0]);

        return EXIT_FAILURE;
    }

    trk8_assembly_line_t* lines;

    if (!parser_parse(argv[1], &lines)) {
        fprintf(stderr, "Failed to parse '%s'\n", argv[1]);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
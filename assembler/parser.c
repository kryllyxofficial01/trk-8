#include "include/parser.h"

bool parser_parse(const char* filepath, trk8_assembly_line_t** lines, uint16_t* line_count) {
    FILE* file = fopen(filepath, "r");

    if (!file) {
        return false;
    }

    trk8_assembly_line_t* assembly_lines;

    char buffer[TRK8_INSTRUCTION_MAX_LENGTH];

    char* token;

    while (fgets(buffer, sizeof(buffer), file)) {
        trim(buffer);

        trk8_assembly_line_t line;

        line.operand_count = 0;

        char* line_string = buffer;

        size_t token_index = 0;

        while ((token = strsep(&line_string, " "))) {
            if (token_index == 0) {
                line.mnemonic = token;
            }
            else {
                line.operands[line.operand_count++] = token;
            }

            token_index++;
        }

        (*line_count)++;
    }

    for (unsigned int i = 0; i < *line_count; i++) {
        printf("'%s', %u\n", assembly_lines[i].mnemonic, assembly_lines[i].operand_count);
    }

    fclose(file);

    *lines = assembly_lines;

    return true;
}
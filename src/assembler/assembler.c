#include "include/assembler.h"

char* assembler_assemble(token_t* tokens) {
    char* binary = calloc(sizeof(char) * MAX_STRING_SIZE, 1);

    int i = 0;
    char* bin;
    while (tokens[i].type != EOL) {
        if (tokens[i].type == ID) {
            map_t* opcodes = assembler_get_opcodes();
            map_t* variant_offsets = assembler_get_variant_offsets();

            char* mnemonic = tokens[i].value;
            if (is_str_contained(HAS_VARIANTS, tokens[i].value)) {
                int offset = map_get(variant_offsets, tokens[i].value);
                switch (tokens[i + offset].type) {
                    case REGISTER: strcat(mnemonic, "_reg"); break;
                    case IMM8:
                    case IMM16: strcat(mnemonic, "_imm"); break;
                }
            }
            else if (!is_str_contained(MNEMONICS, tokens[i].value)) {
                printf("Invalid instruction: '%s'\n", tokens[i].value);
                exit(-1);
            }

            bin = to_binary(map_get(opcodes, mnemonic), 8);
        }
        else if (tokens[i].type == REGISTER) {
            map_t* register_ids = assembler_get_register_ids();

            if (is_str_contained(REGISTERS, tokens[i].value)) {
                bin = to_binary(
                    map_get(register_ids, tokens[i].value), 8
                );
            }
            else {
                printf("Invalid register ID: '%s'\n", tokens[i].value);
                exit(-1);
            }
        }
        else if (tokens[i].type == IMM8) {
            bin = tokens[i].value;

            int missing_bits = 8 - strlen(bin);
            for (int _i = 0; _i < missing_bits; _i++) {
                strins(bin, "0", 0);
            }

            strins(bin, "00000000\n", 0);
        }
        else if (tokens[i].type == IMM16) {
            bin = tokens[i].value;

            int missing_bits = 16 - strlen(bin);
            for (int _i = 0; _i < missing_bits; _i++) {
                strins(bin, "0", 0);
            }

            strins(bin, "\n", 8);
        }

        if (strlen(bin) < 8) {
            int missing_bits = 8 - strlen(bin);
            for (int _i = 0; _i < missing_bits; _i++) {
                strins(bin, "0", 0);
            }
        }

        strcat(binary, bin);
        strcat(binary, "\n");

        i++;
    }

    return binary;
}

map_t* assembler_get_opcodes() {
    map_t* opcodes = map_init();

    int i = 0;
    while (MNEMONICS[i] != NULL) {
        map_insert(opcodes, MNEMONICS[i], i);

        i++;
    }

    return opcodes;
}

map_t* assembler_get_register_ids() {
    map_t* register_ids = map_init();

    int i = 0;
    while (REGISTERS[i] != NULL) {
        map_insert(register_ids, REGISTERS[i], i);

        i++;
    }

    return register_ids;
}

map_t* assembler_get_variant_offsets() {
    map_t* variant_offsets = map_init();

    map_insert(variant_offsets, "mov", 2);

    map_insert(variant_offsets, "lda", 1);

    map_insert(variant_offsets, "stb", 1);
    map_insert(variant_offsets, "ldb", 2);

    map_insert(variant_offsets, "push", 1);

    map_insert(variant_offsets, "add", 2);
    map_insert(variant_offsets, "sub", 2);
    map_insert(variant_offsets, "mul", 2);
    map_insert(variant_offsets, "div", 2);

    map_insert(variant_offsets, "and", 2);
    map_insert(variant_offsets, "or", 2);
    map_insert(variant_offsets, "xor", 2);

    map_insert(variant_offsets, "cmp", 2);
}

map_t* assembler_get_label_locations(char** lines) {
    map_t* label_locations = map_init();

    int i = 0;
    while (lines[i] != NULL) {
        if (lines[i][0] == '.') {
            char label_name[MAX_STRING_SIZE];

            strncpy(label_name, lines[i] + 1, strlen(lines[i]) - 1);

            map_insert(label_locations, label_name, i);
        }

        i++;
    }

    return label_locations;
}
#include "include/assembler.h"

trk8_instruction_byte_info_t byte_counts[TRK8_INSTRUCTIONS_COUNT] = {
    { .mnemonic = "nop", .byte_count = 1 },
    { .mnemonic = "mov", .byte_count = 2 },
    { .mnemonic = "lda", .byte_count = 3 },
    { .mnemonic = "stb", .byte_count = 2 },
    { .mnemonic = "ldb", .byte_count = 2 },
    { .mnemonic = "push", .byte_count = 2 },
    { .mnemonic = "pop", .byte_count = 2 },
    { .mnemonic = "adc", .byte_count = 1 },
    { .mnemonic = "and", .byte_count = 1 },
    { .mnemonic = "or", .byte_count = 1 },
    { .mnemonic = "not", .byte_count = 1 },
    { .mnemonic = "cmp", .byte_count = 1 },
    { .mnemonic = "jmp", .byte_count = 1 },
    { .mnemonic = "bne", .byte_count = 1 },
    { .mnemonic = "bca", .byte_count = 1 },
    { .mnemonic = "bze", .byte_count = 1 },
    { .mnemonic = "hlt", .byte_count = 1 }
};

static uint8_t get_instruction_byte_count(const trk8_assembly_line_t line) {
    if (!line.mnemonic) {
        return 0;
    }

    for (uint8_t i = 0; i < TRK8_INSTRUCTIONS_COUNT; i++) {
        if (strcmp(byte_counts[i].mnemonic, line.mnemonic) == 0) {
            return byte_counts[i].byte_count;
        }
    }

    return 0;
}

static bool add_symbol_table_entry(trk8_symbol_t** table, uint16_t* table_length, uint16_t* table_capacity, const trk8_symbol_t symbol) {
    if (!symbol.name) {
        return false;
    }

    for (uint16_t i = 0; i < *table_length; i++) {
        if (strcmp((*table)[i].name, symbol.name) == 0) {
            fprintf(stderr, "error: duplicate symbol '%s'\n", symbol.name);

            return false;
        }
    }

    if (*table_length == *table_capacity) {
        if (*table_capacity == UINT16_MAX) {
            return false;
        }

        uint16_t new_capacity = (*table_capacity == 0) ? 16 : (
            (*table_capacity > UINT16_MAX / 2) ? UINT16_MAX : (uint16_t) (*table_capacity * 2)
        );

        trk8_symbol_t* new_table = realloc(*table, (size_t) new_capacity * sizeof(trk8_symbol_t));

        if (!new_table) {
            return false;
        }

        *table = new_table;

        *table_capacity = new_capacity;
    }

    size_t symbol_name_length = strlen(symbol.name);

    char* symbol_name_copy = malloc(symbol_name_length + 1);

    if (!symbol_name_copy) {
        return false;
    }

    memcpy(symbol_name_copy, symbol.name, symbol_name_length + 1);

    (*table)[*table_length].name = symbol_name_copy;
    (*table)[*table_length].address = symbol.address;

    (*table_length)++;

    return true;
}

bool assembler_run_pass1(trk8_assembly_line_t* lines, const uint16_t line_count, const uint16_t origin_address, trk8_pass1_result_t* pass1_result) {
    if (!pass1_result || (!lines && line_count > 0)) {
        return false;
    }

    memset(pass1_result, 0, sizeof(*pass1_result));

    uint16_t ir_capacity = 0;
    uint16_t symbol_table_capacity = 0;

    uint16_t location_counter = origin_address;

    for (uint16_t i = 0; i < line_count; i++) {
        trk8_assembly_line_t* line = &lines[i];

        if (!line->mnemonic) {
            continue;
        }

        size_t mnemonic_length = strlen(line->mnemonic);

        if (mnemonic_length > 1 && line->mnemonic[mnemonic_length - 1] == ':' && line->operand_count == 0) {
            char label_name[TRK8_MAX_BUFFER_LENGTH];

            if (mnemonic_length - 1 >= sizeof(label_name)) {
                assembler_free_pass1_result(pass1_result);

                return false;
            }

            memcpy(label_name, line->mnemonic, mnemonic_length - 1);

            label_name[mnemonic_length - 1] = '\0';

            trk8_symbol_t label_symbol = (trk8_symbol_t) {
                .name = label_name,
                .address = location_counter
            };

            if (!add_symbol_table_entry(&pass1_result->symbol_table, &pass1_result->symbol_table_length, &symbol_table_capacity, label_symbol)) {
                assembler_free_pass1_result(pass1_result);

                return false;
            }

            continue;
        }

        if (pass1_result->ir_line_count == ir_capacity) {
            if (ir_capacity == UINT16_MAX) {
                assembler_free_pass1_result(pass1_result);

                return false;
            }

            uint16_t new_capacity = (ir_capacity == 0) ? 16 : (
                (ir_capacity > UINT16_MAX / 2) ? UINT16_MAX : (uint16_t) (ir_capacity * 2)
            );

            trk8_ir_line_t* new_ir_lines = realloc(pass1_result->ir_lines, (size_t) new_capacity * sizeof(*new_ir_lines));

            if (!new_ir_lines) {
                assembler_free_pass1_result(pass1_result);

                return false;
            }

            pass1_result->ir_lines = new_ir_lines;

            ir_capacity = new_capacity;
        }

        uint8_t byte_count = get_instruction_byte_count(*line);

        if (byte_count == 0) {
            fprintf(stderr, "error: unknown mnemonic '%s'\n", line->mnemonic);

            assembler_free_pass1_result(pass1_result);

            return false;
        }

        if (location_counter > UINT16_MAX - byte_count) {
            fprintf(stderr, "error: address overflow\n");

            assembler_free_pass1_result(pass1_result);

            return false;
        }

        pass1_result->ir_lines[pass1_result->ir_line_count].address = location_counter;
        pass1_result->ir_lines[pass1_result->ir_line_count].byte_count = byte_count;
        pass1_result->ir_lines[pass1_result->ir_line_count].source = line;

        pass1_result->ir_line_count++;

        location_counter = (uint16_t) (location_counter + byte_count);
    }

    return true;
}

void assembler_free_pass1_result(trk8_pass1_result_t* pass1_result) {
    if (!pass1_result) {
        return;
    }

    free(pass1_result->ir_lines);

    pass1_result->ir_lines = NULL;
    pass1_result->ir_line_count = 0;

    for (uint16_t i = 0; i < pass1_result->symbol_table_length; i++) {
        free(pass1_result->symbol_table[i].name);
    }

    free(pass1_result->symbol_table);

    pass1_result->symbol_table = NULL;
    pass1_result->symbol_table_length = 0;
}
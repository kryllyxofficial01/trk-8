#include "include/assembler.h"

trk8_instruction_info_t instructions_info[TRK8_INSTRUCTIONS_COUNT] = {
    { .mnemonic = "nop", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 1 },
    { .mnemonic = "mov", .byte_count = 2, .category = TRK8_INSTRUCTION_CATEGORY_TWO_OPERANDS, .category_internal_index = 0 },
    { .mnemonic = "lda", .byte_count = 3, .category = TRK8_INSTRUCTION_CATEGORY_HAS_16BIT_OPERAND, .category_internal_index = 0 },
    { .mnemonic = "stb", .byte_count = 2, .category = TRK8_INSTRUCTION_CATEGORY_ONE_OPERAND, .category_internal_index = 0 },
    { .mnemonic = "ldb", .byte_count = 2, .category = TRK8_INSTRUCTION_CATEGORY_ONE_OPERAND, .category_internal_index = 1 },
    { .mnemonic = "push", .byte_count = 2, .category = TRK8_INSTRUCTION_CATEGORY_ONE_OPERAND, .category_internal_index = 2 },
    { .mnemonic = "pop", .byte_count = 2, .category = TRK8_INSTRUCTION_CATEGORY_ONE_OPERAND, .category_internal_index = 3 },
    { .mnemonic = "adc", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 2 },
    { .mnemonic = "and", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 3 },
    { .mnemonic = "or", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 4 },
    { .mnemonic = "not", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 5 },
    { .mnemonic = "cmp", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 6 },
    { .mnemonic = "jmp", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 7 },
    { .mnemonic = "bne", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 8 },
    { .mnemonic = "bca", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 9 },
    { .mnemonic = "bze", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 10 },
    { .mnemonic = "hlt", .byte_count = 1, .category = TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS, .category_internal_index = 11 }
};

trk8_register_index_t register_indices[TRK8_REGISTERS_COUNT] = {
    { .symbolic_name = "a", .index = 0 },
    { .symbolic_name = "b", .index = 1 },
    { .symbolic_name = "c", .index = 2 },
    { .symbolic_name = "x", .index = 3 },
    { .symbolic_name = "sp", .index = 4 },
    { .symbolic_name = "f", .index = 5 },
    { .symbolic_name = "al", .index = 6 },
    { .symbolic_name = "ah", .index = 7 },
    { .symbolic_name = "pcl", .index = 8 },
    { .symbolic_name = "pch", .index = 9 }
};

static uint8_t get_instruction_byte_count(const trk8_assembly_line_t line) {
    if (!line.mnemonic) {
        return 0;
    }

    for (uint8_t i = 0; i < TRK8_INSTRUCTIONS_COUNT; i++) {
        if (strcmp(instructions_info[i].mnemonic, line.mnemonic) == 0) {
            return instructions_info[i].byte_count;
        }
    }

    return 0;
}

static uint8_t get_register_index(const char* register_name) {
    for (uint8_t i = 0; i < TRK8_REGISTERS_COUNT; i++) {
        if (strcmp(register_indices[i].symbolic_name, register_name) == 0) {
            return register_indices[i].index;
        }
    }

    return -1;
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

static bool process_operand(const char* operand, trk8_operand_type_t* operand_type, uint16_t* value) {
    switch (*operand) {
        case '%': {
            operand++;

            *operand_type = TRK8_OPERAND_TYPE_REGISTER;

            *value = get_register_index(operand);

            break;
        }

        case '!': {
            operand++;

            int base = 10;

            if (operand[0] == '0') {
                if (tolower(operand[1]) == 'b') {
                    base = 2;

                    operand += 2;
                }
                else if (tolower(operand[1]) == 'x') {
                    base = 16;

                    operand += 2;
                }
                else {
                    return false;
                }
            }

            errno = 0;

            char* end;

            unsigned long raw_value = strtoul(operand, &end, base);

            if (end == operand || *end != '\0' || errno == ERANGE) {
                return false;
            }

            if (raw_value <= UINT8_MAX) {
                *operand_type = TRK8_OPERAND_TYPE_IMM8;

                *value = (uint8_t) raw_value;
            }
            else if (raw_value > UINT8_MAX) {
                *operand_type = TRK8_OPERAND_TYPE_IMM16;

                *value = (uint16_t) raw_value;
            }

            break;
        }
    }

    return true;
}

static bool convert_to_bytecode(const trk8_assembly_line_t line, trk8_symbol_t* symbol_table, const uint16_t symbol_table_length, uint8_t** bytecode, uint8_t* byte_count) {
    trk8_instruction_info_t instruction_info;

    for (uint8_t i = 0; i < TRK8_INSTRUCTIONS_COUNT; i++) {
        if (strcmp(instructions_info[i].mnemonic, line.mnemonic) == 0) {
            instruction_info = instructions_info[i];

            break;
        }
    }

    if (instruction_info.category != line.operand_count) {
        fprintf(stderr, "error: mismatching operand count\n");

        return false;
    }

    for (uint8_t i = 0; i < TRK8_INSTRUCTIONS_MAX_BYTE_COUNT; i++) {
        (*bytecode)[i] = 0;
    }

    *byte_count = 1;

    switch (instruction_info.category) {
        case TRK8_INSTRUCTION_CATEGORY_NO_OPERANDS: {
            (*bytecode)[0] = instruction_info.category_internal_index;

            break;
        }

        case TRK8_INSTRUCTION_CATEGORY_ONE_OPERAND: {
            trk8_operand_type_t operand_type;
            uint16_t operand_value = 0;

            if (!process_operand(line.operands[0], &operand_type, &operand_value)) {
                fprintf(stderr, "error: unable to process operand '%s'\n", line.operands[0]);

                return false;
            }

            uint8_t register_index = (operand_type == TRK8_OPERAND_TYPE_REGISTER) ? operand_value : TRK8_ONE_OPERAND_INSTRUCTION_HAS_IMMEDIATE;

            (*bytecode)[0] = (instruction_info.category << 6) | (instruction_info.category_internal_index << 4) | register_index;

            if (register_index == TRK8_ONE_OPERAND_INSTRUCTION_HAS_IMMEDIATE) {
                (*bytecode)[1] = (uint8_t) operand_value;
            }
            else {
                (*bytecode)[1] = TRK8_PADDING_BYTE;
            }

            (*byte_count)++;

            break;
        }

        case TRK8_INSTRUCTION_CATEGORY_TWO_OPERANDS: {
            trk8_operand_type_t first_operand_type;
            uint16_t first_operand_value = 0;

            if (!process_operand(line.operands[0], &first_operand_type, &first_operand_value)) {
                fprintf(stderr, "error: unable to process operand '%s'\n", line.operands[0]);

                return false;
            }

            if (first_operand_type != TRK8_OPERAND_TYPE_REGISTER) {
                fprintf(stderr, "error: first operand must be a register\n");
            }

            trk8_operand_type_t second_operand_type;
            uint16_t second_operand_value = 0;

            if (!process_operand(line.operands[1], &second_operand_type, &second_operand_value)) {
                fprintf(stderr, "error: unable to process operand '%s'\n", line.operands[0]);

                return false;
            }

            (*bytecode)[0] = (instruction_info.category << 6) | (instruction_info.category_internal_index << 5) | (first_operand_value << 1) | (second_operand_type != TRK8_OPERAND_TYPE_REGISTER);
            (*bytecode)[1] = (uint8_t) second_operand_value;

            (*byte_count)++;

            break;
        }

        case TRK8_INSTRUCTION_CATEGORY_HAS_16BIT_OPERAND: {
            break;
        }
    }

    return true;
}

static bool append_bytes(uint8_t** buffer, uint16_t* buffer_length, uint16_t* buffer_capacity, const uint8_t* bytes, uint16_t byte_count) {
    if (*buffer_length + byte_count > *buffer_capacity) {
        if (*buffer_capacity == UINT16_MAX) {
            return false;
        }

        uint16_t new_capacity = (*buffer_capacity == 0) ? 16 : (
            (*buffer_capacity > UINT16_MAX / 2) ? UINT16_MAX : (uint16_t) (*buffer_capacity * 2)
        );

        uint8_t* new_buffer = realloc(*buffer, (size_t) new_capacity * sizeof(uint8_t));

        if (!new_buffer) {
            return false;
        }

        *buffer = new_buffer;

        *buffer_capacity = new_capacity;
    }

    memcpy(*buffer + *buffer_length, bytes, byte_count);

    *buffer_length += byte_count;

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

bool assembler_run_pass2(trk8_pass1_result_t* pass1_result, uint8_t** output, uint16_t* output_byte_count) {
    if (!pass1_result || !output || !output_byte_count) {
        return false;
    }

    *output = NULL;
    *output_byte_count = 0;

    uint8_t* program = NULL;

    uint16_t program_length = 0;
    uint16_t program_capacity = 0;

    for (uint16_t i = 0; i < pass1_result->ir_line_count; i++) {
        trk8_ir_line_t* ir = &pass1_result->ir_lines[i];

        uint8_t* bytes = calloc(TRK8_INSTRUCTIONS_MAX_BYTE_COUNT, sizeof(uint8_t));
        uint8_t byte_count = 0;

        if (!convert_to_bytecode(*ir->source, pass1_result->symbol_table, pass1_result->symbol_table_length, &bytes, &byte_count)) {
            free(program);

            free(bytes);

            return false;
        }

        if (!append_bytes(&program, &program_length, &program_capacity, bytes, byte_count)) {
            free(program);

            free(bytes);

            return false;
        }

        free(bytes);
    }

    *output = program;
    *output_byte_count = program_length;

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
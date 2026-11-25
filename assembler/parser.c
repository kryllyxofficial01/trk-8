#include "include/parser.h"

static char* duplicate_string_span(const char* span_start, const char* span_end) {
    while (span_start < span_end && isspace((unsigned char) *span_start)) {
        span_start++;
    }

    while (span_end > span_start && isspace((unsigned char) *(span_end - 1))) {
        span_end--;
    }

    size_t length = (size_t) (span_end - span_start);

    char* copy = malloc(length + 1);

    if (!copy) {
        return NULL;
    }

    if (length > 0) {
        memcpy(copy, span_start, length);
    }

    copy[length] = '\0';

    return copy;
}

static bool add_operand(trk8_assembly_line_t* line, const char* span_start, const char* span_end) {
    char* operand = duplicate_string_span(span_start, span_end);

    if (!operand) {
        return false;
    }

    if (*operand == '\0') {
        free(operand);

        return true;
    }

    if (line->operand_count >= TRK8_INSTRUCTION_MAX_OPERANDS) {
        fprintf(stderr, "error: extra operand '%s'\n", operand);

        free(operand);

        return false;
    }

    line->operands[line->operand_count++] = operand;

    return true;
}

static void free_asm_line(trk8_assembly_line_t* line) {
    if (!line) {
        return;
    }

    free(line->mnemonic);

    line->mnemonic = NULL;

    for (uint8_t i = 0; i < line->operand_count; i++) {
        free(line->operands[i]);

        line->operands[i] = NULL;
    }

    line->operand_count = 0;
}

static void free_asm_lines(trk8_assembly_line_t* lines, uint16_t count) {
    if (!lines) {
        return;
    }

    for (uint16_t i = 0; i < count; i++) {
        free_asm_line(&lines[i]);
    }

    free(lines);
}

static bool parse_line(const char* line, trk8_assembly_line_t* asm_line, bool* has_content) {
    memset(asm_line, 0, sizeof(*asm_line));

    *has_content = false;

    const char* line_start = line;
    const char* comment_start = strchr(line, ';');
    const char* line_end = comment_start ? comment_start : (line + strlen(line));

    while (line_start < line_end && isspace((unsigned char) *line_start)) {
        line_start++;
    }

    while (line_end > line_start && isspace((unsigned char) *(line_end - 1))) {
        line_end--;
    }

    if (line_start >= line_end) {
        return true;
    }

    const char* scan_ptr = line_start;

    while (scan_ptr < line_end && !isspace((unsigned char) *scan_ptr)) {
        scan_ptr++;
    }

    asm_line->mnemonic = duplicate_string_span(line_start, scan_ptr);

    to_lowercase(asm_line->mnemonic);

    if (!asm_line->mnemonic) {
        free_asm_line(asm_line);

        return false;
    }

    *has_content = true;

    while (scan_ptr < line_end && isspace((unsigned char) *scan_ptr)) {
        scan_ptr++;
    }

    if (scan_ptr >= line_end) {
        return true;
    }

    const char* operand_start = scan_ptr;

    while (scan_ptr < line_end) {
        if (*scan_ptr == ',') {
            if (!add_operand(asm_line, operand_start, scan_ptr)) {
                free_asm_line(asm_line);

                return false;
            }

            operand_start = scan_ptr + 1;
        }

        scan_ptr++;
    }

    if (!add_operand(asm_line, operand_start, line_end)) {
        free_asm_line(asm_line);

        return false;
    }

    return true;
}

bool parser_parse_file(const char* filepath, trk8_assembly_line_t** lines, uint16_t* line_count) {
    if (!filepath || !lines || !line_count) {
        return false;
    }

    *lines = NULL;
    *line_count = 0;

    FILE* file = fopen(filepath, "r");

    if (!file) {
        return false;
    }

    uint16_t capacity = 0;

    trk8_assembly_line_t* parsed_lines = NULL;
    uint16_t parsed_count = 0;

    char buffer[TRK8_MAX_BUFFER_LENGTH];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        trk8_assembly_line_t current_line;

        bool has_content = false;

        if (!parse_line(buffer, &current_line, &has_content)) {
            free_asm_lines(parsed_lines, parsed_count);

            fclose(file);

            return false;
        }

        if (!has_content) {
            continue;
        }

        if (parsed_count == capacity) {
            if (capacity == UINT16_MAX) {
                free_asm_line(&current_line);

                free_asm_lines(parsed_lines, parsed_count);

                fclose(file);

                return false;
            }

            uint16_t new_capacity = (capacity == 0) ? 16 : (
                (capacity > UINT16_MAX / 2) ? UINT16_MAX : (uint16_t) (capacity * 2)
            );

            trk8_assembly_line_t* new_lines = realloc(
                parsed_lines,
                (size_t) new_capacity * sizeof(*new_lines)
            );

            if (!new_lines) {
                free_asm_line(&current_line);

                free_asm_lines(parsed_lines, parsed_count);

                fclose(file);

                return false;
            }

            parsed_lines = new_lines;

            capacity = new_capacity;
        }

        parsed_lines[parsed_count++] = current_line;
    }

    if (ferror(file)) {
        free_asm_lines(parsed_lines, parsed_count);

        fclose(file);

        return false;
    }

    fclose(file);

    *lines = parsed_lines;
    *line_count = parsed_count;

    return true;
}
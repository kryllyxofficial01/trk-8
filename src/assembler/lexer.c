#include "include/lexer.h"

token_t* lexer_lex(char* line) {
    token_t* tokens = malloc(sizeof(struct TOKEN) * MAX_TOKENS);

    uint8_t token_idx = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (!isspace(line[i])) {
            if (line[i] == '@') {
                tokens[token_idx] = lexer_get_register(line, &i);
            }
            else if (isdigit(line[i]) || strchr(BASE_PREFIXES, line[i])) {
                tokens[token_idx] = lexer_get_immediate(line, &i);
            }
            else {
                tokens[token_idx] = lexer_get_id(line, &i);
            }

            token_idx++;
        }
    }

    token_t eol_token;

    eol_token.type = EOL;
    strcpy(eol_token.value, "\0");

    tokens[token_idx] = eol_token;

    return tokens;
}

token_t lexer_get_id(char* line, int* index) {
    token_t token;

    char id[MAX_STRING_SIZE] = "";
    while (isalnum(line[*index])) {
        strncat(id, &line[*index], 1);

        (*index)++;
    }

    *index--;

    token.type = ID;
    strcpy(token.value, id);

    return token;
}

token_t lexer_get_register(char* line, int* index) {
    token_t token;

    (*index)++;

    char register_id[MAX_STRING_SIZE] = "";
    while (isalnum(line[*index])) {
        strncat(register_id, &line[*index], 1);

        (*index)++;
    }

    *index--;

    token.type = REGISTER;
    strcpy(token.value, register_id);

    return token;
}

token_t lexer_get_immediate(char* line, int* index) {
    token_t token;

    char* binary = "";

    char number[MAX_STRING_SIZE] = "";
    if (isdigit(line[*index])) {
        while (isdigit(line[*index])) {
            strncat(number, &line[*index], 1);

            (*index)++;
        }

        unsigned int value = atoi(number);

        if (value > UINT8_MAX) {

        }

        int length;
        if (value <= UINT8_MAX) length = 8;
        else if (value <= UINT16_MAX) length = 16;

        binary = to_binary(value, length);
    }
    else if (strchr(BASE_PREFIXES, line[*index])) {
        (*index)++;

        if (line[*index - 1] == '%') {
            while (strchr(VALID_BIN, line[*index])) {
                strncat(number, &line[*index], 1);

                (*index)++;
            }

            binary = to_binary(strtol(number, NULL, 2), 8);
        }
        else if (line[*index - 1] == '#') {
            while (isxdigit(line[*index])) {
                strncat(number, &line[*index], 1);

                (*index)++;
            }

            unsigned int value = strtol(number, NULL, 16);

            int length;
            if (value <= UINT8_MAX) length = 8;
            else if (value <= UINT16_MAX) length = 16;

            binary = to_binary(value, length);
        }
    }

    *index--;

    if (strlen(binary) <= 8) token.type = IMM8;
    else if (strlen(binary) <= 16) token.type = IMM16;

    strcpy(token.value, binary);

    return token;
}
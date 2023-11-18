#include "include/lexer.h"

token_t* lexer_lex(char* line) {
    token_t* tokens = malloc(sizeof(struct TOKEN) * MAX_TOKENS);

    uint8_t token_idx = 0;
    for (int i = 0; i <= strlen(line); i++) {
        if (line[i] == '@') {
             tokens[token_idx] = lexer_get_register(line, &i);
        }
        else if (isdigit(line[i]) || strchr(BASE_PREFIXES, line[i])) {
            tokens[token_idx] = lexer_get_immediate(line, &i);
        }
        else if (!isspace(line[i])) {
            tokens[token_idx] = lexer_get_id(line, &i);
        }
        else {
            token_idx--;
        }

        token_idx++;
    }

    return tokens;
}

token_t lexer_get_id(char* line, int* index) {
    char id[2048];

    uint16_t i = 0;
    while (isalnum(line[*index])) {
        id[i] = line[(*index)++];

        i++;
    }

    *index--;

    token_t token;

    token.type = ID;
    strcpy(token.value, id);

    return token;
}

token_t lexer_get_register(char* line, int* index) {
    char register_id[5];

    (*index)++;

    uint16_t i = 0;
    while (isalnum(line[*index])) {
        register_id[i] = line[(*index)++];

        i++;
    }

    *index--;

    token_t token;

    token.type = REGISTER;
    strcpy(token.value, register_id);

    return token;
}

token_t lexer_get_immediate(char* line, int* index) {
    char immediate[8];

    char number[2048];
    int i = 0;
    if (isdigit(line[*index])) {
        while (isdigit(line[*index])) {
            number[i] = line[(*index)++];

            i++;
        }

        strcpy(immediate, to_binary(atoi(number)));
    }
    else if (strchr(BASE_PREFIXES, line[*index])) {
        (*index)++;

        if (line[*index-1] == '%') {
            while (strchr(VALID_BIN, line[*index])) {
                number[i] = line[(*index)++];

                i++;
            }

            strcpy(immediate, number);
        }
        else if (line[*index-1] == '#') {
            while (strchr(VALID_HEX, tolower(line[*index]))) {
                number[i] = line[(*index)++];

                i++;
            }

            strcpy(immediate, to_binary(strtol(number, NULL, 16)));
        }
    }

    token_t token;

    token.type = IMM8;
    strcpy(token.value, immediate);

    return token;
}
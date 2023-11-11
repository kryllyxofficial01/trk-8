#include "include/lexer.h"

token_t* lexer_lex(char* line) {
    token_t* tokens = malloc(sizeof(struct TOKEN) * MAX_TOKENS);

    uint8_t token_idx = 0;
    for (int i = 0; i <= get_length(line, char); i++) {
        if (line[i] == '@') {
            tokens[token_idx] = lexer_get_register(line, &i);
            token_idx++;
        }
        else if (!isspace(line[i])) {
            tokens[token_idx] = lexer_get_id(line, &i);
            token_idx++;
        }
    }

    return tokens;
}

token_t lexer_get_id(char* line, int* index) {
    char* id = malloc(sizeof(char) * 2048);

    uint16_t i = 0;
    while (isalnum(line[*index])) {
        id[i] = line[(*index)++];

        i++;
    }

    *index--;

    return (token_t) {
        .type = ID,
        .value = id
    };
}

token_t lexer_get_register(char* line, int* index) {
    char* register_id = malloc(sizeof(char) * 5);

    (*index)++;

    uint16_t i = 0;
    while (isalnum(line[*index])) {
        register_id[i] = line[(*index)++];

        i++;
    }

    *index--;

    return (token_t) {
        .type = REGISTER,
        .value = register_id
    };
}
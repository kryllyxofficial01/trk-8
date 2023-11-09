#include "include/lexer.h"

token_t* lexer_lex(char* line) {
    token_t* tokens = malloc(sizeof(struct TOKEN) * MAX_TOKENS);

    uint8_t token_idx = 0;
    for (int i = 0; i < get_length(line, char); i++) {
        tokens[token_idx] = lexer_get_pneumonic(line, &i);
        token_idx++;
    }

    return tokens;
}

token_t lexer_get_pneumonic(char* line, int* index) {
    char* pnuemonic = malloc(sizeof(char) * 2048);

    uint16_t i = 0;
    while (line[*index] != ' ') {
        pnuemonic[i] = line[(*index)++];

        i++;
    }

    *index--;

    return (token_t) {
        .type = PNEUMONIC,
        .value = pnuemonic
    };
}
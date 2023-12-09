#ifndef __TOKEN_H
#define __TOKEN_H

#include "utils.h"

#define MAX_TOKENS 5

enum token_types {
    ID,
    REGISTER,
    IMM8,
    IMM16,
    EOL
};

typedef struct TOKEN {
    enum token_types type;
    char value[MAX_STRING_SIZE];
} token_t;

#endif
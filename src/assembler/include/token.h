#ifndef __TOKEN_H
#define __TOKEN_H

enum token_types {
    ID,
    REGISTER,
    IMM8
};

typedef struct TOKEN {
    enum token_types type;
    const char* value;
} token_t;

#endif
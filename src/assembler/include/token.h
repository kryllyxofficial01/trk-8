#ifndef __TOKEN_H
#define __TOKEN_H

enum token_types {
    PNEUMONIC,
    IMM8,
    ADDRESS
};

typedef struct TOKEN {
    enum token_types type;
    const char* value;
} token_t;

#endif
#ifndef __LEXER_H
#define __LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "token.h"
#include "utils.h"

token_t* lexer_lex(char* line);
token_t lexer_get_pneumonic(char* line, int* index);

#endif
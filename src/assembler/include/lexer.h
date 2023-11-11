#ifndef __LEXER_H
#define __LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "token.h"
#include "utils.h"

token_t* lexer_lex(char* line);
token_t lexer_get_id(char* line, int* index);
token_t lexer_get_register(char* line, int* index);

#endif
#ifndef __LEXER_H
#define __LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "token.h"
#include "utils.h"

#define BASE_PREFIXES "#%%"

#define VALID_BIN "01"

token_t* lexer_lex(char* line);
token_t lexer_get_id(char* line, int* index);
token_t lexer_get_register(char* line, int* index);
token_t lexer_get_immediate(char* line, int* index);

#endif
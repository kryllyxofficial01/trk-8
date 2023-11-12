#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TOKENS 5
#define PRGM_MEM_SIZE 0x8000

#define BASE_PREFIXES "#%%"

#define VALID_BIN "01"
#define VALID_HEX "0123456789abcdef"

char* to_binary(uint8_t number);
void strins(char* destination, const char* source, int position);

#endif
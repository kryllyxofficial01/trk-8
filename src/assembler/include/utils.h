#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRGM_MEM_SIZE 0x8000
#define MAX_STRING_SIZE 2048

char* to_binary(uint8_t number);
void strins(char* destination, const char* source, int position);
bool is_str_contained(const char** array, const char* string);

#endif
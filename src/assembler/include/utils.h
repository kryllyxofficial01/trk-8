#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define PRGM_MEM_SIZE 0x8000
#define MAX_STRING_SIZE 2048
#define BLOCK_SIZE 1024

char* to_binary(unsigned int number, int length);
bool is_str_contained(const char** array, const char* string);
bool str_ends_with(const char* string, const char* substring);

void strins(char* destination, const char* source, int position);
void strtrim(char* string);
#endif
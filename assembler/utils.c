#include "include/utils.h"

void to_lowercase(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = tolower((unsigned char)string[i]);
    }
}
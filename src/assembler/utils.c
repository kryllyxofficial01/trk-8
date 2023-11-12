#include "include/utils.h"

// Credit: https://cs.stackexchange.com/a/10321
char* to_binary(uint8_t number) {
    char* binary = malloc(sizeof(char) * 8);

    while (number > 0) {
        char num_str[8];
        sprintf(num_str, "%u", number % 2);

        strins(binary, num_str, 0);

        number = floor(number / 2);
    }

    return binary;
}

// Credit: https://stackoverflow.com/a/7459271
void strins(char* destination, const char* source, int position) {
    char buffer[2048] = {};
    strncpy(buffer, destination, position);

    int length = strlen(buffer);

    strcpy(buffer + length, source);
    length += strlen(source);
    strcpy(buffer + length, destination + position);

    strcpy(destination, buffer);
}
#include "include/utils.h"

// Credit: https://cs.stackexchange.com/a/10321
char* to_binary(uint8_t number) {
    char* binary = malloc(sizeof(char) * 8);
    binary[0] = '\0'; // thank you matthias

    while (number > 0) {
        char num_str[8];
        sprintf(num_str, "%u", number % 2);

        strins(binary, num_str, 0);

        number = floor(number / 2);
    }

    return binary;
}


bool is_str_contained(const char** array, const char* string) {
    int i = 0;
    while (array[i] != NULL) {
        if (strcmp(array[i], string) == 0) {
            return true;
        }

        i++;
    }

    return false;
}

// Credit: https://stackoverflow.com/a/744822
bool str_ends_with(const char* string, const char* substring) {
    return strncmp(
        string + strlen(string) - strlen(substring),
        substring, strlen(substring)
    ) == 0;
}

// Credit: https://stackoverflow.com/a/7459271
void strins(char* destination, const char* source, int position) {
    char buffer[MAX_STRING_SIZE] = {};
    strncpy(buffer, destination, position);

    int length = strlen(buffer);

    strcpy(buffer + length, source);
    length += strlen(source);
    strcpy(buffer + length, destination + position);

    strcpy(destination, buffer);
}
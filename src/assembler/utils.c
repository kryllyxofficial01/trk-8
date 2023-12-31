#include "include/utils.h"

// Credit: https://cs.stackexchange.com/a/10321
char* to_binary(unsigned int number, int length) {
    char* binary = malloc(sizeof(char) * length);
    binary[0] = '\0'; // thank you matthias

    while (number > 0) {
        char num_str[length];
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

// Credit: https://linuxhint.com/remove-whitespaces-from-strings-with-strtrim-c/
void strtrim(char* string) {
    size_t start = 0;
    while (isspace(string[start])) start++;

    size_t end = strlen(string) - 1;
    while (isspace(string[start])) end--;

    size_t i;
    for (i = 0; i <= end; i++) {
        string[i] = string[start + i];
    }
    string[i] = '\0';
}
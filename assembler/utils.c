#include "include/utils.h"

void trim(char* string) {
    if (!string) {
        return;
    }

    char* start = string;

    while (*start && isspace((unsigned char) *start)) {
        start++;
    }

    if (*start == '\0') {
        *string = '\0';

        return;
    }

    char* end = string + strlen(string) - 1;

    while (end > start && isspace((unsigned char) *end)) {
        end--;
    }

    size_t length = end - start + 1;

    memmove(string, start, length);

    string[length] = '\0';
}

char* strsep(char** string, const char* delimiter) {
    if (!string || !(*string)) {
        return NULL;
    }

    char* start = *string;

    char* character = start;

    while (*character != '\0') {
        if (strchr(delimiter, *character) != NULL) {
            *character = '\0';

            *string = character + 1;

            return start;
        }

        character++;
    }

    *string = NULL;

    return start;
}
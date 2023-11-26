#include "include/utils.h"

// Credit: https://stackoverflow.com/a/744822
bool str_ends_with(const char* string, const char* substring) {
    return strncmp(
        string + strlen(string) - strlen(substring),
        substring, strlen(substring)
    ) == 0;
}
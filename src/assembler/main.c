#include <stdio.h>

int main(int argc, const char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    char* lines[0x8000];

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        lines[i++] = line;
    }
    lines[i] = 0;

    i = 0;
    while (lines[i] != 0) {
        printf("%s\n", lines[i]);

        i++;
    }

    return 0;
}
#include "include/assembler.h"

map_t* assembler_get_opcodes() {
    map_t* opcodes = map_init();

    int i = 0;
    while (PNEUMONICS[i] != NULL) {
        map_insert(opcodes, PNEUMONICS[i], i);

        i++;
    }

    return opcodes;
}
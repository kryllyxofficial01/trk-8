#include "include/registers.h"

int main(void) {
    trk8_registers_t registers;

    registers_init(&registers);

    registers_debug_print(registers);
}
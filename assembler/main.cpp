#include <iostream>

#include "include/token.hpp"

int main(void) {
    Token token(TT_IDENTIFIER, "mov");

    std::cout << token.to_string() << std::endl;

    return EXIT_SUCCESS;
}
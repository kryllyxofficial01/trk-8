#include <iostream>

#include "include/lexer.hpp"

int main(void) {
    std::string file_contents = "mov %a, 0xea";

    Lexer lexer(file_contents);

    std::vector<Token> tokens = lexer.lex();

    for (Token token : tokens) {
        std::cout << token.to_string() << std::endl;
    }

    return EXIT_SUCCESS;
}
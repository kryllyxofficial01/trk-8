#include <iostream>

#include "include/lexer.hpp"
#include "include/parser.hpp"

int main(void) {
    std::string file_contents = "mov %a, 0x19";

    Lexer lexer(file_contents);

    std::vector<Token> tokens = lexer.lex();

    for (Token token : tokens) {
        std::cout << token.to_string() << std::endl;
    }

    Parser parser(tokens);

    root_node_t ast = parser.parse();

    std::cout << ast->to_string() << std::endl;

    return EXIT_SUCCESS;
}

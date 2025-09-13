#pragma once

#include <string>
#include <vector>
#include <ctype.h>

#include "token.hpp"

#ifndef TRK8_NEXT_CHAR
    #define TRK8_NEXT_CHAR (1)
#endif

#ifndef TRK8_PREVIOUS_CHAR
    #define TRK8_PREVIOUS_CHAR (-1)
#endif

#ifndef is_binary
    #define is_binary(_char) ((_char) == '0' || (_char) == '1')
#endif

class Lexer {
    public:
        Lexer(std::string file_contents); 

        std::vector<Token> lex();

    private:
        Token get_next_token();

        Token get_identifier();
        Token get_number();
        Token get_character();

        void skip_whitespace();

        char peek_char(const int amount) const;

        void next_char();

        std::string file_contents;

        char current_character;
        size_t character_index;
};

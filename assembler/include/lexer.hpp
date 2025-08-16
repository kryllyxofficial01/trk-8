#pragma once

#include <string>
#include <vector>
#include <ctype.h>

#include "token.hpp"

#ifndef is_binary
    #define is_binary(_char) ((_char) == '0' || (_char) == '1')
#endif

class Lexer {
    public:
        Lexer(const std::string file_contents) : file_contents(file_contents) {
            this->character_index = 0;
            this->current_character = this->file_contents[this->character_index];
        }

        std::vector<Token> lex();

    private:
        Token get_next_token();

        Token get_identifier();
        Token get_number();
        Token get_character();

        void skip_whitespace();

        char peek(const int amount);

        void next_char();

        std::string file_contents;

        char current_character;
        size_t character_index;
};
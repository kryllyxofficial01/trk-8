#pragma once

#include <string>
#include <vector>
#include <ctype.h>

#include "token.hpp"

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
        Token get_character();

        void skip_whitespace();

        void next_char();

        std::string file_contents;

        char current_character;
        size_t character_index;
};
#include "include/lexer.hpp"

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens;

    Token current_token;

    while ((current_token = this->get_next_token()).get_type() != TokenTypes::TT_EOF) {
        tokens.push_back(current_token);
    }

    tokens.push_back(current_token);

    return tokens;
}

Token Lexer::get_next_token() {
    this->skip_whitespace();

    if (this->character_index < this->file_contents.length()) {
        if (isalpha(this->current_character)) {
            return this->get_identifier();
        }
        else if (isdigit(this->current_character)) {
            return this->get_number();
        }
        else {
            return this->get_character();
        }
    }

    return Token(TokenTypes::TT_EOF, "\0");
}

Token Lexer::get_identifier() {
    std::string identifier;

    while (isalnum(this->current_character)) {
        identifier += this->current_character;

        this->next_char();
    }

    return Token(TokenTypes::TT_IDENTIFIER, identifier);
}

Token Lexer::get_number() {
    std::string number;

    if (this->current_character == '0') {
        if (this->peek(1) == 'b') {
            this->next_char();
            this->next_char();

            while (is_binary(this->current_character)) {
                number += this->current_character;

                this->next_char();
            }

            return Token(TokenTypes::TT_BINARY, number);
        }
        else if (this->peek(1) == 'x') {
            this->next_char();
            this->next_char();

            while (isxdigit(this->current_character)) {
                number += this->current_character;

                this->next_char();
            }

            return Token(TokenTypes::TT_HEXADECIMAL, number);
        }
    }

    while (isdigit(this->current_character)) {
        number += this->current_character;

        this->next_char();
    }

    return Token(TokenTypes::TT_DECIMAL, number);
}

Token Lexer::get_character() {
    switch (this->current_character) {
        case '%': this->next_char(); return Token(TokenTypes::TT_PERCENT_SIGN, "%");
        case ',': this->next_char(); return Token(TokenTypes::TT_COMMA, ",");
        case '\n': this->next_char(); return Token(TokenTypes::TT_EOL, "\n");
    }

    this->next_char();

    return Token(
        TokenTypes::TT_UNKNOWN_TOKEN,
        std::string(1, this->peek(-1))
    );
}

void Lexer::skip_whitespace() {
    while (isspace(this->current_character)) {
        this->next_char();
    }
}

char Lexer::peek(const int amount) const {
    return this->file_contents[this->character_index + amount];
}

void Lexer::next_char() {
    this->current_character = this->file_contents[++this->character_index];
}
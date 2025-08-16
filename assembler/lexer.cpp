#include "include/lexer.hpp"

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens;

    Token current_token;

    while ((current_token = this->get_next_token()).get_type() != TT_EOF) {
        tokens.push_back(current_token);
    }

    tokens.push_back(current_token);

    return tokens;
}

Token Lexer::get_next_token() {
    this->skip_whitespace();

    if (this->character_index < this->file_contents.length()) {
        if (isalnum(this->current_character)) {
            return this->get_identifier();
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

    return Token(TT_IDENTIFIER, identifier);
}

void Lexer::skip_whitespace() {
    while (isspace(this->current_character)) {
        this->next_char();
    }
}

void Lexer::next_char() {
    this->current_character = this->file_contents[++this->character_index];
}
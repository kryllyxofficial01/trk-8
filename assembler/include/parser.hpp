#ifndef __TRK8_PARSER_HPP
#define __TRK8_PARSER_HPP

#include <vector>
#include <cstdint>

#include "token.hpp"
#include "nodes/nodes.hpp"

class Parser {
    public:
        Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
            this->token_index = 0;

            this->current_token = this->tokens[this->token_index]; 
        }

        root_node_t parse();

    private:
        node_t get_next_node();

        node_t parse_identifier();
        operand_node_t parse_operand();

        void eat(const TokenTypes expected_type);

        void next_token();

        inline const Token& peek(const int offset = 1) const {
            if (this->token_index + offset >= this->tokens.size()) {
                static Token eof(TokenTypes::TT_EOF, "\0");

                return eof;
            }

            return this->tokens[this->token_index + offset];
        }

        inline bool match_type(const TokenTypes token_type) const {
            return this->current_token.get_type() == token_type;
        }

        inline bool is_number_token() const {
            bool result = false;

            result |= this->match_type(TokenTypes::TT_DECIMAL);
            result |= this->match_type(TokenTypes::TT_BINARY);
            result |= this->match_type(TokenTypes::TT_HEXADECIMAL);

            return result;
        }

        std::vector<Token> tokens;

        Token current_token;
        size_t token_index;
};

#endif

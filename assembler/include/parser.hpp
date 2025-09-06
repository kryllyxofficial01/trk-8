#ifndef __TRK8_PARSER_HPP
#define __TRK8_PARSER_HPP

#include <vector>

#include "token.hpp"

#include "nodes/root_node.hpp"
#include "nodes/instruction_node.hpp"
#include "nodes/node.hpp"

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

        void eat(const TokenTypes expected_type);

        void next_token();

        inline const Token& peek(const int offset = 1) const {
            return this->tokens[this->token_index + offset];
        }

        std::vector<Token> tokens;

        Token current_token;
        size_t token_index;
};

#endif

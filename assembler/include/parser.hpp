#ifndef __TRK8_PARSER_HPP
#define __TRK8_PARSER_HPP

#include <vector>
#include <cstdint>

#include "token.hpp"
#include "nodes/nodes.hpp"

#ifndef TRK8_NEXT_TOKEN
    #define TRK8_NEXT_TOKEN (1)
#endif

#ifndef TRK8_PREVIOUS_TOKEN
    #define TRK8_PREVIOUS_TOKEN (-1)
#endif

class Parser {
    public:
        Parser(std::vector<Token> tokens);

        root_node_t parse();

    private:
        node_t get_next_node();

        node_t parse_identifier();
        operand_node_t parse_operand();

        void eat(const TokenTypes expected_type); 

        inline const Token& peek(const int offset) const;

        inline bool match_type(const TokenTypes token_type) const;

        inline bool is_number_token() const;

        void next_token();

        std::vector<Token> tokens;

        Token current_token;
        size_t token_index;
};

#endif

#include "include/parser.hpp"

root_node_t Parser::parse() {
    root_node_t root_node = std::make_unique<RootNode>();

    while (this->current_token.get_type() != TokenTypes::TT_EOF) {
        node_t node = this->get_next_node();

        root_node->add_node(std::move(node));
    }

    return root_node;
}

node_t Parser::get_next_node() {
    if (this->current_token.get_type() == TokenTypes::TT_IDENTIFIER) {
        return this->parse_identifier();
    }
}

node_t Parser::parse_identifier() {
    std::string identifier = this->current_token.get_value();
        
    this->eat(TokenTypes::TT_IDENTIFIER);

    instruction_node_t instruction_node = std::make_unique<InstructionNode>(identifier);

    return instruction_node;
}

void Parser::eat(const TokenTypes expected_type) {
    if (this->current_token.get_type() != expected_type) {
        // todo: handle unexpected token errors
    }

    this->next_token();
}

void Parser::next_token() {
    this->current_token = this->tokens[++this->token_index];
}

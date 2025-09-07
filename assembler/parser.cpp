#include "include/parser.hpp"
#include "include/nodes/operand_node.hpp"

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

    while (true) {
        if (this->match(TokenTypes::TT_EOL) || this->match(this->peek().get_type())) {
            break;
        }

        if (this->match(TokenTypes::TT_COMMA)) {
            this->eat(TokenTypes::TT_COMMA);

            continue;
        }

        instruction_node->add_operand(this->parse_operand());
    }

    return instruction_node;
}

operand_node_t Parser::parse_operand() {
    if (this->match(TokenTypes::TT_PERCENT_SIGN)) {
        this->eat(TokenTypes::TT_PERCENT_SIGN);

        std::string register_id = this->current_token.get_value();

        this->eat(TokenTypes::TT_IDENTIFIER);

        return std::make_unique<OperandNode<std::string>>(
            register_id,
            OperandBaseNode::OperandNodeType::ONT_REGISTER
        );
    }
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

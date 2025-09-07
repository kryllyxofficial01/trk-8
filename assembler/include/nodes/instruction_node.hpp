#ifndef __TRK8_INSTRUCTION_NODE_HPP
#define __TRK8_INSTRUCTION_NODE_HPP

#include <sstream>
#include <string>
#include <vector>

#include "operand_node.hpp"
#include "node.hpp"

class InstructionNode : public Node {
    public:
        explicit InstructionNode(std::string mnemonic) : mnemonic(mnemonic) {}

        void add_operand(operand_node_t operand_node) {
            this->operands.push_back(std::move(operand_node));
        }

        const std::string& get_mnemonic() const {
            return this->mnemonic;
        }

        const std::vector<operand_node_t>& get_operands() const {
            return this->operands;
        }

        std::string to_string() const override {
            std::ostringstream stream;

            stream << "INSTRUCTIONNODE(" << this->mnemonic << ")";
            
            if (this->operands.size() > 0) {
                stream << "{\n";

                for (const operand_node_t& operand : this->operands) {
                    stream << operand->to_string() << "\n";
                }

                stream << "}";
            }

            return stream.str();
        }

    private:
        std::string mnemonic;
        std::vector<operand_node_t> operands;
};

using instruction_node_t = std::unique_ptr<InstructionNode>;

#endif

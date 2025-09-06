#ifndef __TRK8_INSTRUCTION_NODE_HPP
#define __TRK8_INSTRUCTION_NODE_HPP

#include <sstream>
#include <string>
#include <vector>

#include "node.hpp"
#include "operand_node.hpp"

class InstructionNode : public Node {
    public:
        explicit InstructionNode(std::string mnemonic) : mnemonic(mnemonic) {}

        template <typename T>
        void add_operand(T operand_value) {
            this->operands.push_back(
                std::make_unique<OperandNode<T>>(std::move(operand_value))
            );
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

                stream << "}\n";
            }

            return stream.str();
        }

    private:
        std::string mnemonic;
        std::vector<operand_node_t> operands;
};

using instruction_node_t = std::unique_ptr<InstructionNode>;

#endif

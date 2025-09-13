#ifndef __TRK8_OPERAND_NODE_HPP
#define __TRK8_OPERAND_NODE_HPP

#include <memory>
#include <sstream>
#include <string>
#include <type_traits>

#include "node.hpp"

class OperandBaseNode : public Node {
    public:
        enum OperandNodeType {
            ONT_IMMEDIATE,
            ONT_REGISTER
        };

        virtual const OperandNodeType get_type() const = 0;
};

template <typename T>
class OperandNode : public OperandBaseNode {
    public:
        explicit OperandNode(T value, OperandNodeType operand_node_type) {
            this->value = std::move(value);
            this->type = operand_node_type;
        }
        
        const T& get_value() const {
            return this->value;
        }

        const OperandNodeType get_type() const override {
            return this->type;
        }

        const std::string to_string() const override {
            std::ostringstream stream;

            stream << "OPERANDNODE(";
            stream << std::to_string(this->type);
            stream << ", '";

            if constexpr (std::is_same_v<T, std::string>) {
                stream << this->value;
            }
            else {
                stream << std::to_string(this->value);
            }

            stream << "')";

            return stream.str();
        }

    private:
        T value;
        OperandNodeType type;
};

using operand_node_t = std::unique_ptr<OperandBaseNode>;

#endif

#ifndef __TRK8_OPERAND_NODE_HPP
#define __TRK8_OPERAND_NODE_HPP

#include <memory>
#include <string>
#include <type_traits>

#include "node.hpp"

class OperandBaseNode : public Node {
    public:
        enum class OperandNodeType {
            ONT_IMMEDIATE,
            ONT_REGISTER
        };

        virtual OperandNodeType get_type() const = 0;
};

template <typename T>
class OperandNode : public OperandBaseNode {
    public:
        explicit OperandNode(T value) : value(std::move(value)) {}
        
        const T& get_value() const {
            return this->value;
        }

        std::string to_string() const override {
            if constexpr (std::is_same_v<T, std::string>) {
                return "OPERANDNODE(" + this->value + ")";
            }
            else {
                return "OPERANDNODE(" + std::to_string(this->value) + ")";
            }
        }

    private:
        T value;
};

using operand_node_t = std::unique_ptr<OperandBaseNode>;

#endif

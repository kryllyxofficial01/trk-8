#include "include/assembler.hpp"
#include "include/isa.hpp"
#include "include/utils.hpp"
#include <stdexcept>

static OperandType classify_operand(const std::string& operand) {
    if (operand.front() == REGISTER_PREFIX) {
        return OperandType::OP_REGISTER;
    }

    if (operand.front() == IMMEDIATE_PREFIX) {
        // TODO: add support for base 10 and hex (maybe octal???)
        
        try {

        }
        catch (const std::invalid_argument& error) {
            goto default_type;
        }
    }

    default_type:
}

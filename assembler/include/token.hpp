#pragma once

#include <string>
#include <format>

typedef enum _TRK8_TOKEN_TYPES {
    TT_IDENTIFIER,
    TT_INTEGER
} token_type_t;

class Token {
    public:
        Token(const token_type_t& type, const std::string& value) : type(type), value(value) {}

        inline std::string to_string() const {
            return std::format(
                "TOKEN({}, '{}')",
                static_cast<unsigned int>(this->type),
                this->value
            );
        }

    private:
        token_type_t type;
        std::string value;
};
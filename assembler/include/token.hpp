#pragma once

#include <string>
#include <format>

enum TokenTypes {
    TT_IDENTIFIER,

    TT_INTEGER,

    TT_EOF = 255
};

class Token {
    public:
        Token(const enum TokenTypes type, const std::string value) : type(type), value(value) {}
        Token() = default;

        inline std::string to_string() const {
            return std::format(
                "TOKEN({}, '{}')",
                static_cast<unsigned int>(this->type),
                this->value
            );
        }

        enum TokenTypes get_type() const {
            return this->type;
        }

        std::string get_value() const {
            return this->value;
        }

    private:
        enum TokenTypes type;
        std::string value;
};
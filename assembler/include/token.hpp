#pragma once

#include <sstream>
#include <string>

enum TokenTypes {
    TT_IDENTIFIER,

    TT_DECIMAL,
    TT_BINARY,
    TT_HEXADECIMAL,

    TT_PERCENT_SIGN,
    TT_COMMA,

    TT_EOL, // newline

    TT_UNKNOWN_TOKEN = 254,
    TT_EOF = 255
};

class Token {
    public:
        Token(const enum TokenTypes type, const std::string value) : type(type), value(value) {}
        Token() = default;

        inline std::string to_string() const {
            std::ostringstream stream;

            stream << "TOKEN(";
            stream << std::to_string(this->type);
            stream << ", '";
            stream << this->value;
            stream << "')";

            return stream.str();
        }

        inline enum TokenTypes get_type() const {
            return this->type;
        }

        inline std::string get_value() const {
            return this->value;
        }

    private:
        enum TokenTypes type;
        std::string value;
};

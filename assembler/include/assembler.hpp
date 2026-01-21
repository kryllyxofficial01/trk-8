#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct AssemblyLine {
    size_t lineno;

    std::string label;

    std::string mnemonic;
    std::vector<std::string> operands;
};

class Assembler {
    public:
        void assemble(void);

        void load_file(const std::string& filepath);

        void write_binary(const std::string& filepath) const;

    private:
        void first_pass(void);
        void second_pass(void);

        AssemblyLine parse_line(const std::string& line, size_t lineno);

        std::vector<std::string> lines;
        std::vector<uint8_t> output;

        std::unordered_map<std::string, uint16_t> labels;
};

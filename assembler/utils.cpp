#include "include/utils.hpp"

std::string trim(const std::string& string) {
    auto start = string.find_first_not_of(WHITESPACE);

    if (start == std::string::npos) {
        return "";
    }

    auto end = string.find_last_not_of(WHITESPACE);

    return string.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string& string, char delimiter) {
    std::vector<std::string> output;

    std::stringstream sstream(string);
    std::string token;

    while (std::getline(sstream, token, delimiter)) {
        output.push_back(token);
    }

    return output;
}

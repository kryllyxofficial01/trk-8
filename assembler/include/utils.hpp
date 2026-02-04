#pragma once

#include <sstream>
#include <string>
#include <vector>

#ifndef string_contains
    #define string_contains(_string, _substr) (_string.find(_substr) != std::string::npos)
#endif

#ifndef umap_contains
    #define umap_contains(_umap, _key) (_umap.find(_key) != _umap.end())
#endif

#ifndef WHITESPACE
    #define WHITESPACE " \r\n\t"
#endif

std::string trim(const std::string& string);
std::vector<std::string> split(const std::string& string, char delimeter);

#pragma once

#include "Token.hpp"
#include <vector>
#include <string_view>

using Tokens = std::vector<Token>;

struct Lexer {
    static Tokens Tokenize(const std::string_view& expression);
};
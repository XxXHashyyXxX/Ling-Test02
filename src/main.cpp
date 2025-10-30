#include <iostream>
#include "frontend/Lexer.hpp"

int main() {
    Tokens tokens = Lexer::Tokenize("-1-2");
    for(auto& token : tokens) {
        std::cout << token << std::endl;
    }
}
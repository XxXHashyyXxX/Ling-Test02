#include <iostream>
#include "frontend/Token.hpp"
#include <array>

int main() {
    std::array<Token, 9> tokens;
    
    tokens[0] = Token();
    tokens[1] = Token(69);
    tokens[2] = Token(3.4);
    tokens[3] = Token(Token::Type::OperatorMinus);
    tokens[4] = Token(Token::Type::OperatorPlus);
    tokens[5] = Token(Token::Type::OperatorSlash);
    tokens[6] = Token(Token::Type::OperatorStar);
    tokens[7] = Token(Token::Type::ParenthesisLeft);
    tokens[8] = Token(Token::Type::ParenthesisRight);

    for(auto& token : tokens) {
        std::cout << token << std::endl;
    }
}
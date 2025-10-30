#include "Lexer.hpp"
#include <cctype>

Tokens Lexer::Tokenize(const std::string_view &expression)
{
    Tokens tokens;

    for(auto it = expression.begin(); it != expression.end(); ++it) {
        if(std::isspace(*it)) continue;

        if(std::isdigit(*it)) {
            auto start = it;
            while(std::isdigit(*it)) ++it;
            
            if(*it == '.') {
                // Double
                ++it;
                while(std::isdigit(*it)) ++it;
                auto end = it;
                double value = std::stod(std::string(start, end));
                tokens.push_back(Token(value));
                --it;
                continue;
            }

            auto end = it;
            int value = std::stoi(std::string(start, end));
            tokens.push_back(Token(value));
            --it;
            continue;
        }

        if(*it == '+') {
            tokens.push_back(Token(Token::Type::OperatorPlus));
            continue;
        }

        if(*it == '-') {
            tokens.push_back(Token(Token::Type::OperatorMinus));
            continue;
        }

        if(*it == '*') {
            tokens.push_back(Token(Token::Type::OperatorStar));
            continue;
        }

        if(*it == '/') {
            tokens.push_back(Token(Token::Type::OperatorSlash));
            continue;
        }

        if(*it == '(') {
            tokens.push_back(Token(Token::Type::ParenthesisLeft));
            continue;
        }

        if(*it == ')') {
            tokens.push_back(Token(Token::Type::ParenthesisRight));
            continue;
        }

        while(std::isspace(*it)) ++it;
        tokens.push_back(Token());
    }

    return tokens;
}
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
            if(tokens.empty()) {
                tokens.push_back(Token(Token::Type::OperatorPlus, Token::OperatorArity::Unary));
                continue;
            }
            auto previous = tokens.back();
            if(previous.type == Token::Type::LiteralDouble ||
                    previous.type == Token::Type::LiteralInt || 
                    previous.type == Token::Type::ParenthesisRight)
                tokens.push_back(Token(Token::Type::OperatorPlus, Token::OperatorArity::Binary));
            else
                tokens.push_back(Token(Token::Type::OperatorPlus, Token::OperatorArity::Unary));
            continue;
        }

        if(*it == '-') {
            if(tokens.empty()) {
                tokens.push_back(Token(Token::Type::OperatorMinus, Token::OperatorArity::Unary));
                continue;
            }
            auto previous = tokens.back();
            if(previous.type == Token::Type::LiteralDouble ||
                    previous.type == Token::Type::LiteralInt || 
                    previous.type == Token::Type::ParenthesisRight)
                tokens.push_back(Token(Token::Type::OperatorMinus, Token::OperatorArity::Binary));
            else
                tokens.push_back(Token(Token::Type::OperatorMinus, Token::OperatorArity::Unary));
            continue;
        }

        if(*it == '*') {
            if(tokens.empty()) {
                tokens.push_back(Token(Token::Type::OperatorStar, Token::OperatorArity::Unary));
                continue;
            }
            auto previous = tokens.back();
            if(previous.type == Token::Type::LiteralDouble ||
                    previous.type == Token::Type::LiteralInt || 
                    previous.type == Token::Type::ParenthesisRight)
                tokens.push_back(Token(Token::Type::OperatorStar, Token::OperatorArity::Binary));
            else
                tokens.push_back(Token(Token::Type::OperatorStar, Token::OperatorArity::Unary));
            continue;
        }

        if(*it == '/') {
            if(tokens.empty()) {
                tokens.push_back(Token(Token::Type::OperatorSlash, Token::OperatorArity::Unary));
                continue;
            }
            auto previous = tokens.back();
            if(previous.type == Token::Type::LiteralDouble ||
                    previous.type == Token::Type::LiteralInt || 
                    previous.type == Token::Type::ParenthesisRight)
                tokens.push_back(Token(Token::Type::OperatorSlash, Token::OperatorArity::Binary));
            else
                tokens.push_back(Token(Token::Type::OperatorSlash, Token::OperatorArity::Unary));
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
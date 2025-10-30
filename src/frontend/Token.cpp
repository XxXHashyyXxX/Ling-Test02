#include "Token.hpp"
#include <stdexcept>

Token::Token(Type type)
{
    if(type == Type::LiteralInt || type == Type::LiteralDouble) 
        throw std::invalid_argument("Type provided for token requires initialization with value");
    
    this->type = type;
}

std::ostream &operator<<(std::ostream &os, const Token &token)
{
    switch(token.type) {
        case Token::Type::Invalid:
            os << "Invalid token";
            return os;
        case Token::Type::LiteralInt:
            if(!std::holds_alternative<int>(token.value)) throw std::runtime_error("Stored value doesnt match the type");
            return os << "Int " << std::get<int>(token.value);
        case Token::Type::LiteralDouble:
            if(!std::holds_alternative<double>(token.value)) throw std::runtime_error("Stored value doesnt match the type");
            return os << "Double " << std::get<double>(token.value);
        case Token::Type::OperatorMinus:
            return os << "Operator -";
        case Token::Type::OperatorPlus:
            return os << "Operator +";
        case Token::Type::OperatorSlash:
            return os << "Operator /";
        case Token::Type::OperatorStar:
            return os << "Operator *";
        case Token::Type::ParenthesisLeft:
            return os << "Parenthesis (";
        case Token::Type::ParenthesisRight:
            return os << "Parenthesis )";
        default:
            throw std::runtime_error("Unrecognized token");
    }
}

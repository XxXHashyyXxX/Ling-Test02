#include "Token.hpp"
#include <stdexcept>

Token::Token(Type type, OperatorArity arity)
{
    if(type == Type::LiteralInt || type == Type::LiteralDouble) 
        throw std::invalid_argument("Type provided for token requires initialization with value");
    
    this->type = type;
    value = arity;
}

int Token::GetValueAsNumber()
{
    if(type != Type::LiteralInt) throw std::runtime_error("Value stored in token is not a number");
    if(!std::holds_alternative<int>(value)) throw std::runtime_error("Stored value doesnt match the type");

    return std::get<int>(value);
}

double Token::GetValueAsReal()
{
    if(type != Type::LiteralDouble) throw std::runtime_error("Value stored in token is not a real");
    if(!std::holds_alternative<double>(value)) throw std::runtime_error("Stored value doesnt match the type");

    return std::get<double>(value);
}

Token::OperatorArity Token::GetValueAsOperatorArity()
{
    if(type != Type::OperatorMinus && type != Type::OperatorPlus && type != Type::OperatorSlash && type != Type::OperatorSlash)
        throw std::runtime_error("Value stored in token is not an operator");
    if(!std::holds_alternative<OperatorArity>(value)) throw std::runtime_error("Stored value doesnt match the type");

    return std::get<OperatorArity>(value);
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
            if(!std::holds_alternative<Token::OperatorArity>(token.value)) throw std::runtime_error("Stored value doesnt match the type");
            os << "Operator - ";
            switch(std::get<Token::OperatorArity>(token.value)) {
                case Token::OperatorArity::Binary:
                    return os << "binary";
                case Token::OperatorArity::Unary:
                    return os << "unary";
                default:
                    throw std::runtime_error("Unrecognized operator arity");
            }
        case Token::Type::OperatorPlus:
            if(!std::holds_alternative<Token::OperatorArity>(token.value)) throw std::runtime_error("Stored value doesnt match the type");
            os << "Operator + ";
            switch(std::get<Token::OperatorArity>(token.value)) {
                case Token::OperatorArity::Binary:
                    return os << "binary";
                case Token::OperatorArity::Unary:
                    return os << "unary";
                default:
                    throw std::runtime_error("Unrecognized operator arity");
            }
        case Token::Type::OperatorSlash:
            if(!std::holds_alternative<Token::OperatorArity>(token.value)) throw std::runtime_error("Stored value doesnt match the type");
            os << "Operator / ";
            switch(std::get<Token::OperatorArity>(token.value)) {
                case Token::OperatorArity::Binary:
                    return os << "binary";
                case Token::OperatorArity::Unary:
                    return os << "unary";
                default:
                    throw std::runtime_error("Unrecognized operator arity");
            }
        case Token::Type::OperatorStar:
            if(!std::holds_alternative<Token::OperatorArity>(token.value)) throw std::runtime_error("Stored value doesnt match the type");
            os << "Operator * ";
            switch(std::get<Token::OperatorArity>(token.value)) {
                case Token::OperatorArity::Binary:
                    return os << "binary";
                case Token::OperatorArity::Unary:
                    return os << "unary";
                default:
                    throw std::runtime_error("Unrecognized operator arity");
            }
        case Token::Type::ParenthesisLeft:
            return os << "Parenthesis (";
        case Token::Type::ParenthesisRight:
            return os << "Parenthesis )";
        default:
            throw std::runtime_error("Unrecognized token");
    }
}

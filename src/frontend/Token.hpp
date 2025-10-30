#pragma once

#include <variant>
#include <ostream>

struct Token {
    enum class Type {
        Invalid,
        LiteralInt, LiteralDouble,
        OperatorPlus, OperatorMinus, OperatorStar, OperatorSlash,
        ParenthesisLeft, ParenthesisRight
    } type;

    enum class OperatorArity {
        Unary, Binary
    };

    std::variant<std::monostate, int, double, OperatorArity> value;

    Token(Type type = Type::Invalid, OperatorArity arity);
    Token(int value) : value(value), type(Type::LiteralInt) {}
    Token(double value) : value(value), type(Type::LiteralDouble) {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token);

    int GetValueAsNumber();
    double GetValueAsReal();
    OperatorArity GetValueAsOperatorArity();
};

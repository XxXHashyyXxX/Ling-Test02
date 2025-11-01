#pragma once

#include "Lexer.hpp"
#include "Ast.hpp"

class Parser {
public:
    static std::unique_ptr<AstValueNode> ParseExpression(const Tokens& tokens);
    static Tokens testOnp(const Tokens& tokens) { return ParseExpressionToOnp(tokens); }

private:
    static Tokens ParseExpressionToOnp(const Tokens& tokens);
    static int GetOperatorPrecedence(const Token::Type& type);
};
#include "Parser.hpp"
#include <stack>

std::unique_ptr<AstValueNode> Parser::ParseExpression(const Tokens &tokens)
{
    
}

Tokens Parser::ParseExpressionToOnp(const Tokens &tokens)
{
    Tokens outTokens;
    outTokens.reserve(tokens.size());
    std::stack<Token> operators;

    for(auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch(it->type) {
            case Token::Type::Invalid:
            case Token::Type::LiteralDouble:
            case Token::Type::LiteralInt:
                outTokens.push_back(*it);
                break;
            case Token::Type::ParenthesisLeft:
                operators.push(*it);
                break;
            case Token::Type::ParenthesisRight:
                while(!operators.empty() && operators.top().type != Token::Type::ParenthesisLeft) {
                    auto top = operators.top();
                    operators.pop();
                    outTokens.push_back(top);
                }

                if(operators.empty() || operators.top().type != Token::Type::ParenthesisLeft) 
                    throw std::runtime_error("Invalid parenthesis match");
                
                operators.pop();
                break;
            case Token::Type::OperatorMinus:
            case Token::Type::OperatorPlus:
            case Token::Type::OperatorSlash:
            case Token::Type::OperatorStar:
                auto currentPrecedence = GetOperatorPrecedence(it->type);
                while(!operators.empty() && 
                        operators.top().type != Token::Type::ParenthesisLeft && 
                        (GetOperatorPrecedence(operators.top().type) > currentPrecedence ||
                        (GetOperatorPrecedence(operators.top().type) == currentPrecedence && 
                        std::get<Token::OperatorArity>(it->value) == Token::OperatorArity::Binary))) {
                    auto op = operators.top();
                    operators.pop();
                    outTokens.push_back(op);
                }
                operators.push(*it);
                break;
        }
    }

    while(!operators.empty()) {
        auto token = operators.top();
        operators.pop();
        outTokens.push_back(token);
    }

    return outTokens;
}

int Parser::GetOperatorPrecedence(const Token::Type &type)
{
    switch(type) {
        case Token::Type::Invalid:
        case Token::Type::LiteralDouble:
        case Token::Type::LiteralInt:
        case Token::Type::ParenthesisLeft:
        case Token::Type::ParenthesisRight:
            throw std::runtime_error("Token not precedenceable");
        case Token::Type::OperatorPlus:
        case Token::Type::OperatorMinus:
            return 0;
        case Token::Type::OperatorStar:
        case Token::Type::OperatorSlash:
            return 1;
        default:
            throw std::runtime_error("Unrecognized token type");
    }
}

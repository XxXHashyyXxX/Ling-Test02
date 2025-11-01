#include "Ast.hpp"

int AstLiteralValueNode::GetIntValue()
{
    if(std::holds_alternative<int>(value)) return std::get<int>(value);
    if(std::holds_alternative<double>(value)) return static_cast<int>(std::get<double>(value));
    throw std::runtime_error("Value not initialized");
}

double AstLiteralValueNode::GetDoubleValue()
{
    if(std::holds_alternative<int>(value)) return static_cast<double>(std::get<int>(value));
    if(std::holds_alternative<double>(value)) return std::get<double>(value);
    throw std::runtime_error("Value not initialized");
}

int AstUnaryOperatorNode::GetIntValue()
{
    if(!operand) throw std::runtime_error("Operand not initialized");

    switch(type) {
        case Type::Identity:
            return operand->GetIntValue();
        case Type::Negation:
            return -operand->GetIntValue();
        default:
            throw std::runtime_error("Invalid operator type");
    }
}

double AstUnaryOperatorNode::GetDoubleValue()
{
    if(!operand) throw std::runtime_error("Operand not initialized");

    switch(type) {
        case Type::Identity:
            return operand->GetDoubleValue();
        case Type::Negation:
            return -operand->GetDoubleValue();
        default:
            throw std::runtime_error("Invalid operator type");
    }
}

int AstBinaryOperatorNode::GetIntValue()
{
    if(!leftOperand || !rightOperand) throw std::runtime_error("Operands not initialized");

    switch(type) {
        case Type::Addition:
            return leftOperand->GetIntValue() + rightOperand->GetIntValue();
        case Type::Subtraction:
            return leftOperand->GetIntValue() - rightOperand->GetIntValue();
        case Type::Multiplication:
            return leftOperand->GetIntValue() * rightOperand->GetIntValue();
        case Type::Division:
            if(rightOperand->GetIntValue() == 0) throw std::runtime_error("Division by zero");
            return leftOperand->GetIntValue() / rightOperand->GetIntValue();
        default:
            throw std::runtime_error("Invalid operator type");
    }
}

double AstBinaryOperatorNode::GetDoubleValue()
{
    if(!leftOperand || !rightOperand) throw std::runtime_error("Operands not initialized");

    switch(type) {
        case Type::Addition:
            return leftOperand->GetDoubleValue() + rightOperand->GetDoubleValue();
        case Type::Subtraction:
            return leftOperand->GetDoubleValue() - rightOperand->GetDoubleValue();
        case Type::Multiplication:
            return leftOperand->GetDoubleValue() * rightOperand->GetDoubleValue();
        case Type::Division:
            if(rightOperand->GetDoubleValue() == 0) throw std::runtime_error("Division by zero");
            return leftOperand->GetDoubleValue() / rightOperand->GetDoubleValue();
        default:
            throw std::runtime_error("Invalid operator type");
    }
}

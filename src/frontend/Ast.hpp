#pragma once

#include <memory>
#include <variant>

class AstNode {
public:
    virtual ~AstNode() = default;
};

class AstValueNode : public AstNode {
public:
    virtual ~AstValueNode() = default;

    virtual int GetIntValue() = 0;
    virtual double GetDoubleValue() = 0;
};

class AstLiteralValueNode : public AstValueNode {
public:
    ~AstLiteralValueNode() = default;
    AstLiteralValueNode(int value) : value(value) {}
    AstLiteralValueNode(double value) : value(value) {}

    int GetIntValue() override;
    double GetDoubleValue() override;

private:
    std::variant<int, double> value;
};

class AstUnaryOperatorNode : public AstValueNode {
public:
    enum class Type {
        Identity, Negation
    };

    ~AstUnaryOperatorNode() = default;
    AstUnaryOperatorNode(Type type, AstValueNode* operand) : 
        type(type), operand(operand) {}

    int GetIntValue() override;
    double GetDoubleValue() override;

private:
    Type type;
    std::unique_ptr<AstValueNode> operand;
};

class AstBinaryOperatorNode : public AstValueNode {
public:
    enum class Type {
        Addition, Subtraction, Multiplication, Division
    };

    ~AstBinaryOperatorNode() = default;
    AstBinaryOperatorNode(Type type, AstValueNode* leftOperand, AstValueNode* rightOperand) :
        type(type), leftOperand(leftOperand), rightOperand(rightOperand) {}

    int GetIntValue() override;
    double GetDoubleValue() override;

private:
    Type type;
    std::unique_ptr<AstValueNode> leftOperand;
    std::unique_ptr<AstValueNode> rightOperand;
};
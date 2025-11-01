#include <iostream>
#include <memory>
#include <stdexcept>
#include "frontend/Ast.hpp"

int main() {
    std::unique_ptr<AstValueNode> value;

    // === Literal: int ===
    value.reset(new AstLiteralValueNode(7));
    std::cout << "=== Literal int ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Literal: double ===
    value.reset(new AstLiteralValueNode(-2.5));
    std::cout << "=== Literal double ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Unary: Identity (int) ===
    value.reset(new AstLiteralValueNode(42));
    AstValueNode* op_identity_int = value.release();
    value.reset(new AstUnaryOperatorNode(
        AstUnaryOperatorNode::Type::Identity,
        op_identity_int
    ));
    std::cout << "=== Unary identity (int) ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Unary: Negation (double) ===
    value.reset(new AstLiteralValueNode(3.5));
    AstValueNode* op_neg_double = value.release();
    value.reset(new AstUnaryOperatorNode(
        AstUnaryOperatorNode::Type::Negation,
        op_neg_double
    ));
    std::cout << "=== Unary negation (double) ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Binary: Addition (int + double) ===
    value.reset(new AstLiteralValueNode(5));
    AstValueNode* add_l = value.release();
    value.reset(new AstLiteralValueNode(3.1));
    AstValueNode* add_r = value.release();
    value.reset(new AstBinaryOperatorNode(
        AstBinaryOperatorNode::Type::Addition,
        add_l, add_r
    ));
    std::cout << "=== Binary addition ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Binary: Subtraction (10 - 4) ===
    value.reset(new AstLiteralValueNode(10));
    AstValueNode* sub_l = value.release();
    value.reset(new AstLiteralValueNode(4));
    AstValueNode* sub_r = value.release();
    value.reset(new AstBinaryOperatorNode(
        AstBinaryOperatorNode::Type::Subtraction,
        sub_l, sub_r
    ));
    std::cout << "=== Binary subtraction ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Binary: Multiplication (-2 * 8.5) ===
    value.reset(new AstLiteralValueNode(-2));
    AstValueNode* mul_l = value.release();
    value.reset(new AstLiteralValueNode(8.5));
    AstValueNode* mul_r = value.release();
    value.reset(new AstBinaryOperatorNode(
        AstBinaryOperatorNode::Type::Multiplication,
        mul_l, mul_r
    ));
    std::cout << "=== Binary multiplication ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Binary: Division (9 / 3) ===
    value.reset(new AstLiteralValueNode(9));
    AstValueNode* div_l_ok = value.release();
    value.reset(new AstLiteralValueNode(3));
    AstValueNode* div_r_ok = value.release();
    value.reset(new AstBinaryOperatorNode(
        AstBinaryOperatorNode::Type::Division,
        div_l_ok, div_r_ok
    ));
    std::cout << "=== Binary division (ok) ===\n";
    std::cout << "Int: " << value->GetIntValue() << "\n";
    std::cout << "Double: " << value->GetDoubleValue() << "\n";

    // === Binary: Division by zero (1 / 0) ===
    try {
        value.reset(new AstLiteralValueNode(1));
        AstValueNode* div_l_zero = value.release();
        value.reset(new AstLiteralValueNode(0));
        AstValueNode* div_r_zero = value.release();
        value.reset(new AstBinaryOperatorNode(
            AstBinaryOperatorNode::Type::Division,
            div_l_zero, div_r_zero
        ));
        std::cout << "=== Binary division by zero ===\n";
        std::cout << "Int: " << value->GetIntValue() << "\n";
        std::cout << "Double: " << value->GetDoubleValue() << "\n";
    } catch (const std::runtime_error& e) {
        std::cout << "=== Binary division by zero ===\n";
        std::cout << "runtime_error: " << e.what() << "\n";
    }

    return 0;
}

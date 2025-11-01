#include <iostream>
#include "frontend/Parser.hpp"
#include <string>
#include <fstream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> vector) {
    os << "[";
    for(auto it = vector.begin(); it != vector.end(); ++it) {
        os << *it;
        if(it == vector.end() - 1) os << "]";
        else os << "\n";
    }

    return os;
}

int performTests() {
    std::ifstream numTests("testNum.txt");
    std::ifstream realTests("testReal.txt");

    std::string line;

    std::cout << "=== Number Tests ===" << std::endl;
    while(std::getline(numTests, line)) {
        const auto p1 = line.find(';');
        const auto p2 = line.find(';', p1 + 1);

        auto name = line.substr(0, p1);
        auto expression = line.substr(p1 + 1, p2 - p1 - 1);
        auto expected = line.substr(p2 + 1);

        std::cout << "Test " << name << ": " << expression << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Calculated: " << Parser::ParseExpression(Lexer::Tokenize(expression))->GetIntValue() << std::endl;
    }

    std::cout << "=== Real tests === " << std::endl;
    while(std::getline(realTests, line)) {
        const auto p1 = line.find(';');
        const auto p2 = line.find(';', p1 + 1);

        auto name = line.substr(0, p1);
        auto expression = line.substr(p1 + 1, p2 - p1 - 1);
        auto expected = line.substr(p2 + 1);

        std::cout << "Test " << name << ": " << expression << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Calculated: " << Parser::ParseExpression(Lexer::Tokenize(expression))->GetDoubleValue() << std::endl;
    }

    return 0;
}

int main() {
    return performTests();
}
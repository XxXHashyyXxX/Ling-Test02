#include <iostream>
#include "frontend/Parser.hpp"
#include <string>

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

int main() {
    std::string expression = "3 + 2 + 1 + 0";
    auto lexed = Lexer::Tokenize(expression);
    auto onp = Parser::testOnp(lexed);
    std::cout << onp << std::endl;

    return 0;
}
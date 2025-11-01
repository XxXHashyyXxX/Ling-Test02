cmake_minimum_required(VERSION 3.14)
project(ling)

set(CMAKE_CXX_STANDARD 20)

add_executable(ling src/main.cpp
                src/frontend/Token.cpp
                src/frontend/Lexer.cpp
                src/frontend/Ast.cpp)

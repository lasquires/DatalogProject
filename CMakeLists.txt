cmake_minimum_required(VERSION 3.22)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project2 main.cpp DatalogProgram.cpp Parameter.cpp Parser.cpp Predicate.cpp Rule.cpp Scanner.cpp Token.cpp)

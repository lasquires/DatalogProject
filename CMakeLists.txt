cmake_minimum_required(VERSION 3.22)
project(project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(project3 main.cpp Scheme.cpp Tuple.cpp Relation.cpp DatalogProgram.cpp Parameter.cpp Parser.cpp Predicate.cpp Rule.cpp Scanner.cpp Token.cpp Interpreter.cpp Database.cpp)

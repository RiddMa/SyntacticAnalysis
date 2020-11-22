cmake_minimum_required(VERSION 3.17)
project(SyntacticAnalysis)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cpp" "*.h")

add_executable(SYN ${SOURCES})
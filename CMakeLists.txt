cmake_minimum_required(VERSION 3.23)
project(SymbolTabelProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(SymbolTabelProject main.cpp stentry.h stlist.h stable.h stlist.cpp stable.cpp)

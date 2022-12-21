cmake_minimum_required(VERSION 3.22)
project(projeto_pratico)

set(CMAKE_CXX_STANDARD 14)

add_executable(projeto_pratico project-implementation.cpp registro.cpp registro.h CSVToBinary.cpp CSVToBinary.h)

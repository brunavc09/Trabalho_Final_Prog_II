cmake_minimum_required(VERSION 4.1)
project(Trabalho_Final_Prog_II C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Trabalho_Final_Prog_II
        include/estoque.h
        include/gastos.h
        src/estoque.c
        src/gastos.c)

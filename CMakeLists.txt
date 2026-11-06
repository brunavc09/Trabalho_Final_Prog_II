cmake_minimum_required(VERSION 3.21)
project(Trabalho_Final_Prog_II C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Trabalho_Final_Prog_II
        include/estoque.h
        include/gastos.h
        src/estoque.c
        src/gastos.c
        src/main.c
        funções_aux/avl.h
        funções_aux/avl.c)

include(FetchContent)

FetchContent_Declare(
        libprg
        GIT_REPOSITORY https://github.com/brunavc09/libprg.git
        GIT_TAG        v1.0
)
FetchContent_MakeAvailable(libprg)

target_link_libraries(Trabalho_Final_Prog_II PUBLIC libprg)
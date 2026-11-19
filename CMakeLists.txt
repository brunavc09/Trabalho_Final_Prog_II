cmake_minimum_required(VERSION 3.21)
project(Trabalho_Final_Prog_II C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Trabalho_Final_Prog_II
        src/estoque.c
        src/gastos.c
        src/main.c
        src/arquivo.c
        src/entrada.c
)

add_executable(teste_estoque
        tests/teste_arquivo.c
        src/arquivo.c
        src/estoque.c
)

add_executable(teste_entrada
        tests/teste_entrada.c
        src/entrada.c
)

include(FetchContent)

FetchContent_Declare(
        libprg
        GIT_REPOSITORY https://github.com/brunavc09/libprg.git
        GIT_TAG        v1.2
)
FetchContent_MakeAvailable(libprg)

target_link_libraries(Trabalho_Final_Prog_II PUBLIC libprg)
target_link_libraries(teste_estoque PUBLIC libprg)
target_link_libraries(teste_entrada PUBLIC libprg)

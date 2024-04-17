cmake_minimum_required(VERSION 3.27)
project(programacao_concorrente C)

set(CMAKE_C_STANDARD 11)

include_directories(exercicios-de-aula/04-03)

add_executable(programacao_concorrente
        exercicios-de-aula/04-03/Main.c
        exercicios-de-aula/04-03/MinMax.c
        exercicios-de-aula/04-03/MinMax.h
        exercicios-de-aula/04-03/SortVector.c
        exercicios-de-aula/04-03/SortVector.h
)

cmake_minimum_required(VERSION 3.30)
project(Palestra C)

set(CMAKE_C_STANDARD 11)

add_executable(Palestra
        main.c
        utils.c
        cliente_lista.h
        lezioni.h
        cliente_coda.h
        lista_lezioni.h
)
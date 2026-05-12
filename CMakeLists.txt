cmake_minimum_required(VERSION 4.0)
project(proy)

set(CMAKE_CXX_STANDARD 20)

add_executable(proy main.cpp
        Tablero.cpp
        Tablero.h
        Detective.cpp
        Detective.h
        Sospechoso.cpp
        Sospechoso.h
        GestorSospechosos.cpp
        GestorSospechosos.h
)
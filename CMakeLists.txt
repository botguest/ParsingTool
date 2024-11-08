cmake_minimum_required(VERSION 3.24)
project(PROJ2 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-pedantic -Wall -Werror -Wextra)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(PROJ2 main.c)

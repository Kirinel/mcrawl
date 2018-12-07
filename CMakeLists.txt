cmake_minimum_required(VERSION 3.10)
project(mcrawl C)

set(CMAKE_C_STANDARD 99)

add_executable(mcrawl main.c parsing.c parsing.h)
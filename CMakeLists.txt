cmake_minimum_required(VERSION 3.12)
project(vs_plugin)

set(CMAKE_C_STANDARD 99)

add_library(colortools SHARED show.c)
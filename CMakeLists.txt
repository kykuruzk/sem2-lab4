cmake_minimum_required(VERSION 3.27)
project(lab4)
MATH(EXPR stack_size "64 * 1024 * 1024") # 32 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp
        Tree.h
        Errors.h
        Set.h
        Menu.h
        SetTest.h
        TreeTest.h
        student.h)

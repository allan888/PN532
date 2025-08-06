cmake_minimum_required(VERSION 3.28)
project(PN532 C)

set(CMAKE_CXX_STANDARD 11)  # 强制使用 C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 必须支持 C++11
set(CMAKE_C_STANDARD 23)

add_executable(PN532 main.c
        pn532.c
        pn532.h)

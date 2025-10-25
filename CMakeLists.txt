cmake_minimum_required(VERSION 3.23)

project(ASD LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror -pedantic)

add_subdirectory(src)

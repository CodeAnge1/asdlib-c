cmake_minimum_required(VERSION 3.23)

project(ASD LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror -pedantic)

add_subdirectory(src)

add_library(ASD_LIB INTERFACE)

target_link_libraries(ASD_LIB
  INTERFACE
    singly_linked_list
    stack
    queue
)

target_include_directories(ASD_LIB INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
	$<INSTALL_INTERFACE:include>
)

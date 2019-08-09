cmake_minimum_required(VERSION 3.14)
project(Hanoi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS -Wall )
set(CMAKE_C_FLAGS -Werror)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(${PROJECT_NAME} source.c tour.c)
target_link_libraries( ${PROJECT_NAME}  ${CURSES_LIBRARIES} )
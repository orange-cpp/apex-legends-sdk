cmake_minimum_required(VERSION 3.26)

project(apex-sdk)
add_library(apex-sdk source/EntityList.cpp)
add_subdirectory(extlibs)
add_subdirectory(source)
target_include_directories(apex-sdk PUBLIC include)
target_compile_options(apex-sdk PRIVATE -Werror -Wall -Wextra -pedantic-errors)
target_link_libraries(apex-sdk PUBLIC uml)
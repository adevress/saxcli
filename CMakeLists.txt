cmake_minimum_required(VERSION 3.20)
project(reflecli VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


include(CTest)

if(NOT CMAKE_BUILD_TYPE)
    set(set CMAKE_BUILD_TYPE "RelWithDebInfo" FORCE)
endif()


list(APPEND sax_cli_src "src/reflecli.cpp")
list(APPEND sax_cli_headers "include/reflecli/reflecli.hpp")


# Library
add_library(reflecli_lib
    ${sax_cli_src}
    ${sax_cli_headers}
)

target_include_directories(reflecli_lib PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(reflecli_lib PUBLIC fmt::fmt doctest)
target_compile_definitions(reflecli_lib PRIVATE DOCTEST_CONFIG_DISABLE)

add_executable(test_reflecli
    ${sax_cli_src}
    ${sax_cli_headers}
    "tests/doctest_main.cpp"
)
target_link_libraries(test_reflecli PUBLIC doctest fmt::fmt)
target_include_directories(test_reflecli PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME test_reflecli COMMAND test_reflecli)

# Alias
add_library(reflecli::reflecli ALIAS reflecli_lib)

add_subdirectory(external)
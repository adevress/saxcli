cmake_minimum_required(VERSION 3.20)
project(saxcli VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


include(CTest)

if(NOT CMAKE_BUILD_TYPE)
    set(set CMAKE_BUILD_TYPE "RelWithDebInfo" FORCE)
endif()


list(APPEND sax_cli_src "src/saxcli.cpp")
list(APPEND sax_cli_headers "include/saxcli/saxcli.hpp")


# Library
add_library(saxcli_lib
    ${sax_cli_src}
    ${sax_cli_headers}
)

target_include_directories(saxcli_lib PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(saxcli_lib PUBLIC fmt::fmt expected function-ref)
target_compile_definitions(saxcli_lib PRIVATE DOCTEST_CONFIG_DISABLE)

add_executable(test_saxcli
    ${sax_cli_src}
    ${sax_cli_headers}
    "tests/doctest_main.cpp"
)
target_link_libraries(test_saxcli PUBLIC doctest expected fmt::fmt)
target_include_directories(test_saxcli PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME test_saxcli COMMAND test_saxcli)

# Alias
add_library(saxcli::saxcli ALIAS saxcli_lib)

add_subdirectory(external)
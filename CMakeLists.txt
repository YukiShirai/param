cmake_minimum_required(VERSION 3.1)

add_library(param
            param.cpp
            )
set_target_properties(param PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(param INTERFACE 
                            ${CMAKE_CURRENT_SOURCE_DIR})

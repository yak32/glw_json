cmake_minimum_required(VERSION 2.8)
PROJECT(glw_json)
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/../../googletest/ )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/../../googletest/include/ )
ADD_EXECUTABLE (tests tests.cpp )
ADD_EXECUTABLE (performnce_test performance_test.cpp )



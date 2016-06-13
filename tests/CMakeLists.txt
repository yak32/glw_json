cmake_minimum_required(VERSION 2.8)
PROJECT(glw_json)
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/googletest/ )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/googletest/include/ )

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

ADD_EXECUTABLE (tests tests.cpp )
ADD_EXECUTABLE (performance_test performance_test.cpp )



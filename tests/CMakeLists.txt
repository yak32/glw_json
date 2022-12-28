CMAKE_MINIMUM_REQUIRED(VERSION 3.5 FATAL_ERROR)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(submodules/googletest)
ADD_SUBDIRECTORY(submodules/googlebenchmark)
ADD_SUBDIRECTORY(submodules/rapidjson)

INCLUDE_DIRECTORIES(submodules/googletest/googletest/include)
INCLUDE_DIRECTORIES(submodules/googletest/googletest/src)
INCLUDE_DIRECTORIES(submodules/googlebenchmark/include)
INCLUDE_DIRECTORIES(submodules/rapidjson/include)

ADD_EXECUTABLE (tests tests.cpp )

IF(NOT WIN32)
	SET(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
	SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
	SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")
	MESSAGE("Generating coverage!!")
ENDIF()

LINK_DIRECTORIES(${GBENCHMARK_LIBS_DIR})

# ADD_EXECUTABLE (benchmark_test benchmark.cpp )
# ADD_DEPENDENCIES(benchmark_test benchmark rapidjson)
# TARGET_LINK_LIBRARIES(benchmark_test benchmark)

# IF(WIN32)
# 	TARGET_LINK_LIBRARIES(benchmark_test Shlwapi.lib)
# ENDIF()

IF(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")
	SET(THREADS_PREFER_PTHREAD_FLAG ON)
	FIND_PACKAGE(Threads REQUIRED)
	TARGET_LINK_LIBRARIES(tests Threads::Threads)
	# TARGET_LINK_LIBRARIES(benchmark_test Threads::Threads)
ENDIF()

ADD_TEST(test1 tests)
ADD_DEPENDENCIES(tests gtest)
TARGET_LINK_LIBRARIES(tests gtest)

add_custom_command(
	TARGET tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:tests>
	${CMAKE_CURRENT_SOURCE_DIR}/)




# INSTALL(TARGETS benchmark_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../install/)
# INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/test.json ${CMAKE_CURRENT_SOURCE_DIR}/data.json
#  		DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../install/)


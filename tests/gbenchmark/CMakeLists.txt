CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(gbenchmark_builder C CXX)
INCLUDE(ExternalProject)

EXTERNALPROJECT_ADD(gbenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=Libs
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=Libs
        -DGOOGLETEST_PATH=${GOOGLETEST_PATH}
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        # Disable install step
        INSTALL_COMMAND "")

ADD_DEPENDENCIES(gbenchmark googletest)

# Specify include dir
EXTERNALPROJECT_GET_PROPERTY(gbenchmark source_dir)
SET(GBENCHMARK_INCLUDE_DIR ${source_dir}/include PARENT_SCOPE)

# Specify MainTest's link libraries
EXTERNALPROJECT_GET_PROPERTY(gbenchmark binary_dir)

IF(WIN32)
	SET(GBENCHMARK_LIBS_DIR ${binary_dir}/src/Libs PARENT_SCOPE)
ELSE()
	SET(GBENCHMARK_LIBS_DIR ${binary_dir}/src/ PARENT_SCOPE)
ENDIF()


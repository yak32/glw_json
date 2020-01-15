CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(rapid_json_builder C CXX)
INCLUDE(ExternalProject)

EXTERNALPROJECT_ADD(rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND "")

# Specify include dir
EXTERNALPROJECT_GET_PROPERTY(rapidjson source_dir)
SET(RAPIDJSON_INCLUDE_DIR ${source_dir}/include PARENT_SCOPE)


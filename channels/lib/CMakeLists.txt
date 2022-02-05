cmake_minimum_required(VERSION 3.0)

project(channels)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES "src/*.c*")
file(GLOB HDR_FILES "include/*.h*")

set(CHANNELS_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

include_directories(include)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
cmake_minimum_required(VERSION 3.13)
project(EsGateToHard VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "-fno-rtti")
set(CMAKE_BUILD_PARALLEL_LEVEL 3)

message("\n====== ${PROJECT_NAME} =======")
message("CMake version: \t" ${CMAKE_VERSION})
message("CMake CXX_FLAGS: \t" ${CMAKE_CXX_FLAGS})
message("Project version: \t" ${PROJECT_VERSION})
message("C++ standart: \t" ${CMAKE_CXX_STANDARD})
message("Compile definitions: \t" ${DEFINITIONS})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("Project dir: \t\t" ${PROJECT_SOURCE_DIR})

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	set(BUILD_MODE "debug")
else()
	set(BUILD_MODE "release")
endif()
message("Mode: \t" ${CMAKE_BUILD_TYPE})

set(BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../build/${BUILD_MODE}/${PROJECT_NAME})
set(CMAKE_BINARY_DIR ${BUILD_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
message("Path to binary file: \t" ${CMAKE_BINARY_DIR})

set(PROJECT_SRCS
		${PROJECT_SOURCE_DIR}/main.cpp
		${PROJECT_SOURCE_DIR}/usetty.hpp
		)
add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

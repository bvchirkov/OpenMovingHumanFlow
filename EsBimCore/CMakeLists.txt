cmake_minimum_required(VERSION 3.16)
project(EsBimCore
            VERSION 0.1.0
            LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS    OFF)
set(CMAKE_VERBOSE_MAKEFILE  ON)

set(CMAKE_CXX_COMPILER          g++-10)
set(CMAKE_C_COMPILER            gcc-10)
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#add_compile_options(-std=gnu++2a)

message("\n====== ${PROJECT_NAME} =======")
message("CMake version: \t" ${CMAKE_VERSION})
message("CMake CXX_FLAGS: \t" ${CMAKE_CXX_FLAGS})
message("Project version: \t" ${PROJECT_VERSION})
message("C++ standart: \t" ${CMAKE_CXX_STANDARD})

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
        JsonView/BimRoot.cpp
        JsonView/BimLevels.cpp
        JsonView/BimAddrInfo.cpp
        JsonView/BimDoorElement.cpp
        JsonView/BimRoomElement.cpp
        JsonView/BimBaseElement.cpp
        JsonView/BimElementSign.cpp
        JsonView/BimPolygonPoint.cpp
        JsonView/BimPolygonRing.cpp
        JsonView/BimStairElement.cpp
        JsonView/BimDevices.cpp
        JsonView/BimDevicesTypes.cpp
        Room.cpp
        Door.cpp
        Stair.cpp
        PolygonTools.cpp
        BaseElement.cpp
        Safety.cpp
        Base.cpp
        BaseDoor.cpp )

include_directories(JsonView)
include_directories(Devices)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})

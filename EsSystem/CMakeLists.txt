cmake_minimum_required(VERSION 3.16)

project(EsSystem
            VERSION 0.1.0
            LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_PARALLEL_LEVEL 3)
set(CMAKE_VERBOSE_MAKEFILE      ON)

set(CMAKE_CXX_COMPILER          g++-10)
set(CMAKE_C_COMPILER            gcc-10)
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(DEFINITIONS BIG_PRINT) #Для вывода дополнительной информации
add_compile_definitions(${DEFINITIONS}) #Для вывода дополнительной информации

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

set(EXTRAS ${CMAKE_CURRENT_SOURCE_DIR}/../../extras)
message("Path to EXTRAS: \t" ${EXTRAS})
set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../../build/${BUILD_MODE})
message("Path to LIBS: \t" ${LIBS})

link_directories(
		${EXTRAS}/GpCore
		${LIBS}/EsBimCore
		${LIBS}/EsModelOfMoving
		${LIBS}/EsOutputStruct
		)

# Find all *.cpp and *.hpp files in project
FILE (GLOB_RECURSE SRC *.cpp)
FILE (GLOB_RECURSE SRC_INCLUDE *.hpp)

add_executable(${PROJECT_NAME} ${SRC})

find_package(Boost 1.67 REQUIRED
                COMPONENTS program_options coroutine context thread system)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::program_options
        Boost::coroutine
        Boost::context
        Boost::thread
        Boost::system
        pthread
        GpCore
        EsBimCore
        EsModelOfMoving
        EsOutputStruct
    )

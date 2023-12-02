cmake_minimum_required(VERSION 3.26)
project(TextEditor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_PROJECT include/TextEditor)
set(INCLUDE_THIRD_PARTIES dependencies/include)
set(INCLUDE ${INCLUDE_PROJECT} ${INCLUDE_THIRD_PARTIES})
set(LIBS dependencies/lib/OIS)

file(GLOB SRC "src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE})

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LIBS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE libOIS.1.5.1.dylib)

cmake_minimum_required(VERSION 3.26)
project(TextEditor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("system: ${CMAKE_SYSTEM_NAME}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    execute_process(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
    message("architecture: ${ARCHITECTURE}")
else ()
    error("platforms except macos are not yet supported :(")
endif ()

set(INCLUDE_PROJECT include/TextEditor)
set(INCLUDE_THIRD_PARTIES dependencies/include)
set(INCLUDE ${INCLUDE_PROJECT} ${INCLUDE_THIRD_PARTIES})
set(LIB_ROOT dependencies/lib)
set(SCRIPTS_ROOT scripts)

file(GLOB NCURSES "${LIB_ROOT}/ncurses/${CMAKE_SYSTEM_NAME}/*.a")
file(GLOB SRC "src/*.cpp")

list(APPEND LIB_LIST ${NCURSES})


set(TERMINFO_DIR ${LIB_ROOT}/ncurses/${CMAKE_SYSTEM_NAME}/terminfo)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

file(COPY ${TERMINFO_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(TERMINFO_PATH "${CMAKE_CURRENT_BINARY_DIR}/terminfo")
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE TERMINFO_PATH="${TERMINFO_PATH}")
message("terminfo dir is at: ${TERMINFO_PATH}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

endif ()

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE})
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_ROOT})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_LIST})



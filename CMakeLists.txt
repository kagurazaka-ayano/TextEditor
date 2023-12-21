cmake_minimum_required(VERSION 3.26)
project(TextEditor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("system: ${CMAKE_SYSTEM_NAME}")

set(INCLUDE_PROJECT include/TextEditor)
set(LIB_ROOT dependencies/lib)

# for wchar support
add_compile_definitions(NCURSES_WIDECHAR)
add_compile_definitions(_XOPEN_SOURCE_EXTENDED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    execute_process(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
    message("architecture: ${ARCHITECTURE}")
    set(INCLUDE_THIRD_PARTIES "dependencies/include/Darwin")
    file(GLOB NCURSES "${LIB_ROOT}/ncurses/Darwin/*.a")
    file(GLOB FMT "${LIB_ROOT}/fmt/Darwin/*.a")
elseif (MINGW)
    message("using mingw")
    set(INCLUDE_THIRD_PARTIES "dependencies/include/mingw")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        message("Building for: 64bit")
        set(NCURSES "${LIB_ROOT}/ncurses/mingw64/*.a")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        message("Building for: 32bit")
        set(NCURSES "${LIB_ROOT}/ncurses/mingw32/*.a")
    endif ()
elseif (LINUX)
    message("linux is not yet being supported :(")
elseif (MSVC)
    error("MSVC is not supported")
endif ()

set(INCLUDE ${INCLUDE_PROJECT} ${INCLUDE_THIRD_PARTIES})
set(SCRIPTS_ROOT scripts)

file(GLOB SRC "src/*.cpp")

list(APPEND LIB_LIST ${NCURSES})
list(APPEND LIB_LIST ${FMT})

set(TERMINFO_DIR ${LIB_ROOT}/ncurses/terminfo)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

file(COPY ${TERMINFO_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(TERMINFO_PATH "${CMAKE_CURRENT_BINARY_DIR}/terminfo")
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE TERMINFO_PATH="${TERMINFO_PATH}")
message("terminfo dir is at: ${TERMINFO_PATH}")

message(${SRC})
message(${INCLUDE})
message(${LIB_ROOT})
message(${LIB_LIST})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE})
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_ROOT})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_LIST})



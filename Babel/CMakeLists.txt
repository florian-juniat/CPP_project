cmake_minimum_required(VERSION 2.8.12)
project(Babel)

if (UNIX)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else (UNIX)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.9/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()
endif (UNIX)

if (UNIX)
    set(CXXFLAGS "-Wall -Werror")
    add_definitions("-fPIC" ${CXXFLAGS})
endif (UNIX)

add_subdirectory(server)
add_subdirectory(graph)

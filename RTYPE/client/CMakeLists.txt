cmake_minimum_required(VERSION 2.8.12)
project(Rtype)

include_directories(include)

add_executable(r-type_client
    src/main.cpp
    src/handle.cpp
    src/data.cpp
)

target_link_libraries(r-type_client
    -lboost_system
    -lboost_thread
    -pthread
    -lsfml-graphics
    -lsfml-window
    -lsfml-system
)

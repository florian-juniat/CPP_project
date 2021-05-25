cmake_minimum_required(VERSION 2.8.12)
project(Babel)

include_directories(include)

add_executable(babel_server
    src/main.cpp
    src/serveur.cpp
    src/communicate.cpp
    src/contact.cpp
    src/list_connect.cpp
)

target_link_libraries(babel_server
    -lboost_system
    -pthread
)

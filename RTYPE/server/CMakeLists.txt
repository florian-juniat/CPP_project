cmake_minimum_required(VERSION 2.8.12)
project(Rtype)

include_directories(include)

add_executable(r-type_server
    src/main.cpp
    src/action.cpp
    src/client.cpp
    src/party.cpp
    src/tab_action.cpp
    src/tab_client.cpp
    src/data.cpp
    src/tab_party.cpp
    src/handle.cpp
    src/Colision.cpp
    src/Draw.cpp
    src/Enemy.cpp
    src/Engine.cpp
    src/Input.cpp
    src/Lazer_enemy.cpp
    src/Lazer_player.cpp
    src/Player.cpp
    src/Update.cpp
    src/send_file.cpp
    src/Obstacle.cpp
)

target_link_libraries(r-type_server
    -lboost_system
    -lboost_thread
    -pthread
    -lsfml-graphics
    -lsfml-window
    -lsfml-system
)

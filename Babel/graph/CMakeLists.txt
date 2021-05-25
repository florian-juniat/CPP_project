cmake_minimum_required(VERSION 2.8.12)
project(Babel)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui)

add_executable( babel_client
    main.cpp
    mainwindow.cpp
    customcallbutton.cpp
    customcallbutton.h
    customlabelcontacts.cpp
    customlabelcontacts.h
    customwidget.cpp
    customwidget.h
    customwidgettwo.cpp
    customwidgettwo.h
    labelcontactlist.cpp
    labelcontactlist.h
    mainwindow.ui
    client.cpp
    client.h
)

target_link_libraries(babel_client
    Qt5::Widgets
    Qt5::Gui
    -pthread
)

#-------------------------------------------------
#
# Project created by QtCreator 2019-09-24T10:11:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = babel
TEMPLATE = app

LIBS += -L/usr/share/boost_1_39_0/stage/lib -lboost_thread -lboost_system -ljack -pthread

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    customcallbutton.cpp \
    customwidget.cpp \
    customwidgettwo.cpp \
    customlabelcontacts.cpp \
    labelcontactlist.cpp \
    client.cpp

HEADERS += \
        mainwindow.h \
    customcallbutton.h \
    customwidget.h \
    customwidgettwo.h \
    customlabelcontacts.h \
    labelcontactlist.h

FORMS += \
        mainwindow.ui

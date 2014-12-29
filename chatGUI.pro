#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T17:19:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatGUI
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    chat.cpp\
    usefull.cpp

HEADERS  += login.h \
    chat.h\
    usefull.h

FORMS    += login.ui \
    chat.ui

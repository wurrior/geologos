#-------------------------------------------------
#
# Project created by QtCreator 2013-09-04T17:39:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = geologos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingswindow.cpp \
    control.cpp

HEADERS  += mainwindow.h \
    settingswindow.h \
    control.h

FORMS    += mainwindow.ui \
    settingswindow.ui

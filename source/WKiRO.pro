#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T14:55:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WKiRO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "/usr/local/include/"

LIBS += `pkg-config --libs opencv`

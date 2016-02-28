#-------------------------------------------------
#
# Project created by QtCreator 2016-02-19T01:54:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmicableNumbers
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp \
    conststrings.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    worker.h \
    conststrings.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    dialogabout.ui

macx:ICON = my_app.icns

RC_FILE = myapp.rc

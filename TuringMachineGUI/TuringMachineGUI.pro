#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T14:54:20
#
#-------------------------------------------------

CONFIG += c++14

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TuringMachineGUI
TEMPLATE = app


SOURCES += main.cpp \
        TMMainWindow.cpp \
        ../src/TMTape.cpp \
        ../src/TMAPI.cpp \
        ../src/TMStateWatcher.cpp \
        ../src/TMFileParser.cpp \
        ../src/TMTuringMachine.cpp \
        ../src/TMCommandParser.cpp \
        ../src/TMControlGraph.cpp \
        ../src/TMAlphabet.cpp \
    GraphTableWidget.cpp \
    TMExceptionDialog.cpp

HEADERS  += TMMainWindow.h \
    GraphTableWidget.h \
    TMExceptionDialog.h

INCLUDEPATH += ../include

FORMS    += TMMainWindow.ui \
    TMExceptionDialog.ui

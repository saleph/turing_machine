CONFIG += c++14

TARGET = TuringMachine
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    src/TMAlphabet.cpp \
    src/TMAPI.cpp \
    src/TMCommandParser.cpp \
    src/TMControlGraph.cpp \
    src/TMFileParser.cpp \
    src/TMStateWatcher.cpp \
    src/TMTape.cpp \
    src/TMTuringMachine.cpp

HEADERS += \
    include/LazyInitializator.h \
    include/TMAlphabet.h \
    include/TMAPI.h \
    include/TMCommand.h \
    include/TMCommandParser.h \
    include/TMControlGraph.h \
    include/TMExceptions.h \
    include/TMFileParser.h \
    include/TMHead.h \
    include/TMHeadMoveType.h \
    include/TMStateWatcher.h \
    include/TMStringCharPair.h \
    include/TMTape.h \
    include/TMTuringMachine.h

INCLUDEPATH += include
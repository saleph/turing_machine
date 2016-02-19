CONFIG += c++14

TARGET = TuringMachineTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \ 
    UnitTests/TMAlphabetTests.cpp \
    UnitTests/TMAPITests.cpp \
    UnitTests/TMCommandParserTests.cpp \
    UnitTests/TMControlGraphTests.cpp \
    UnitTests/TMFileParserTests.cpp \
    UnitTests/TMStringCharPairHashPolicyTests.cpp \
    UnitTests/TMTapeTests.cpp \
    UnitTests/TMTuringMachineTests.cpp \
    ../src/TMTape.cpp \
    ../src/TMAPI.cpp \
    ../src/TMStateWatcher.cpp \
    ../src/TMFileParser.cpp \
    ../src/TMTuringMachine.cpp \
    ../src/TMCommandParser.cpp \
    ../src/TMControlGraph.cpp \
    ../src/TMAlphabet.cpp

INCLUDEPATH += \
    ../include \
    /usr/local/include/boost/
    
LIBS += \
    -lboost_unit_test_framework \
    -lboost_filesystem \
    -lboost_system
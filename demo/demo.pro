TEMPLATE = app

CONFIG += console c++1z strict_c++
CONFIG -= app_bundle qt

QMAKE_CXXFLAGS += -pedantic-errors -Wall
QMAKE_CXXFLAGS_DEBUG += -fsanitize=address,undefined
QMAKE_LFLAGS_DEBUG += -fsanitize=address,undefined

SOURCES += main.cpp ../common/buffer_gap.cpp

HEADERS += ../common/buffer_gap.hpp

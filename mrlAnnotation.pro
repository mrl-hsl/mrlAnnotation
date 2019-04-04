#-------------------------------------------------
#
# Project created by QtCreator 2019-01-19T13:06:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mrlAnnotation
TEMPLATE = app

LIBS += `pkg-config opencv --libs`
CONFIG += c++11

SOURCES += main.cpp\
        src/tool.cpp \
        src/sample.cpp \
        src/dataset.cpp \
        src/EGBS.cpp src/DisjointSet.cpp src/graph.cpp \
    src/mqlabel.cpp \
    src/selector.cpp \
    src/circle.cpp \
    src/polygon.cpp \
    src/line.cpp

HEADERS  += src/tool.h \
    src/dataset.h \
    src/EGBS.h src/DisjointSet.h src/graph.h \
    src/sample.h \
    src/mqlabel.h \
    src/selector.h \
    src/circle.h \
    src/polygon.h \
    src/line.h

FORMS    += tool.ui

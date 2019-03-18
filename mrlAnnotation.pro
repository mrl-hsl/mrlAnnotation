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
        tool.cpp \
        sample.cpp \
        dataset.cpp \
        EGBS.cpp DisjointSet.cpp graph.cpp \
    mqlabel.cpp \
    selector.cpp \
    circle.cpp \
    polygon.cpp \
    line.cpp

HEADERS  += tool.h \
    dataset.h \
    EGBS.h DisjointSet.h graph.h \
    sample.h \
    mqlabel.h \
    selector.h \
    circle.h \
    polygon.h \
    line.h

FORMS    += tool.ui

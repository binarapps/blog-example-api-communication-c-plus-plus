#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T11:11:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
TARGET = 2-ParsingJson
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jsonparser.cpp

HEADERS  += mainwindow.h \
    jsonparser.h

FORMS    += mainwindow.ui

LIBS += -ljson \
        -lcryptopp
INCLUDEPATH += /usr/local/include/

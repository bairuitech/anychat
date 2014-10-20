#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T10:10:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloAnyChat_qt
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
INCLUDEPATH += $$PWD/../../../../sdk/client/c++/
DEPENDPATH +=  $$PWD/../../../../sdk/client/c++/

#ifdef WIN32
LIBS += -L$$PWD/../../../../bin/client/ -lBRAnyChatCore

#else UNIX
#LIBS += -L$$PWD/../../../../bin/client/ -lanychatcore



#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T10:10:52
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloAnyChatCloud_qt
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
INCLUDEPATH += $$PWD/../../../../sdk/client/c++/
DEPENDPATH +=  $$PWD/../../../../sdk/client/c++/

LIBS += -L$$PWD/../../../../bin/client/ -lanychatcore


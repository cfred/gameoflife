#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T20:25:16
#
#-------------------------------------------------

QT       += core gui
#CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
    cell.cpp \
    gameoflife.cpp

HEADERS  += \
    cell.h \
    gameoflife.h

FORMS    += gameoflife.ui

#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T19:30:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = crypto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    caesarcipher.cpp \
    cryptohelper.cpp

HEADERS  += mainwindow.h \
    caesarcipher.h \
    cryptohelper.h

FORMS    += mainwindow.ui \
    caesarcipher.ui

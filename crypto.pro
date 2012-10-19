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
    cryptohelper.cpp \
    caesarafcipher.cpp \
    caesarkwcipher.cpp \
    playfaircipher.cpp \
    trithemiuscipher.cpp \
    vigenerecipher.cpp

HEADERS  += mainwindow.h \
    caesarcipher.h \
    cryptohelper.h \
    caesarafcipher.h \
    caesarkwcipher.h \
    playfaircipher.h \
    trithemiuscipher.h \
    vigenerecipher.h

FORMS    += mainwindow.ui \
    caesarcipher.ui \
    caesarafcipher.ui \
    caesarkwcipher.ui \
    playfaircipher.ui \
    trithemiuscipher.ui \
    vigenerecipher.ui

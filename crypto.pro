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
    vigenerecipher.cpp \
    magicsquarecipher.cpp \
    wheatstonecipher.cpp \
    settingsdialog.cpp \
    aboutdialog.cpp \
    abstractcipherview.cpp

HEADERS  += mainwindow.h \
    caesarcipher.h \
    cryptohelper.h \
    caesarafcipher.h \
    caesarkwcipher.h \
    playfaircipher.h \
    trithemiuscipher.h \
    vigenerecipher.h \
    magicsquarecipher.h \
    wheatstonecipher.h \
    settingsdialog.h \
    aboutdialog.h \
    abstractcipherview.h

FORMS    += mainwindow.ui \
    caesarcipher.ui \
    caesarafcipher.ui \
    caesarkwcipher.ui \
    playfaircipher.ui \
    trithemiuscipher.ui \
    vigenerecipher.ui \
    magicsquarecipher.ui \
    wheatstonecipher.ui \
    settingsdialog.ui \
    aboutdialog.ui \
    abstractcipherview.ui

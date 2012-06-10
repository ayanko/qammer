#-------------------------------------------------
#
# Project created by QtCreator 2012-06-09T14:52:29
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qammer
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/logindialog.cpp \
    qt-json/json.cpp

HEADERS  += src/mainwindow.h \
    src/logindialog.h \
    qt-json/json.h

FORMS    += src/mainwindow.ui \
    src/logindialog.ui

RESOURCES += \
    src/qammer.qrc

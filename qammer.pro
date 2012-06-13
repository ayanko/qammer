#-------------------------------------------------
#
# Project created by QtCreator 2012-06-09T14:52:29
#
#-------------------------------------------------

QT += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qammer
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/logindialog.cpp \
    qt-json/json.cpp \
    src/messagewidget.cpp \
    src/client.cpp \
    src/message.cpp \
    src/user.cpp \
    src/group.cpp \
    src/messagedialog.cpp

HEADERS  += src/mainwindow.h \
    src/logindialog.h \
    qt-json/json.h \
    src/messagewidget.h \
    src/client.h \
    src/message.h \
    src/user.h \
    src/group.h \
    src/messagedialog.h

FORMS    += src/mainwindow.ui \
    src/logindialog.ui \
    src/messagewidget.ui \
    src/messagedialog.ui

RESOURCES += \
    qammer.qrc

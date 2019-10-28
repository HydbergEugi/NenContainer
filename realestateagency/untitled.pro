#-------------------------------------------------
#
# Project created by QtCreator 2019-05-20T00:34:38
#
#-------------------------------------------------

QT       += core gui
QT +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        agreement_accept.cpp \
        autorization.cpp \
        comboboxitemdelegate.cpp \
        database.cpp \
        dialog.cpp \
        floor_covering.cpp \
        locality.cpp \
        main.cpp \
        mainwindow.cpp \
        purchases.cpp \
        registration.cpp \
        users.cpp

HEADERS += \
        agreement_accept.h \
        autorization.h \
        comboboxitemdelegate.h \
        database.h \
        dialog.h \
        floor_covering.h \
        locality.h \
        mainwindow.h \
        purchases.h \
        registration.h \
        users.h

FORMS += \
        agreement_accept.ui \
        autorization.ui \
        comboboxdelegate.ui \
        dialog.ui \
        floor_covering.ui \
        locality.ui \
        mainwindow.ui \
        purchases.ui \
        registration.ui \
        users.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

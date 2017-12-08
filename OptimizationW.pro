#-------------------------------------------------
#
# Project created by QtCreator 2017-11-23T21:45:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OptimizationW
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    area.cpp \
    optimization.cpp \
    const.cpp \
    function.cpp \
    stopcriterion.cpp \
    stdafx.cpp \
    dialog.cpp \
    dialogfunc.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    area.h \
    const.h \
    function.h \
    optimization.h \
    stopcriterion.h \
    stdafx.h \
    targetver.h \
    dialog.h \
    dialogfunc.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialogfunc.ui

DISTFILES += \
    icon1.png

RESOURCES += \
    myres.qrc

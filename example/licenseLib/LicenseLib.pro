#-------------------------------------------------
#
# Project created by QtCreator 2018-11-23T11:02:00
#
#-------------------------------------------------

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = computerconfiguration
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    linuxOperation.h.cpp

HEADERS  += widget.h \
    linuxOperation.h \
    linuxfactory.h \
    cpuinfo.h

FORMS    += widget.ui

DISTFILES += \
    license/license.pri

RESOURCES += \
    res/splash.qrc

LIBS += "$$PWD\lib\license.lib"

INCLUDEPATH   += "$$PWD\include" \
                 "$$PWD\include\src"

#INCLUDEPATH   += "H:\Myself\license\include" \
#                 "H:\Myself\license\include\src"



message("$$(PWD)/include/src")

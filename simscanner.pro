#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T20:05:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simscanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scanmodel.cpp \
    pe_parser/entropy.cpp \
    pe_parser/pe32.cpp \
    pe_parser/peParser.cpp \
    sqlite/sqlite3.c \
    sqlite/sqlite3.c \
    fpropsdialog.cpp \
    dbprofile.cpp

HEADERS  += mainwindow.h \
    scanmodel.h \
    pe_parser/entropy.h \
    pe_parser/pe32.h \
    pe_parser/peParser.h \
    sqlite/sqlite3.h \
    fpropsdialog.h \
    dbprofile.h

FORMS    += mainwindow.ui \
    fpropsdialog.ui

RESOURCES += \
    simscanner.qrc

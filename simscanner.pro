#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T20:05:24
#
#-------------------------------------------------

QT       += core gui charts

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
    dbprofile.cpp \
    qpefilemenu.cpp \
    qpefile.cpp \
    qnnwrapper.cpp

HEADERS  += mainwindow.h \
    scanmodel.h \
    pe_parser/entropy.h \
    pe_parser/pe32.h \
    pe_parser/peParser.h \
    sqlite/sqlite3.h \
    fpropsdialog.h \
    dbprofile.h \
    qpefilemenu.h \
    qpefile.h \
    qnnwrapper.h

FORMS    += mainwindow.ui \
    fpropsdialog.ui

RESOURCES += \
    simscanner.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lopennn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lopennn
else:unix: LIBS += -L$$PWD/libs/ -lopennn

INCLUDEPATH += $$PWD/../OpenNN/opennn
DEPENDPATH += $$PWD/../OpenNN/opennn

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libopennn.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libopennn.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/opennn.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/opennn.lib
else:unix: PRE_TARGETDEPS += $$PWD/libs/libopennn.a

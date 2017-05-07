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
    qssnn.cpp \
    aboutdialog.cpp \
    addnewdialog.cpp \
    entropychartview.cpp \
    entropyflowwindow.cpp \
    entropy_parser.cpp \
    qchartlayout.cpp \
    structuretree.cpp \
    entropychartitem.cpp \
    spropsdialog.cpp \
    entropynn.cpp \
    samplestree.cpp \
    sectionitem.cpp

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
    qssnn.h \
    aboutdialog.h \
    addnewdialog.h \
    macro.h \
    entropychartview.h \
    entropyflowwindow.h \
    entropy_parser.h \
    qchartlayout.h \
    structuretree.h \
    entropychartitem.h \
    spropsdialog.h \
    entropynn.h \
    samplestree.h \
    sectionitem.h

FORMS    += mainwindow.ui \
    fpropsdialog.ui \
    aboutdialog.ui \
    addnewdialog.ui \
    spropsdialog.ui

RESOURCES += \
    simscanner.qrc

SUBDIRS += \
    opennn/opennn.pro

DISTFILES += \
    opennn/utilities.cu \
    opennn/CMakeLists.txt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/tinyxml2/release/ -ltinyxml2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/tinyxml2/debug/ -ltinyxml2
else:unix: LIBS += -L$$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/tinyxml2/ -ltinyxml2

INCLUDEPATH += $$PWD/../OpenNN/tinyxml2
DEPENDPATH += $$PWD/../OpenNN/tinyxml2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/tinyxml2/release/libtinyxml2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/tinyxml2/debug/libtinyxml2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/tinyxml2/release/tinyxml2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/tinyxml2/debug/tinyxml2.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/tinyxml2/libtinyxml2.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Release/opennn/release/ -lopennn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/opennn/debug/ -lopennn
else:unix: LIBS += -L$$PWD/../build-opennn-Desktop_Qt_5_7_0_MSVC2013_32bit-Debug/opennn/ -lopennn

INCLUDEPATH += $$PWD/../OpenNN/opennn
DEPENDPATH += $$PWD/../OpenNN/opennn

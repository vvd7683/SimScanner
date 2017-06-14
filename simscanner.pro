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
    fpropsdialog.cpp \
    qpefilemenu.cpp \
    qpefile.cpp \
    aboutdialog.cpp \
    addnewdialog.cpp \
    entropychartview.cpp \
    entropyflowwindow.cpp \
    entropy_parser.cpp \
    qchartlayout.cpp \
    structuretree.cpp \
    entropychartitem.cpp \
    spropsdialog.cpp \
    samplestree.cpp \
    sectionitem.cpp \
    qchartdialog.cpp \
    nnprofilesdialog.cpp \
    selectedsampleitem.cpp \
    ss_defs.cpp \
    nnitem.cpp

HEADERS  += mainwindow.h \
    scanmodel.h \
    pe_parser/entropy.h \
    pe_parser/pe32.h \
    pe_parser/peParser.h \
    fpropsdialog.h \
    qpefilemenu.h \
    qpefile.h \
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
    samplestree.h \
    sectionitem.h \
    qchartdialog.h \
    ss_types.h \
    nnprofilesdialog.h \
    selectedsampleitem.h \
    ss_defs.h \
    nnitem.h

FORMS    += mainwindow.ui \
    fpropsdialog.ui \
    aboutdialog.ui \
    addnewdialog.ui \
    spropsdialog.ui \
    nnprofilesdialog.ui

RESOURCES += \
    simscanner.qrc

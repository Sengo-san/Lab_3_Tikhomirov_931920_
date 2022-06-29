QT       += core gui charts
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IGeneratorColors.cpp \
    IScanner.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DataElement.h \
    DataGraph.h \
    IOCContainer.h \
    IGeneratorQChart.h \
    Graph.h \
    GraphGenerator.h \
    IGeneratorColors.h \
    IScanner.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

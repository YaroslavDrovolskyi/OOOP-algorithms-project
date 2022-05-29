QT       += core gui
QT += gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    facadeinfo.cpp \
    factory.cpp \
    main.cpp \
    mainwindow.cpp \
    facade.cpp \
    memento.cpp \
    visitor.cpp

HEADERS += \
    facadeinfo.h \
    factory.h \
    mainwindow.h \
        facade.h \
    memento.h \
    visitor.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
















win32: LIBS += -L$$PWD/../lib/ -lalgoslib

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

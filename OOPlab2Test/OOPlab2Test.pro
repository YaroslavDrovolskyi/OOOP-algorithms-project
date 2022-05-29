QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

#HEADERS +=\
#../OOPlab2/algorithms.h

SOURCES += \
    tst_tests.cpp
 #    ../OOPlab2/algorithms.cpp
#INCLUDEPATH += ../OOPlab2




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lalgoslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lalgoslib

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib




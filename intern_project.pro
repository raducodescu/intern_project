QT += quick
CONFIG += c++14 -lpthread -lboost_system console

QMAKE_CXXFLAGS += --std=c++14 -lpthread -lboost_system

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    agent.cpp \
    airport.cpp \
    aplane.cpp \
    arequest.cpp \
    filegenerator.cpp \
    genericairport.cpp \
    landingrequest.cpp \
    planerequest.cpp \
    regularplane.cpp \
    requestconsumer.cpp \
    requestgenerator.cpp \
    takeoffrequest.cpp \
    track.cpp \
    utils.cpp \
    dummyconsumer.cpp \
    action.cpp \
    observer.cpp \
    logobserver.cpp \
    testairport.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    agent.h \
    airport.h \
    aplane.h \
    arequest.h \
    filegenerator.h \
    genericairport.h \
    landingrequest.h \
    planerequest.h \
    regularplane.h \
    requestconsumer.h \
    requestgenerator.h \
    takeoffrequest.h \
    track.h \
    utils.h \
    dummyconsumer.h \
    action.h \
    observer.h \
    logobserver.h \
    testairport.h

DISTFILES += \
    input_conf \
    requests

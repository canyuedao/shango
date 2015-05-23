TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    httpserver.cpp

RESOURCES += qml.qrc data.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

include(../../../library/libevent/libevent.pri)

HEADERS += \
    httpserver.h

DISTFILES +=


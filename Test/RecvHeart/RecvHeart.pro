TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    heart.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

include(../../../library/boost_1_58_0/boost.pri)

CONFIG += c++11

HEADERS += \
    heart.h

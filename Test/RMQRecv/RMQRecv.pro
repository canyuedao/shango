TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    rabbitmqtest.cpp \
    qrabbitmqclient.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

include(../../../library/librabbitmq/librabbitmq.pri)

HEADERS += \
    rabbitmqtest.h \
    qrabbitmqclient.h

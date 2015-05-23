TEMPLATE = app

QT += qml quick concurrent sql

SOURCES += main.cpp \
    controller/maincontroller.cpp \
    controller/transfusecontroller.cpp \
    controller/configurecontroller.cpp \
    other/networkmanager.cpp \
    other/localstore.cpp \
    other/globalobject.cpp \
	model/commonmodel.cpp \
    other/heart.cpp \
    other/analysisjson.cpp \
    other/quickjson.cpp


RESOURCES += \
            res/qml.qrc \
            res/other.qrc \
            res/image.qrc \
            res/qml_transfuse.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

include(../../library/boost_1_58_0/boost.pri)
include(../../library/librabbitmq/librabbitmq.pri)
include(../../library/qxmlrpc/qxmlrpc.pri)


DEFINES += __PROJECT__=\\\"$${PWD}\\\"

HEADERS += \
    controller/maincontroller.h \
    controller/transfusecontroller.h \
    controller/configurecontroller.h \
    other/networkmanager.h \
    other/localstore.h \
    other/globalobject.h \
	model/commonmodel.h \
    other/heart.h \
    other/analysisjson.h \
    C:/Users/Administrator/Desktop/QuickJson/quickjson.h \
    other/quickjson.h


DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

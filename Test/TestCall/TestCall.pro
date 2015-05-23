TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += res/qml.qrc \
    res/images.qrc

#OTHER_FILES += android/AndroidManifest.xml \
#        android/ic_launcher-web.png \
#        android/src/com/shango/medica/infusioncalldisplay/MainActivity.java \
#        android/res/drawable-xxhdpi/ic_launcher.png \
#        android/res/drawable-mdpi/ic_launcher.png \
#        android/res/drawable-xhdpi/ic_launcher.png \
#        android/res/drawable-xxhdpi/ic_launcher.png


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

DISTFILES += \
    android/src/com/shango/medica/infusioncalldisplay/MainActivity.java \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/drawable-xxhdpi/ic_launcher.png \
    android/res/drawable-mdpi/ic_launcher.png \
    android/res/drawable-xhdpi/ic_launcher.png \
    android/res/drawable-xxhdpi/ic_launcher.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android



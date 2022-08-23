QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    downloader.cpp \
    localcache.cpp \
    main.cpp \
    mainwindow.cpp \
    predownloadconfigwindow.cpp \
    qprogressindicator.cpp \

HEADERS += \
    downloader.h \
    localcache.h \
    mainwindow.h \
    predownloadconfigwindow.h \
    qprogressindicator.h \

FORMS += \
    mainwindow.ui \
    predownloadconfigwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc \
    style.qrc

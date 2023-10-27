QT       += core gui
INCLUDEPATH +=.\vlc-3.0.9.2\sdk\include
LIBS +=$$PWD\vlc-3.0.9.2\sdk\lib\libvlc.lib
LIBS +=$$PWD\vlc-3.0.9.2\sdk\lib\libvlccore.lib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    btnvolume.cpp \
    cbottomctrlbar.cpp \
    crightplaylist.cpp \
    dlgvolumesilder.cpp \
    framelesswidgetbase.cpp \
    main.cpp \
    playbtngroupwidget.cpp \
    titlebar.cpp \
    videowidget.cpp \
    widget.cpp

HEADERS += \
    btnvolume.h \
    cbottomctrlbar.h \
    crightplaylist.h \
    dlgvolumesilder.h \
    framelesswidgetbase.h \
    myqss.h \
    playbtngroupwidget.h \
    titlebar.h \
    videowidget.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

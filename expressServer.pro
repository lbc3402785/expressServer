#-------------------------------------------------
#
# Project created by QtCreator 2019-12-10T11:09:34
#
#-------------------------------------------------

QT       += core gui network

QT += multimedia
QT       *= xml opengl
QMAKE_CXXFLAGS+=/bigobj
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG       +=console
TARGET = expressServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
OBJECTS_DIR=$${PWD}/build


OPENCV_INCLUDE_DIRS=D:\soft\opencv3\build\include
OPENCV_LIBRARY_DIRS=D:\soft\opencv3\build\x64\vc15\lib
ZLIB_INCLUDE_DIRS="D:\soft\opencv3\sources\3rdparty\zlib"

INCLUDEPATH+=D:\soft\eigen-eigen-323c052e1731
INCLUDEPATH+=$$(DLIB_ROOT)\include
INCLUDEPATH+=$$OPENCV_INCLUDE_DIRS
INCLUDEPATH+=$$ZLIB_INCLUDE_DIRS
LIBS+=-L$$(DLIB_ROOT)\lib -ldlib19.16.99_release_64bit_msvc1900
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_world344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_ximgproc344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_calib3d344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_features2d344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_flann344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_highgui344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_videoio344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_imgcodecs344
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_core344

SOURCES += \
        dialog.cpp \
        main.cpp \
        mainwindow.cpp \
        modelfitting.cpp \
        settings.cpp \
        src/Dlib.cpp \
        src/cnpy.cpp \
        test.cpp \
        thread/cameraworkthread.cpp \
        thread/threadsynglobalobj.cpp \
        thread/udpworkthread.cpp \
        thread/workingthread.cpp

HEADERS += \
        dialog.h \
        drawLandmarks.hpp \
        mainwindow.h \
        modelfitting.h \
        obstaclemethodsolver.h \
        settings.h \
        src/Dlib.h \
        src/EigenUtil.h \
        src/MMSolver.h \
        src/NumpyUtil.h \
        src/Poisson.h \
        src/cnpy.h \
        src/stdafx.h \
        test.h \
        thread/cameraworkthread.h \
        thread/threadsafequeue.h \
        thread/threadsynglobalobj.h \
        thread/udpworkthread.h \
        thread/workingthread.h \
        ui_dialog.h \
        util/eigenfunctions.h

FORMS += \
        dialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    icon.qrc

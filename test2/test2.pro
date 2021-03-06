#-------------------------------------------------
#
# Project created by QtCreator 2015-01-15T16:43:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fichiercontrol.cpp

HEADERS  += mainwindow.h \
    fichiercontrol.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:/opencv/build/include
LIBPATH += C:/opencv/build/x86/vc12/lib\


CONFIG(release,debug|release){
CONFIG += embed_manifest_exe
QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
LIBS += C:/opencv/build/x86/vc12/lib/opencv_calib3d249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_contrib249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_features2d249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_flann249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_highgui249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_imgproc249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_objdetect249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_video249.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_core249.lib
}

CONFIG(debug,debug|release){
LIBS += C:/opencv/build/x86/vc12/lib/opencv_calib3d249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_contrib249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_features2d249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_flann249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_highgui249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_imgproc249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_objdetect249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_video249d.lib
LIBS += C:/opencv/build/x86/vc12/lib/opencv_core249d.lib
}

RESOURCES += \
    icon.qrc

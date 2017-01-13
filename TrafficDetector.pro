#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T10:38:03
#
#-------------------------------------------------

QT       += core gui widgets

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

TARGET = TrafficDetector
TEMPLATE = app


SOURCES += main.cpp\
    models/projectmodel.cpp \
    processing/BackgroundDetector.cpp \
    processing/MotionDetector.cpp \
    processing/qtipl.cpp \
    views/mainwindow.cpp \
    processing/player.cpp \
    processing/controller.cpp


FORMS    += views/mainwindow.ui

INCLUDEPATH += /usr/include/opencv

LIBS +=-L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

HEADERS += \
    models/projectmodel.h \
    processing/BackgroundDetector.h \
    processing/MotionDetector.h \
    processing/player.h \
    processing/qtipl.h \
    views/mainwindow.h \
    processing/controller.h

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

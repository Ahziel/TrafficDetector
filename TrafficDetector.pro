#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T10:38:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficDetector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BackgroundDetector.cpp \
    MotionDetector.cpp \
    qtipl.cpp

HEADERS  += mainwindow.h \
    BackgroundDetector.h \
    MotionDetector.h \
    qtipl.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/opencv

LIBS +=-L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T10:38:03
#
#-------------------------------------------------

QT       += core gui widgets multimedia

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficDetector
TEMPLATE = app


SOURCES += main.cpp\
    models/projectmodel.cpp \
    processing/BackgroundDetector.cpp \
    processing/MotionDetector.cpp \
    processing/qtipl.cpp \
    views/mainwindow.cpp

HEADERS  += models/projectmodel.h \
    processing/BackgroundDetector.h \
    processing/MotionDetector.h \
    processing/qtipl.h \
    views/mainwindow.h

FORMS    += views/mainwindow.ui

INCLUDEPATH += /usr/include/opencv

LIBS +=-L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T10:38:03
#
#-------------------------------------------------

QT       += core gui widgets webkit webkitwidgets

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
    controllers/controller.cpp \
    processing/trafficdetector.cpp \
    views/help.cpp


FORMS    += views/mainwindow.ui \
    views/help.ui

INCLUDEPATH += /usr/include/opencv

LIBS +=-L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

HEADERS += \
    models/projectmodel.h \
    processing/BackgroundDetector.h \
    processing/MotionDetector.h \
    processing/player.h \
    processing/qtipl.h \
    views/mainwindow.h \
    controllers/controller.h \
    processing/trafficdetector.h \
    views/help.h

RESOURCES += \
    icons.qrc



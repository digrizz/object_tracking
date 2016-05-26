#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T18:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = object_tracking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logger.cpp \
    detector.cpp \
    tracker.cpp

HEADERS  += mainwindow.h \
    logger.h \
    detector.h \
    tracker.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\OpenCV\\opencv\\build\include

LIBS += -LC:\\OpenCV\\opencv-debug\\lib \
-lopencv_core310.dll \
-lopencv_highgui310.dll \
-lopencv_imgproc310.dll \
-lopencv_imgcodecs310.dll \
-lopencv_videoio310.dll \
-lopencv_video310.dll \
-lopencv_videostab310.dll \
-lopencv_calib3d310.dll \
-lopencv_ts310 \
-lopencv_shape310.dll \
-lopencv_photo310.dll \
-lopencv_objdetect310.dll \
-lopencv_ml310.dll \
-lopencv_flann310.dll \
-lopencv_features2d310.dll

# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Cyber

QT = core gui widgets

HEADERS = \
   $$PWD/include/datatype.h \
   $$PWD/include/ImageProcessor.h \
   $$PWD/include/mainwindow.h \
   $$PWD/include/resourcemanager.h \
   $$PWD/include/ui_mainwindow.h \
   $$PWD/include/yoloparser.h \
   $$PWD/include/yolov5_lib.h \
   $$PWD/plugins/preprocess.h \
   $$PWD/YOLO/include/calibrator.h \
   $$PWD/YOLO/include/config.h \
   $$PWD/YOLO/include/cuda_utils.h \
   $$PWD/YOLO/include/datetype.h \
   $$PWD/YOLO/include/logging.h \
   $$PWD/YOLO/include/macros.h \
   $$PWD/YOLO/include/model.h \
   $$PWD/YOLO/include/postprocess.hpp \
   $$PWD/YOLO/include/types.h \
   $$PWD/YOLO/include/utils.h \
   $$PWD/YOLO/include/yololayer.h

SOURCES = \
   $$PWD/src/main.cpp \
   $$PWD/src/mainwindow.cpp \
   $$PWD/src/resourcemanager.cpp \
   $$PWD/src/yoloparser.cpp \
   $$PWD/src/yolov5_lib.cpp \
   $$PWD/ui/mainwindow.ui \
   $$PWD/YOLO/src/calibrator.cpp \
   $$PWD/YOLO/src/model.cpp

INCLUDEPATH = \
    $$PWD/include \
    $$PWD/plugins \
    $$PWD/YOLO/include

#DEFINES = 


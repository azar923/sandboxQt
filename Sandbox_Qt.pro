#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T13:47:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = Sandbox_Qt
TEMPLATE = app


SOURCES += main.cpp\
        sandbox.cpp \
    sandboxwidget.cpp \
    camera.cpp \
    filestream.cpp \
    inputstream.cpp \
    lighting.cpp \
    math_3d.cpp \
    pipeline.cpp \
    scene.cpp \
    shadertechnique.cpp \
    skybox.cpp \
    terrain.cpp \
    texture.cpp \
    texture2D.cpp \
    texture3D.cpp \
    settings.cpp \
    sensorcalibration.cpp \
    sensorsettings.cpp

HEADERS  += sandbox.h \
    sandboxwidget.h \
    camera.h \
    datastream.h \
    filestream.h \
    inputstream.h \
    lighting.h \
    math_3d.h \
    pipeline.h \
    scene.h \
    shadertechnique.h \
    skybox.h \
    terrain.h \
    texture.h \
    texture2D.h \
    texture3D.h \
    settings.h \
    sensorcalibration.h \
    sensorsettings.h

FORMS    += sandbox.ui \
    settings.ui \
    sensorcalibration.ui \
    sensorsettings.ui

LIBS += -lGL -lGLEW -lglut

INCLUDEPATH += /home/maxim/flex/include/

LIBS +=-L/home/maxim/OpenNI2/Bin/x64-Release/ -lOpenNI2
LIBS += -L/usr/local/lib/ -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_photo -lopencv_highgui -lopencv_cudaimgproc -lopencv_cudafilters

LIBS += -L/home/maxim/flex/lib/linux64 -l:flexRelease_x64.a -l:flexReleaseExt_x64.a -ldl
LIBS += -L/usr/local/cuda/lib64/ -lcudart

RESOURCES += \
    shaders.qrc


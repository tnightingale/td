######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 26 20:18:46 2011
######################################################################

include(./3rdparty/inc/tiled/tiled.pri)
include(./3rdparty/inc/libtiled/libtiled.pri)

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = ./bin
QT += network
OBJECTS_DIR = ./obj

macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
    LIBS += -L$$OUT_PWD/3rdparty/Frameworks
    system(mkdir ./bin/td.app/Contents/Frameworks)
    system(cp ./3rdparty/Frameworks/libtiled.dylib ./bin/td.app/Contents/Frameworks/libtiled.1.dylib)
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
    LIBS += -L$$OUT_PWD/3rdparty/lib/
}

AUDIO_HDRS +=   src/audio/manager.h \
                src/audio/openal_helper.h

AUDIO_SRCS +=   src/audio/manager.cpp \
                src/audio/openal_helper.cpp
                
NETWORK_HDRS += src/network/netclient.h \
                src/network/stream.h

NETWORK_SRCS += src/network/stream.cpp \
                src/network/netclient.cpp
                
ENGINE_HDRS +=  src/engine/CDriver.h \
                src/engine/Effect.h \
                src/engine/GameObject.h \
                src/engine/InputComponent.h \
                src/engine/NPC.h \
                src/engine/PlayerInputComponent.h \
                src/engine/PhysicsComponent.h \
                src/engine/Player.h \
                src/engine/PlayerPhysicsComponent.h \
                src/engine/Projectile.h \
                src/engine/SDriver.h \
                src/engine/Tile.h \
                src/engine/Unit.h \
                src/engine/PlayerGraphicsComponent.h \
                src/engine/GraphicsComponent.h

ENGINE_SRCS +=  src/engine/CDriver.cpp \
                src/engine/Effect.cpp \
                src/engine/GameObject.cpp \
                src/engine/InputComponent.cpp \
                src/engine/NPC.cpp \
                src/engine/PlayerInputComponent.cpp \
                src/engine/PhysicsComponent.cpp \
                src/engine/Player.cpp \
                src/engine/PlayerPhysicsComponent.cpp \
                src/engine/Projectile.cpp \
                src/engine/SDriver.cpp \
                src/engine/Unit.cpp \
                src/engine/PlayerGraphicsComponent.cpp

GRAPHICS_SRCS +=src/graphics/mapdisplayer.cpp

GRAPHICS_HDRS += src/graphics/mapdisplayer.h



HEADERS += src/MainWindow.h $$AUDIO_HDRS $$NETWORK_HDRS $$ENGINE_HDRS $$GRAPHICS_HDRS
SOURCES += src/main.cpp src/MainWindow.cpp $$AUDIO_SRCS $$NETWORK_SRCS $$ENGINE_SRCS $$GRAPHICS_SRCS

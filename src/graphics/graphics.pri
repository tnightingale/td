include(../3rdparty/libtiled/libtiled.pri)

LIBS += ../lib/libtiled.a -lz

GRAPHICS_SRCS +=    ./graphics/MapDisplayer.cpp \
                    ./graphics/ContextMenuGraphicsComponent.cpp \
                    ./graphics/GraphicsComponent.cpp \
                    ./graphics/PlayerGraphicsComponent.cpp \
                    ./graphics/ProjectileGraphicsComponent.cpp \
                    ./graphics/TowerGraphicsComponent.cpp


GRAPHICS_HDRS +=    ./graphics/MapDisplayer.h \
                    ./graphics/ContextMenuGraphicsComponent.h \
                    ./graphics/GraphicsComponent.h \
                    ./graphics/PlayerGraphicsComponent.h \
                    ./graphics/PixmapFiles.h \
                    ./graphics/DrawParams.h \
                    ./graphics/ProjectileGraphicsComponent.h \
                    ./graphics/TowerGraphicsComponent.h
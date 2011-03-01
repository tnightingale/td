AUDIO_HDRS +=   ./audio/manager.h \
                ./audio/openal_helper.h

AUDIO_SRCS +=   ./audio/manager.cpp \
                ./audio/openal_helper.cpp


macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
}
unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
}
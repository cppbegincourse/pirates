TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Pirates/main.cpp \
    Pirates/World.cpp \
    Pirates/Pirate.cpp \
    Pirates/iplatorm.cpp \
    Pirates/cursesplatform.cpp \
    Pirates/logstream.cpp

HEADERS += \
    Pirates/Treasure.h \
    Pirates/Entity.h \
    Pirates/Pirate.h \
    Pirates/World.h \
    Pirates/stdafx.h \
    Pirates/iplatform.h \
    Pirates/cursesplatform.h \
    Pirates/Input.h \
    Pirates/logstream.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += ncurses

unix: PKGCONFIG += sfml-graphics

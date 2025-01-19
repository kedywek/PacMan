######################################################################
# Automatically generated by qmake (3.1) Sun Jan 19 21:26:14 2025
######################################################################

TEMPLATE = app
TARGET = PacMan
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += src/Character.h \
           src/Collectible.h \
           src/GameWindow.h \
           src/Ghost.h \
           src/Map.h \
           src/Pac.h \
           src/Point.h \
           src/Types.h
SOURCES += src/Character.cpp \
           src/Collectible.cpp \
           src/GameWindow.cpp \
           src/Ghost.cpp \
           src/Map.cpp \
           src/Pac.cpp \
           src/Point.cpp
RESOURCES += resources.qrc
QT += widgets

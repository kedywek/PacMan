######################################################################
# Automatically generated by qmake (3.1) Sat Feb 8 02:12:06 2025
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
HEADERS += src/AStar.h \
           src/Blinky.h \
           src/Character.h \
           src/Clyde.h \
           src/Collectible.h \
           src/Direction.h \
           src/GameState.h \
           src/GameWindow.h \
           src/Ghost.h \
           src/Inky.h \
           src/Interface.h \
           src/Map.h \
           src/MapState.h \
           src/Pac.h \
           src/Pinky.h \
           src/Point.h \
           src/Scoreboard.h \
           src/ScoreboardTable.h \
           src/Star.h \
           src/Types.h
SOURCES += src/AStar.cpp \
           src/Blinky.cpp \
           src/Character.cpp \
           src/Clyde.cpp \
           src/Collectible.cpp \
           src/GameWindow.cpp \
           src/Ghost.cpp \
           src/Inky.cpp \
           src/Interface.cpp \
           src/Map.cpp \
           src/Pac.cpp \
           src/Pinky.cpp \
           src/Point.cpp \
           src/Scoreboard.cpp \
           src/ScoreboardTable.cpp \
           src/Star.cpp
RESOURCES += resources.qrc
QT += widgets

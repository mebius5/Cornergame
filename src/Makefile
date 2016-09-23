# <GAME NAME> Makefile

SRCFILES = \
	gameManager.cpp \
	drawer.cpp \
	enemy.cpp \
	hero.cpp \
	inputHandler.cpp \
	location.cpp \
	texture.cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -O2
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_mixer SDL2_image SDL2_ttf`
LDFLAGS += `pkg-config --libs sdl2 SDL2_mixer SDL2_image SDL2_ttf`

TARGET = gameManager

all: $(TARGET)

$(TARGET): $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(TARGET)

#For compiling on mac only
mac:
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2

# <GAME NAME> Makefile

SRCFILES = \
	aiComponent.cpp \
	aiHandler.cpp \
	artComponent.cpp \
	collisionHandler.cpp \
	command.cpp \
	drawingHandler.cpp \
	entity.cpp \
	entityHandler.cpp \
	gameManager.cpp \
	inputComponent.cpp \
	inputHandler.cpp \
	locationHandler.cpp \
	locationComponent.cpp \
	physicsComponent.cpp \
	soundHandler.cpp \
	statsComponent.cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -O2 -g
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_mixer SDL2_image SDL2_ttf`
LDFLAGS += `pkg-config --libs sdl2 SDL2_mixer SDL2_image SDL2_ttf`
MACFLAGS = -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2_ttf -lSDL2_mixer \
	-lSDL2_image -lSDL2
INCLUDE = -Ih

TARGET = gameManager

all: $(TARGET)

$(TARGET): $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS)

clean:
	$(RM) $(TARGET) *.o

#For compiling on mac only
mac:
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) $(INCLUDE) $(MACFLAGS)

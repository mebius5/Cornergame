# <GAME NAME> Makefile

SRCFILES = \
	aiComponent.cpp \
	aiHandler.cpp \
	animationComponent.cpp \
	collisionComponent.cpp \
	collisionHandler.cpp \
	command.cpp \
	controlHandler.cpp \
	drawingHandler.cpp \
	entity.cpp \
	entityBuilder.cpp \
	gameManager.cpp \
	heroInputComponent.cpp \
    highscoreState.cpp \
	inputComponent.cpp \
	inputHandler.cpp \
	menuState.cpp \
	menuSateInputComponent.cpp \
	playState.cpp \
	physicsComponent.cpp \
	soundHandler.cpp \
	startState.cpp \
	startStateInputComponent.cpp \
	state.cpp \
	staticArtComponent.cpp \
	statsComponent.cpp \
	textFadeInComponent.cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -O2
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_mixer SDL2_image SDL2_ttf`
LDFLAGS += `pkg-config --libs sdl2 SDL2_mixer SDL2_image SDL2_ttf`
MACFLAGS = -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2_ttf -lSDL2_mixer \
	-lSDL2_image -lSDL2
INCLUDE = -Ih

TARGET = gameManager

all: $(TARGET)

$(TARGET): $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS)

debug: $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -g $(INCLUDE) $(LDFLAGS)

clean:
	$(RM) $(TARGET) *.o
	$(RM) -rf *.dSYM

#For compiling on mac only
mac:
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) $(INCLUDE) $(MACFLAGS)

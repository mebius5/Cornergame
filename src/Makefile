# <GAME NAME> Makefile

SRCFILES = \
	aiHandler.cpp \
	animationComponent.cpp \
	collisionHandler.cpp \
	command.cpp \
	component.cpp \
	controlHandler.cpp \
	drawingHandler.cpp \
	enemyAiComponent.cpp \
	enemyCollisionComponent.cpp \
	entity.cpp \
	entityBuilder.cpp \
	entityManager.cpp \
	gameManager.cpp \
    healthComponent.cpp \
	healthBarArtComponent.cpp \
	heroCollisionComponent.cpp \
	heroInputComponent.cpp \
    highscoreState.cpp \
	inputHandler.cpp \
	menuOptionInputComponent.cpp \
	menuState.cpp \
	playState.cpp \
	resultsState.cpp \
    scoreComponent.cpp \
    scoreHandler.cpp \
    scoreTextArtComponent.cpp \
	soundHandler.cpp \
	startState.cpp \
	state.cpp \
	staticArtComponent.cpp \
	terrainCollisionComponent.cpp \
	textFadeInComponent.cpp \
	victoryZoneCollisionComponent.cpp

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_mixer SDL2_image SDL2_ttf`
LDFLAGS += `pkg-config --libs sdl2 SDL2_mixer SDL2_image SDL2_ttf`
MACFLAGS = -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2_ttf -lSDL2_mixer \
	-lSDL2_image -lSDL2
INCLUDE = -Ih

TARGET = gameManager

all: $(TARGET)

$(TARGET): $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -O2 $(INCLUDE) $(LDFLAGS)

debug: $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -g -O0 $(INCLUDE) $(LDFLAGS)

valgrind: $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -g -O2 $(INCLUDE) $(LDFLAGS)

clean:
	$(RM) $(TARGET) *.o
	$(RM) -rf *.dSYM

#For compiling on mac only
mac:
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) $(INCLUDE) $(MACFLAGS)

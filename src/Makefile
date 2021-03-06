# <GAME NAME> Makefile

SRCFILES = \
	aiHandler.cpp \
	ammoBarArtComponent.cpp \
	ammoComponent.cpp \
	animationComponent.cpp \
	backgroundArtComponent.cpp \
	bombCollisionComponent.cpp \
	bombIndicatorArtComponent.cpp \
	bounceAnimationComponent.cpp \
	bounceCollisionComponent.cpp \
	camera.cpp \
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
	fadingTerrainArtComponent.cpp \
	fadingTerrainColComponent.cpp \
	gameManager.cpp \
	healthComponent.cpp \
	healthBarArtComponent.cpp \
	heroCollisionComponent.cpp \
	heroInputComponent.cpp \
	highscoreState.cpp \
	inputHandler.cpp \
	level.cpp \
	levelSelectInputComponent.cpp \
	levelSelectState.cpp \
	levelTransitState.cpp \
	menuOptionInputComponent.cpp \
	menuState.cpp \
    movementComponent.cpp \
	objectAnimationComponent.cpp \
	oneTimeAnimationComponent.cpp \
    particleAnimationComponent.cpp\
    particleComponent.cpp \
    particleHandler.cpp \
	physicsComponent.cpp \
	physicsHandler.cpp \
	playState.cpp \
	powerUpArtComponent.cpp \
	powerUpCollisionComponent.cpp \
	powerUpComponent.cpp \
	powerUpHandler.cpp \
	projectileArtComponent.cpp \
	projectileCollisionComponent.cpp \
	respawnEntity.cpp \
	resultsState.cpp \
	scoreComponent.cpp \
	scoreHandler.cpp \
	soundHandler.cpp \
	startState.cpp \
	state.cpp \
	staticArtComponent.cpp \
	terrainCollisionComponent.cpp \
	textFadeInComponent.cpp \
	timeHandler.cpp \
	tutorialState.cpp \
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
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -g -O2 $(INCLUDE) $(LDFLAGS)

valgrind: $(SRCFILES)
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -g -O2 $(INCLUDE) $(LDFLAGS)

clean:
	$(RM) $(TARGET) *.o
	$(RM) -rf *.dSYM
	$(RM) *~

#For compiling on mac only
mac:
	$(CXX) -o $(TARGET) $(SRCFILES) $(CXXFLAGS) -g $(INCLUDE) $(MACFLAGS)

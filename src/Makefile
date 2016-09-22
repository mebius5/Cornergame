# <GAME NAME> Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -O2
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_mixer SDL2_image SDL2_ttf`
LDFLAGS += `pkg-config --libs sdl2 SDL2_mixer SDL2_image SDL2_ttf`

TARGET = gameManager

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) -o $(TARGET) $(TARGET).cpp $(CXXFLAGS) $(LDFLAGS)
clean:
	$(RM) $(TARGET)

# Assignment 1 Makefile
# Andrew Zhu azhu8@jhu.edu

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -O2
INCLUDES = -I/usr/local/include/SDL2
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image

TARGET = demo

all: $(TARGET)

$(TARGET): $(TARGET).C
	$(CXX) -o $(TARGET) $(TARGET).C $(CXXFLAGS) $(INCLUDES) $(LIBS)
clean:
	$(RM) $(TARGET)

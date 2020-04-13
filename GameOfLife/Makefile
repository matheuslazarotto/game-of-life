INCLUDE_DIR=./include
CXXFLAGS=-Wall -I$(INCLUDE_DIR)
VPATH=./src

TARGETS=game

DEPENDENCIES=main.cpp canvas.cpp game.cpp system.cpp

build: $(TARGETS)

$(TARGETS): $(DEPENDENCIES) -lSDL2
	$(CXX) $(CXXFLAGS) -o game $^

.PHONY: clean
clean:
	-rm -f $(TARGETS)

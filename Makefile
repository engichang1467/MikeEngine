cppsrc = $(wildcard src/graphics/window.cpp)
hsrc = $(wildcard src/graphics/window.h)
osrc = $(cppsrc:window.cpp=window.o)

LDFLAGS = -lGL -lglut -lGLEW -lglfw

all: engine srcPrep

# To compile the window programs fom the graphic folder
srcPrep: $(cppsrc) $(hsrc)
	g++ -Wall -c $(cppsrc) $(LDFLAGS)

engine: mikeyEngine.o $(osrc)
	g++ -Wall -o engine mikeyEngine.o $(osrc) $(LDFLAGS)

mikeyEngine.o: mikeyEngine.cpp $(hsrc)
	g++ -Wall -c mikeyEngine.cpp $(LDFLAGS)

clean:
	rm -f engine *.o $(osrc)
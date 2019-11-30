cppsrc = $(wildcard src/graphics/window.cpp)
hsrc = $(wildcard src/graphics/window.h)
osrc = $(cppsrc:window.cpp=window.o)

LDFLAGS = -lGL -lglut -lGLEW -lglfw

all: engine srcPrep

# To compile the window programs fom the graphic folder
srcPrep: $(cppsrc) $(hsrc)
	g++ -Wall -c $(cppsrc) $(LDFLAGS)

engine: mikeEngine.o $(osrc)
	g++ -Wall -o engine mikeEngine.o $(osrc) $(LDFLAGS)

mikeEngine.o: mikeEngine.cpp $(hsrc)
	g++ -Wall -c mikeEngine.cpp $(LDFLAGS)

clean:
	rm -f engine *.o $(osrc)
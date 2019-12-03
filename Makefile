cppsrc = $(wildcard src/graphics/window.cpp)
hsrc = $(wildcard src/graphics/window.h)
osrc = $(cppsrc:window.cpp=window.o)

OS := $(shell uname)

ifeq ($(OS), Darwin)
	# Check if its in MAC OS
	LDFLAGS = -framework OpenGl -lglfw -lGLEW
else
	# Check if its Linux
	LDFLAGS = -lGL -lglut -lGLEW -lglfw 
endif


all: engine srcPrep

# To compile the window programs fom the graphic folder
srcPrep: $(cppsrc) $(hsrc)
	g++ -Wall -c $(cppsrc) $(LDFLAGS)

engine: torpoEngine.o $(osrc)
	g++ -Wall -o engine torpoEngine.o $(osrc) $(LDFLAGS)

torpoEngine.o: torpoEngine.cpp $(hsrc)
	g++ -Wall -c torpoEngine.cpp $(LDFLAGS)

clean:
	rm -f engine *.o $(osrc)
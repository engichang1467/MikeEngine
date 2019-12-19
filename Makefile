CppGraphicsSrc = $(wildcard src/graphics/window.cpp)
HGraphicsSrc = $(wildcard src/graphics/window.h)
OGraphicsSrc = $(CppGraphicsSrc:window.cpp=window.o)

CppVec2MathsSrc = $(wildcard src/maths/vec2.cpp)
CppVec3MathsSrc = $(wildcard src/maths/vec3.cpp)
CppVec4MathsSrc = $(wildcard src/maths/vec4.cpp)
CppMathsSrc = $(CppVec2MathsSrc) $(CppVec3MathsSrc) $(CppVec4MathsSrc)


HVec2MathsSrc = $(wildcard src/maths/vec2.h)
HVec3MathsSrc = $(wildcard src/maths/vec3.h)
HVec4MathsSrc = $(wildcard src/maths/vec4.h)
HMathsSrc = $(HVec2MathsSrc) $(HVec3MathsSrc) $(HVec4MathsSrc)

OVec2MathsSrc = $(CppMathsSrc:vec2.cpp=vec2.o)
OVec3MathsSrc = $(CppMathsSrc:vec3.cpp=vec3.o)
OVec4MathsSrc = $(CppMathsSrc:vec4.cpp=vec4.o)
OMathsSrc = $(OVec2MathSrc) $(OVec3MathSrc) $(OVec4MathSrc)

OS := $(shell uname)

ifeq ($(OS), Darwin)
	# Check if its in MAC OS
	LDFLAGS = -framework OpenGl -lglfw -lGLEW
else
	# Check if its Linux
	LDFLAGS = -lGL -lglut -lGLEW -lglfw 
endif

#engine
all:  srcPrep engine

# To compile the window programs fom the graphic folder
srcPrep: $(CppGraphicsSrc) $(HGraphicsSrc) $(CppMathsSrc) $(HMathsSrc)
	g++ -Wall -c $(CppGraphicsSrc) $(CppMathsSrc) $(LDFLAGS)

torpoEngine.o: torpoEngine.cpp $(HGraphicsSrc) $(HMathsSrc)
	g++ -Wall -c torpoEngine.cpp $(LDFLAGS)

engine: *.o # $(OGraphicsSrc) $(OVec2MathSrc) $(OVec3MathSrc) $(OVec4MathSrc)
	g++ -Wall -o engine *.o $(LDFLAGS)

clean:
	rm -f engine *.o $(OGraphicsSrc) $(OMathsSrc)
CFLAGS=-Wall --pedantic -I./include
LDFLAGS=-lc -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm
RELEASE=-O2
DEBUG=-g
SOURCE=$(wildcard *.cpp)
OBJECTS:= $(patsubst %.cpp,%.o,$(SOURCE))

all : $(OBJECTS)
	g++ $(LDFLAGS) $(OBJECTS) -o sogo

release : override CFLAGS+=-O2
release : clean all;

debug : override CFLAGS+=-g -DDEBUG
debug : clean all;

asm : override CFLAGS+=-S
asm : clean all;

clean :
	rm -f sogo $(OBJECTS)

%.o : %.cpp
	g++ -c $(CFLAGS) $< -o $@


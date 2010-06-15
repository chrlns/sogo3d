CFLAGS=-Wall --pedantic -pipe -I./include
LDFLAGS=-lc -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm -lpthread
# We use -O2 as -O3 is NOT safe with gcc 4.x
RELEASE=-O2 -march=native
DEBUG=-g -DDEBUG
SOURCE=$(wildcard *.cpp)
OBJECTS:= $(patsubst %.cpp,%.o,$(SOURCE))

all : $(OBJECTS)
	g++ $(LDFLAGS) $(OBJECTS) -o sogo

release : override CFLAGS+=$(RELEASE)
release : clean all;

debug : override CFLAGS+=$(DEBUG) 
debug : clean all;

asm : override CFLAGS+=-S
asm : clean all;

clean :
	rm -f sogo $(OBJECTS)

%.o : %.cpp
	g++ -c $(CFLAGS) $< -o $@


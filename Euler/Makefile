CC = gcc
CPP = g++
LD = gcc
RM = /bin/rm -f
CFLAGS = `sdl-config --cflags` -Wall -O2
LDFLAGS = `sdl-config --libs` -I/usr/X11R6/include -L/usr/X11R6/lib -lGL -lGLU -lm -lstdc++

SRC = Kerr.cc Camera.cc Euler.cc Sphere.cc Particle.cc Vector.cc
OBJ = $(SRC:.cc=.o)

PROG = kerr 

all: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
	$(CPP) $(CFLAGS) -c $(SRC)

clean:
	$(RM) $(OBJ) $(PROG)

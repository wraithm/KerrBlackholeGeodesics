CC = gcc
CPP = g++
LD = g++
RM = /bin/rm -f
CFLAGS = `sdl-config --cflags` -Wall -O2
LDFLAGS = `sdl-config --libs` -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lGL -lGLU

SRC = kerr.cc camera.cc odesolver.cc sphere.cc
OBJ = $(SRC:.cc=.o)

PROG = kerr 

all: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)
	$(RM) $(OBJ)

$(OBJ): $(SRC)
	$(CPP) $(CFLAGS) -c $(SRC)

clean:
	$(RM) $(OBJ) $(PROG)

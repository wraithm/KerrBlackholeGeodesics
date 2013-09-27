CC = gcc
CPP = g++
LD = gcc
RM = /bin/rm -f
CFLAGS = -I/Library/Frameworks/SDL.framework/Headers/ -I/System/Library/Frameworks/OpenGL.framework/Headers -framework SDL -framework Cocoa -framework OpenGL -Wall -O3 SDLmain.m
#CFLAGS = -I/opt/local/include/ -I/System/Library/Frameworks/OpenGL.framework/Headers -I/System/Library/Frameworks/GLUT.framework -framework SDL -framework Cocoa -framework OpenGL -Wall -O3 SDLmain.m
#LDFLAGS = -I/Library/Frameworks/SDL.framework/Headers -I/System/Library/Frameworks/OpenGL.framework/Headers -lGL -lGLU -lSDL -lpthread

SRC = Kerr.cc Camera.cc Odesolver.cc Sphere.cc
#OBJ = $(SRC:.cc=.o)

PROG = kerr 

all: $(PROG)

$(PROG): 
	$(CPP) $(CFLAGS) $(SRC) -o $(PROG)

#$(PROG): $(OBJ)
#	$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)
#	$(RM) $(OBJ)

#$(OBJ): $(SRC)
#	$(CPP) $(CFLAGS) -c $(SRC)

clean:
	$(RM) $(PROG)

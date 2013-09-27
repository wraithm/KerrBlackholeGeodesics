Author: Matthew Wraith

INTRODUCTION
============
This is a simple Euler integration of the equations of motion for a Kerr
blackhole from General Relativity. The Kerr blackhole is a solution to
Einstein's equations which are spherically symmetric, but the blackhole rotates
with some angular momentum. I took the space-time metric and found the equations
of motion for a test particle using the Euler-Lagrange equations and also the
equivalent geodesic equations. I did some of the math by hand, but also some in
Mathematica, because (as you will see) the math was far too cumbersome to do by
hand. I display the solution in OpenGL and SDL. I created a first-person
environment to view the particles going around the blackhole. WASD-keys to move,
and E and C to move up and down. The mouse looks around. The program takes over
the whole screen. The camera starts pretty close to the blackhole. Hold S to
back up and view the whole scene.

Note: When the particle falls into the blackhole, it goes off to infinity.
That's really what the equations do. So, when the particle falls into the
blackhole, there will be a line that extends off to infinity. The equations
become singular on the surface of the blackhole. Everything blows up to
infinity.


IMPLEMENTATION NOTES
--------------------
I used a lot of arrays in this program. Usually, I would use vectors, lists,
or whatever would be appropriate. However, OpenGL is implemented in C, and uses
standard C arrays for everything. So, that's why there are arrays for everything
in this implementation.


COMPILATION INSTRUCTIONS
------------------------
I compiled this on a 64-bit Linux system. OpenGL and SDL are both required for
this to run correctly.

SDL can be downloaded from - http://www.libsdl.org/
OpenGL can be obtained from - http://www.opengl.org/wiki/Getting_Started  

I've included a Makefile for GNU C++.

To compile and run:
    make && ./kerr

If make doesn't work, this should:

```
g++ `sdl-config --cflags` -Wall -O2 -c Kerr.cc Camera.cc Euler.cc Sphere.cc Particle.cc Vector.cc
gcc `sdl-config --libs` -I/usr/X11R6/include -L/usr/X11R6/lib -lGL -lGLU -lm -lstdc++ Kerr.o Camera.o Euler.o Sphere.o Particle.o Vector.o -o kerr
```


USAGE INSTRUCTIONS
------------------
There are several elements which can be configured for this program.

First of all, it's likely that the screen resolution may not work. Camera.h
contains two defines WINSIZEX and WINSIZEY. I have them set to 1600 x 900 at the
moment (my computer screen resolution), but if your computer does not have this
resolution, it won't work. Also, STEP in Euler.h defines the speed of the
simulation. I could have this value based upon the wall time, so that the
simulation is not dependent upon the clock speed of the computer. I just wanted
to have serious control over the simulation when I wrote this. MASS and ANGM are
the mass and angular momentum of the blackhole, which are interesting to play
with.

I've set up two particles to be displayed. You can play with the initial
conditions of these particles. The instructions for setting the initial
conditions for the particles is included in Kerr.cc.

The mouse is used to look around.

```
The keyboard commands are:
Q or ESC - Quit
W - Move forward
A - Strafe left
D - Strafe right
S - Move backward
E - Move upward
C - Move downward
```

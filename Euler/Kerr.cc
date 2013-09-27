// Author: Matthew Wraith

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>

#include "Camera.h"
#include "Sphere.h"
#include "Particle.h"

using namespace std;

const double pi = 3.141592654;

const float grey[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const float yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const float blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
const float red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
const float green[] = { 0.0f, 1.0f, 0.0f, 1.0f };

const float lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

Camera camera;
Sphere blackhole(2.0f*MASS, 30); // A blackhole's radius is twice its mass

Particle p1(
    0.0, 18.0, pi/2, 0.0,  // Initial positions
    23.0, 0.0, 0.1, 0.1,  // Initial velocities
    0.5, 20 // Radius and number of subdivisions of the sphere
);
Particle p2(
    0.0, 20.0, pi/2, 0.0,  // Initial positions
    25.0, 0.0, -0.1, -0.3, // Initial velocities
    0.5, 20 // Radius and number of subdivisions of the sphere
);

SDL_Event event;

// The meaning of the initial coordinates
// t is time,
// r is the radius
// th is the polar angle
// ph is the azimuthal angle
// t' is the rate of change of time (general relativity)
// r' is the radial velocity
// th' is the polar velocity
// ph' is the azimuthal velocity.
//
// The blackhole rotates in the direction of the azimuthal angle. Negative
// values of ph' will give you orbits that rotate against the blackhole. This
// produces very interesting results.
//
// Some interesting intial conditions given in Boyer-Lindquist Coords
//{t,   r,    th,   ph,  t',   r', th',   ph'};
//{0.0, 20.0, pi/2, 0.0, 20.0, 0.0, 0.28, 0.1}; //VERY large
//{0.0, 19.0, pi/2, 0.0, 10.0, 0.0, 0.08, 0.08}; //This works, I think.
//{0.0, 16.0, pi/2, 0.0, 30.0, 0.1, 0.5, 0.3}; //large sweeps
//{0.0, 50.0, pi/2, 0.0, 9.0, 0.0, 0.02, 0.02}; //large and crazy.
//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.1, 0.1}; //strange orbit that goes around the top and bottom
//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.2, 0.2}; //very stable but tight
//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.08, 0.08}; //very stable but tight
//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.06, 0.06};

//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.1, -0.1}; //counter rotating orbit... scary...
//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, -0.1, -0.1}; //counter rotating orbit... scary too...
//{0.0, 18.0, pi/2, 0.0, 23.0, 0.0, -0.1, -0.2}; //counter rotating orbit... scary too...
//{0.0, 50.0, pi/2, 0.0, 9.0, 0.0, 0.02, -0.02}; //counter rotating orbit... scary too...

// Make a grid, 100 x 100, with 5 units of separation
void drawGrid() {
    glBegin(GL_LINES);
    for(float i = -500; i <= 500; i += 5) {
        glColor3ub(150, 190, 150);
        glVertex3f(-500, 0, i);
        glVertex3f(500, 0, i);
        glVertex3f(i, 0,-500);
        glVertex3f(i, 0, 500);
    }
    glEnd();
}

// Draw the scene to the screen.
// This draws the camera, the black hole, and any particles that I want.
void drawScene(SDL_Surface *screen) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.drawCamera();
    //drawGrid(); // A grid if you'd like to see where you are.
    
    // Make a lit yellow sphere
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, yellow);
        glColor4fv(yellow);
        blackhole.drawSphere(); // Draw the blackhole
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glPopMatrix();

    // Make the blue planet
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glColor4fv(blue);
    p1.update();
    p1.drawThis();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
    glColor4fv(red);
    p2.update();
    p2.drawThis();
    
    glFlush();
    SDL_GL_SwapBuffers();           
}

// Initialize everything.
void init() {
    float specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float shininess[] = { 80.0f };
    float whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_EnableKeyRepeat(10, 30);

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Only one light

    // Smooth shading
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    glShadeModel(GL_SMOOTH);

    // Material properties
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    // Light properties
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ambient);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    SDL_ShowCursor(0); // Don't show the cursor
    glPointSize(3.0f);
        
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80.0f, WINSIZEX/WINSIZEY, 0.1f, 300.0f); // Set up the perspective

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Done with OpenGL and SDL
    
    // Initialize the camera
    camera.setCameraPosition(0, 2.5f, 5,  0, 2.5f, 0,  0, 1, 0); 
}

// The keyboard function
// Instructions:
// w - move forward
// s - move backward
// a - strafe left
// d - strafe right
// e - fly upward
// c - fly downward
//
// in main(), ESC and Q are given for quitting
void keyboardInput(float direction) {
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(keystate[SDLK_w])
        camera.moveCamera(+direction);

    if(keystate[SDLK_s])
        camera.moveCamera(-direction);

    if(keystate[SDLK_a])
        camera.strafeCamera(-direction);

    if(keystate[SDLK_d])
        camera.strafeCamera(direction);

    if(keystate[SDLK_e])
        camera.flyCamera(3*direction);

    if(keystate[SDLK_c])
        camera.flyCamera(-3*direction);
}


// Main
int main(int argc, char *argv[]) {
    // Fullscreen and OpenGL
    int options = (SDL_FULLSCREEN|SDL_OPENGL);

    // If the screen can't be initialized, quit
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Unable to init SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    atexit(SDL_Quit);

    // Set up the screen
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(WINSIZEX, WINSIZEY, 32, options);
  
    if(screen == NULL) {
        cout << "Unable to set video: " << SDL_GetError() << endl;
        exit(1);
    }
  
    int done = 0;

    init();
    
    while(done == 0) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                done = 1; 
    
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) 
                    done = 1; // ESC or Q to quit
                
                keyboardInput(0.15f); // Keyboard function
            }
        }

        camera.moveMouse(); // Detect mouse motion
        drawScene(screen); // Draw everything
    }

    return 0;
}

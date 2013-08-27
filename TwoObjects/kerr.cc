#include "main.h"
#include "camera.h"
#include "odesolver.h"
#include "sphere.h"

#define pi 3.141592654

#define INCREMENT 0.003f
#define SIMSPEED 0.005 
#define HISTORY 1000000
#define PREVSTEP 1

Camera objCamera;
SDL_Event event;

double tint = 5.0;
double dt;

int step;
float history[HISTORY];
float history2[HISTORY];
int iterations = 2;

//                         {0,   t,    r,   th,  ph,   t',  r',  th',  ph'};
//double prevpos[MAXVAR] = {0, 0.0, 20.0, pi/2, 0.0, 20.0, 0.0, 0.28, 0.1}; //VERY large
//double prevpos[MAXVAR] = {0, 0.0, 19.0, pi/2, 0.0, 10.0, 0.0, 0.08, 0.08}; //This works, I think.
//double prevpos[MAXVAR] = {0, 0.0, 16.0, pi/2, 0.0, 30.0, 0.1, 0.5, 0.3}; //large sweeps
//double prevpos[MAXVAR] = {0, 0.0, 50.0, pi/2, 0.0, 9.0, 0.0, 0.02, 0.02}; //large and crazy.
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.1, 0.1}; //The strange orbit that goes around the top and bottom
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.2, 0.2}; //very stable but tight
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.08, 0.08}; //very stable but tight
double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.06, 0.06};

//double prevpos2[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.1, -0.1}; //counter rotating orbit... scary...
//double prevpos2[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, -0.1, -0.1}; //counter rotating orbit... scary too...
double prevpos2[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, -0.1, -0.2}; //counter rotating orbit... scary too...
//double prevpos2[MAXVAR] = {0, 0.0, 50.0, pi/2, 0.0, 9.0, 0.0, 0.02, -0.02}; //counter rotating orbit... scary too...

void drawCross() {
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.0);

    glBegin(GL_POINTS);
        glVertex3f(objCamera.mView.x, objCamera.mView.y, objCamera.mView.z);
    glEnd();
}

void drawGrid() {
    glBegin(GL_LINES);
    for(float i = -500; i <= 500; i += 5)
    {
        glColor3ub(150, 190, 150);
        glVertex3f(-500, 0, i);
        glVertex3f(500, 0, i);
        glVertex3f(i, 0,-500);
        glVertex3f(i, 0, 500);
    }
    glEnd();
}

void drawBH() {
    glColor3f(1.0f, 1.0f, 0.0f);
    drawSphere(2.0f, 20);
}

void drawKerr() {
    double Y[MAXVAR], Y2[MAXVAR];
    int nbad, nok, nvar;
    double h, t1;

    for(int i = 1; i <= MAXVAR; i++) {
        Y[i] = prevpos[i];
        Y2[i] = prevpos2[i];
    }

    nvar = 8;
    t1 = 0.0;
    h = 0.01;

    struct timeb ta;
    struct timeb tc;
    double deltat;

    if(tint == 5.0) {
        ftime(&ta);
        tint = ta.time + ta.millitm/1000.0;
        deltat = tint + INCREMENT;
    } else {
        ftime(&tc);
        deltat = tc.time + tc.millitm/1000.0;
    }

    dt = deltat - tint;

    odeint(Y, nvar, t1, SIMSPEED*dt, 1e-4, &h, 0.001, &nok, &nbad);
    odeint(Y2, nvar, t1, SIMSPEED*dt, 1e-4, &h, 0.001, &nok, &nbad);

    if(iterations <= HISTORY) {
        //history[iterations] = (float) Y[2] * cos(Y[4]) * sin(Y[3]);
        history[iterations] = (float) sqrt(pow(Y[2], 2) + pow(ANGM/MASS, 2)) * cos(Y[4]) * sin(Y[3]);
        history[iterations - 1] = (float) Y[2] * cos(Y[3]);
        history[iterations - 2] = (float) sqrt(pow(Y[2], 2) + pow(ANGM/MASS, 2)) * sin(Y[3]) * sin(Y[4]);
        //history[iterations - 2] = (float) Y[2] * sin(Y[3]) * sin(Y[4]);

        history2[iterations] = (float) sqrt(pow(Y2[2], 2) + pow(ANGM/MASS, 2)) * cos(Y2[4]) * sin(Y2[3]);
        history2[iterations - 1] = (float) Y2[2] * cos(Y2[3]);
        history2[iterations - 2] = (float) sqrt(pow(Y2[2], 2) + pow(ANGM/MASS, 2)) * sin(Y2[3]) * sin(Y2[4]);

        iterations += 3;
    }

    glPushMatrix();
        glColor3ub(0, 0, 139);
        glTranslatef((float) sqrt(pow(Y[2], 2) + pow(ANGM/MASS, 2)) * cos(Y[4]) * sin(Y[3]), (float) sqrt(pow(Y[2], 2) + pow(ANGM/MASS, 2)) * cos(Y[3]), (float) Y[2] * sin(Y[3]) * sin(Y[4]));
        //glTranslatef((float) Y[2] * cos(Y[4]) * sin(Y[3]), (float) Y[2] * cos(Y[3]), (float) Y[2] * sin(Y[3]) * sin(Y[4]));
        drawSphere(0.5f, 20);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(139, 0, 0);
        glTranslatef((float) sqrt(pow(Y2[2], 2) + pow(ANGM/MASS, 2)) * cos(Y2[4]) * sin(Y2[3]), (float) sqrt(pow(Y2[2], 2) + pow(ANGM/MASS, 2)) * cos(Y2[3]), (float) Y2[2] * sin(Y2[3]) * sin(Y2[4]));
        drawSphere(0.5f, 20);
    glPopMatrix();

    if(step >= PREVSTEP) {
        for(int i = 1; i <= MAXVAR; i++) {
            prevpos[i] = Y[i];
            prevpos2[i] = Y2[i];
        }

        step = 0;
    } else {
        step++;
    }
}

void drawTrace() {
    glBegin(GL_LINE_STRIP);
        glColor3ub(0, 0, 139);
        for(int i = 2; i <= iterations; i += 3)
            glVertex3f(history[i], history[i - 1], history[i - 2]);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3ub(139, 0, 0);
        for(int i = 2; i <= iterations; i += 3)
            glVertex3f(history2[i], history2[i - 1], history2[i - 2]);
    glEnd();
}

void DrawScene(SDL_Surface *screen) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,
              objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
              objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);

	//drawGrid();
	drawCross();
    drawBH();
    drawKerr();
    drawTrace();
    
    glFlush();
	SDL_GL_SwapBuffers();			
}

void init() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_EnableKeyRepeat(10, 30);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	SDL_ShowCursor(0);
		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(80.0f, WINSIZEX/WINSIZEY, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	objCamera.setCameraPosition(0, 2.5f, 5,  0, 2.5f, 0,  0, 1, 0);
}

void keyboardInput(float direction) {
	Uint8 *keystate = SDL_GetKeyState(NULL);

        if(keystate[SDLK_w])
            objCamera.moveCamera(+direction);

        if(keystate[SDLK_s])
            objCamera.moveCamera(-direction);

	    if(keystate[SDLK_a])
            objCamera.strafeCamera(-direction);

        if(keystate[SDLK_d])
            objCamera.strafeCamera(direction);

        if(keystate[SDLK_e])
            objCamera.flyCamera(3*direction);

        if(keystate[SDLK_c])
            objCamera.flyCamera(-3*direction);
}

int options = (SDL_FULLSCREEN|SDL_OPENGL);

int main(int argc, char *argv[]) {
    step = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
  		cout << "Unable to init SDL: " << SDL_GetError() << endl;
  		exit(1);
  	}
	
	atexit(SDL_Quit);

  	SDL_Surface *screen;
	//Maybe calculate computer speed and check what resolution to use?
  	screen = SDL_SetVideoMode(WINSIZEX, WINSIZEY, 32, options);
  
	if(screen == NULL) {
		cout << "Unable to set video: " << SDL_GetError() << endl;
    	exit(1);
  	}
  
	int done = 0;

	init();
    
  	while(done == 0) {
    	while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				done = 1; 
			}
	
			if(event.type == SDL_KEYDOWN) {
      			if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) {	
					done = 1;
				}
				
				keyboardInput(0.15f);
			}
		}
		objCamera.moveMouse();
   		DrawScene(screen);
	}

return 0;
}

#include "Main.h"
#include "Camera.h"
#include "Odesolver.h"
#include "Sphere.h"

#define pi 3.1416

#define INCREMENT 0.003f
#define SIMSPEED 5 
#define HISTORY 10000000
#define PREVSTEP 0

Camera objCamera;
SDL_Event event;

double tint = 5.0;
double dt;

int step;
float historyx[HISTORY], historyy[HISTORY], historyz[HISTORY];
int iterations;

// Some interesting initial conditions.
// TODO Read these from a config-file.
//                         {0,   t,    r,   th,  ph,   t',  r',  th',  ph'};
//double prevpos[MAXVAR] = {0, 0.0, 20.0, pi/2, 0.0, 20.0, 0.0, 0.28, 0.1};
//double prevpos[MAXVAR] = {0, 0.0, 19.0, pi/2, 0.0, 10.0, 0.0, 0.08, 0.08};
//double prevpos[MAXVAR] = {0, 0.0, 16.0, pi/2, 0.0, 30.0, 0.1, 0.5, 0.3};
//double prevpos[MAXVAR] = {0, 0.0, 50.0, pi/2, 0.0, 9.0, 0.2, 0.02, 0.02};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.1, 0.1};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.2, 0.2};
double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.08, 0.08};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.1, -0.1};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, -0.1, -0.1};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, -0.1, -0.2};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.02, -0.02};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.08, 0.06};
//double prevpos[MAXVAR] = {0, 0.0, 18.0, pi/2, 0.0, 23.0, 0.0, 0.06, 0.06};

void drawCross() {
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.0);

    glBegin(GL_POINTS);
        glVertex3f(objCamera.view.x, objCamera.view.y, objCamera.view.z);
    glEnd();
}

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

void drawBH() {
    glColor3f(1.0f, 1.0f, 0.0f);
    drawSphere(2.0f*MASS, 20);
}

void drawKerr() {
    double Y[MAXVAR];
    int nbad, nok, nvar;
    double h, t1;

    for(int i = 1; i <= MAXVAR; i++)
        Y[i] = prevpos[i];

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

    float x = (float) sqrt(pow(Y[2], 2) + pow(ANGM/MASS, 2)) * cos(Y[4]) * sin(Y[3]);
    float y = (float) Y[2] * cos(Y[3]);
    float z = (float) sqrt(pow(Y[2], 2) + pow(ANGM/MASS, 2)) * sin(Y[3]) * sin(Y[4]);

    if(iterations <= HISTORY) {
        historyx[iterations] = x;
        historyy[iterations] = y;
        historyz[iterations] = z;

        iterations++;
    }

    glPushMatrix();
        glColor3ub(0, 0, 139);
        glTranslatef(x, y, z);
        drawSphere(0.25f, 20);
    glPopMatrix();

    if(step >= PREVSTEP) {
        for(int i = 1; i <= MAXVAR; i++)
            prevpos[i] = Y[i];

        step = 0;
    } else {
        step++;
    }
}

void drawTrace() {
    glColor3f(1.0f, 1.0f, 1.0f);
    //glPointSize(0.01);

    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < iterations; i++) {
            glVertex3f(historyx[i], historyy[i], historyz[i]);
            glNormal3f(historyx[i], historyy[i], historyz[i]);
        }

        glVertex3f(0.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 0.0f);
    glEnd();
}

void DrawScene(SDL_Surface *screen) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(objCamera.pos.x,  objCamera.pos.y,  objCamera.pos.z,
              objCamera.view.x, objCamera.view.y, objCamera.view.z,
              objCamera.up.x,   objCamera.up.y,   objCamera.up.z);

    //drawGrid();
    drawBH();
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
    glPushMatrix();
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
    drawKerr();

    glDisable(GL_LIGHT0);
    drawTrace();
    drawCross();
    glEnable(GL_LIGHT0);
    
    glFlush();
    SDL_GL_SwapBuffers();           
}

void init() {
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_EnableKeyRepeat(10, 30);

    GLfloat mat_specular[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_shininess[] = {50.0};
    GLfloat white_light[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lmodel_ambient);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    //glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_POINT_SMOOTH); //test
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
    iterations = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Unable to init SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    atexit(SDL_Quit);

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
            if(event.type == SDL_QUIT) {
                done = 1; 
            }
    
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)   
                    done = 1;
                
                keyboardInput(0.15f);
            }
        }

        objCamera.moveMouse();
        DrawScene(screen);
    }

    return 0;
}

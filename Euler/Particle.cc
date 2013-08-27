// Author: Matthew Wraith

#include "Particle.h"

// Create a particle with position p, and velocity v. The sphere representing
// the particle will have a radius r. n is the number of subdivisions of the
// gluSphere.
Particle::Particle(vec4 p, vec4 v, double r, int n) {
    pos = p;
    ode = new Euler(p, v);
    sphere = new Sphere(r, n);
}

// Another constructor with the 4-vectors decomposed
Particle::Particle(
        double t, double r, double th, double ph,
        double vt, double vr, double vth, double vph,
        double radius, int n) {

    pos = vec4(t, r, th, ph);
    ode = new Euler(pos, vec4(vt, vr, vth, vph));
    sphere = new Sphere(radius, n);
}

Particle::~Particle() {
    delete ode;
    delete sphere;
}

// Draw the trace and the sphere at the position of the particle
void Particle::drawThis() {
    GLfloat *v;
    v = posToFloat();

    glPushMatrix();
        glTranslatef(v[0], v[1], v[2]);
        sphere->drawSphere();
    glPopMatrix();

    drawTrace();
}

// Conversion from Boyer-Lindquist Coords to the world coords
GLfloat *Particle::posToFloat() {
    float rescaledR = (float) sqrt(pow(pos.r, 2) + pow(ANGM/MASS, 2));
    float x = (float) rescaledR * cos(pos.ph) * sin(pos.th); 
    float y = (float) rescaledR * cos(pos.th);
    float z = (float) pos.r * sin(pos.th) * sin(pos.ph);

    GLfloat *cartesianPosition = new GLfloat[3];

    cartesianPosition[0] = x;
    cartesianPosition[1] = y;
    cartesianPosition[2] = z;

    return cartesianPosition;
}

// Draw a line for the history of the particle
void Particle::drawTrace() {
    glColor3f(0.4, 0.4, 0.4);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < iteration; i++)
            glVertex3fv(history[i]);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Get the next position of the particle
void Particle::update() {
    pos = ode->getNextStep();

    if (iteration < MAXHISTORY) {
        history[iteration] = posToFloat();

        iteration++;
    } else {
        iteration = 0;
    }

}


    

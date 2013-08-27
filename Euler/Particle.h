// Author: Matthew Wraith

#ifndef PARTICLE_H
#define PARTICLE_H

#include <GL/gl.h>
#include "Sphere.h"
#include "Euler.h"

// I have a function which tracks the particle over time. This is the maximum
// amount it will record in the history before it restarts the tracking.
#define MAXHISTORY 10000

// A relativistic particle in spacetime. Represented by a 4 vector.
class Particle {
public:
    // Constructors
    Particle(vec4 p, vec4 v, double r, int n);
    Particle(
        double t, double r, double th, double ph,
        double vt, double vr, double vth, double vph,
        double radius, int n);
    ~Particle();

    // Drawing and integrating
    void drawThis();
    void drawTrace();
    void update();

private:
    vec4 pos;
    Euler *ode;
    Sphere *sphere;
    int iteration;
    float *history[MAXHISTORY]; // Fill with old positions 

    GLfloat *posToFloat();
};

#endif

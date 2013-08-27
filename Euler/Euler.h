// Author: Matthew Wraith

#ifndef EULER_H
#define EULER_H

#include <cmath>
#include <iostream>
#include "Vector.h"

// The maximum number of first-order differential equations.
// For a set of four second order differential equations, you need 2*4=8
#define MAXVAR 8 
// The timestep on the simulation, the smaller this number, the more accurate
// and slower the simulation will run. The higher, the less accurate and faster
// the simulation will run.
#define STEP 0.01 

#define MASS 1 // Mass of the black hole
#define ANGM 3 // Angular momentum of the black hole

// This is my Euler ODE system solver
class Euler {
public:
    Euler(vec4 p, vec4 v); // Initialize with a position and velocity
    vec4 getNextStep(); // Calculate the next position

private:
    double init[MAXVAR];
    double x[MAXVAR];

    void euler();
    vec4 getPosition();
    void resetPosition();
    void takeDerivs(double *XT, double *XF);
};

#endif

// Author: Matthew Wraith

#ifndef SPHERE_H
#define SPHERE_H

#include <GL/gl.h>
#include <GL/glu.h>

class Sphere {
public:
    double radius;
    int ndiv;

    Sphere(double r, int n);

    void drawSphere();
};

#endif

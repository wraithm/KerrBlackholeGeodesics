// Author: Matthew Wraith

#include "Sphere.h"

// Construct a sphere of radius r, and n subdivisions
Sphere::Sphere(double r, int n) {
    radius = r;
    ndiv = n;
}

// Draw a gluSphere that's all smooth and pretty
void Sphere::drawSphere() {
    GLUquadricObj *quadric = gluNewQuadric();

    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, radius, ndiv, ndiv);
    gluDeleteQuadric(quadric);
}

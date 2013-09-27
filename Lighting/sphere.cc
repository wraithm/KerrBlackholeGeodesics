#include "main.h"
#include "sphere.h"

void drawSphere(double radius, int ndiv) {
    GLUquadricObj *quadric = gluNewQuadric();

    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, radius, ndiv, ndiv);
    gluDeleteQuadric(quadric);
}

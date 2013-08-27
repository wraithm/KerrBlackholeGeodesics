#include "main.h"
#include "sphere.h"

/*
void drawSphere(double radius, int ndiv)
{
    GLUquadricObj *quadric = gluNewQuadric();

    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, radius, ndiv, ndiv);
    gluDeleteQuadric(quadric);
}
*/

void drawSphere(double radius, int ndiv)
{
    int th, ta, dth, dta;
    dth = (int) ((350*10 - 10)/200);  
    dta = (int) ((350 - 10)/200);

    for(th = 10, ta = -90; th < 350*10, ta < 90; th = th + dth, ta = ta + dta)
    {
        glBegin(GL_LINE_STRIP);
            glVertex3f(cos(th*.01745)*cos(ta*.01745)*radius, sin(ta*.01745)*radius, sin(th*.01745)*cos(ta*.01745)*radius);

            /*
            glColor3f(
                cos(th*.01745 )*cos(ta*.01745)+.5, // unit sphere radius vector
                sin(ta*.01745)+.5,
                sin(th*.01745)*cos(ta*.01745)+.5);
            */
    }
    glEnd();
}

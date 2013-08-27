// Author: Matthew Wraith

#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "Vector.h"

// My screen is 1600 x 900.
// I should add this to a configuration file.
#define WINSIZEX 1600
#define WINSIZEY 900

#define MOUSEDIV 500 //originally 1000

class Camera {
public:
    vec3 pos;
    vec3 view;
    vec3 up;

    void setCameraPosition(
            double pos_x, double pos_y, double pos_z,
            double view_x, double view_y, double view_z,
            double up_x, double up_y, double up_z);

    void moveMouse();
    void moveCamera(double speed);
    void strafeCamera(double speed);
    void flyCamera(double speed);
    void rotateCamera(double speed);
    void drawCross();
    void drawCamera();
};

#endif

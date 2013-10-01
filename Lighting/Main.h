#ifndef MAIN_H
#define MAIN_H

#include <gl.h>
#include <glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include <math.h>
#include <sys/timeb.h>

using namespace std;

typedef struct Vector3 {
    Vector3() {}
    Vector3 (float new_x, float new_y, float new_z)
    { x = new_x; y = new_y; z = new_z; }
    Vector3 operator+(Vector3 v) { return Vector3(v.x+x, v.y+y, v.z+z); }
    Vector3 operator-(Vector3 v) { return Vector3(x-v.x, y-v.y, z-v.z); }
    Vector3 operator*(float number) { return Vector3(x*number, y*number, z*number); }
    Vector3 operator/(float number) { return Vector3(x/number, y/number, z/number); }
    float x, y, z;
} Vector3;

#endif

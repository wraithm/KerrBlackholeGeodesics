#include <gl.h>
#include <glu.h>
#include <SDL/SDL.h>
#include <iostream>
#include <math.h>
#include <sys/timeb.h>

using namespace std;

typedef struct tVector3
{
        tVector3() {}
        tVector3 (float new_x, float new_y, float new_z)
        {x = new_x; y = new_y; z = new_z;}
        tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
        tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
        tVector3 operator*(float number)     {return tVector3(x*number, y*number, z*number);}
        tVector3 operator/(float number)     {return tVector3(x/number, y/number, z/number);}
        float x, y, z;
}tVector3;

/*
//This is a six component vector for solving the ODEs.
typedef struct oVector6
{
    oVector6() {}
    oVector6(float new_t, float new_phi, float new_r, float new_tp, float new_phip, float new_rp)
    {
        t = new_t;
        phi = new_phi;
        r = new_r;
        tp = new_tp;
        phip = new_phip;
        rp = new_rp;
    }

    oVector6 operator+(oVector6 vVector) {return oVector6(vVector.t+t, vVector.phi+phi, vVector.r+r, vVector.tp+tp, vVector.phip+phip, vVector.rp+rp);}
    oVector6 operator-(oVector6 vVector) {return oVector6(t-vVector.t, phi-vVector.phi, r-vVector.r, tp-vVector.tp, phip-vVector.phip, rp-vVector.rp);}
    oVector6 operator*(float number)     {return oVector6(t*number, phi*number, r*number, tp*number, phip*number, rp*number);}
    oVector6 operator/(float number)     {return oVector6(t/number, phi/number, r/number, tp/number, phip/number, rp/number);}

    float t, phi, r, tp, phip, rp;
}oVector6;
*/

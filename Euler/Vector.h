#ifndef VECTOR_H
#define VECTOR_H

// My vector classes.
// 
// vec3 is a cartesian 3 vector
class vec3 {
public:
    double x, y, z; // Cartesian 3 vector

    vec3();
    vec3(double nx, double ny, double nz);
    vec3 operator+(vec3 v);
    vec3 operator-(vec3 v);
    vec3 operator*(double c);
    vec3 operator/(double c);
};

// vec4 is a Boyer-Lindquist 4 vector. This is for my relativistic calculations.
class vec4 {
public:
    double t, r, th, ph; // Time, Radial, Polar, Azimuthal

    vec4();
    vec4(double nt, double nr, double nth, double nph);
    vec4 operator+(vec4 v);
    vec4 operator-(vec4 v);
    vec4 operator*(double c);
    vec4 operator/(double c);
};

#endif

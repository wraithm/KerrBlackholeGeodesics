// Author: Matthew Wraith

#include "Vector.h"

vec3::vec3() {}
vec3::vec3(double nx, double ny, double nz) { 
    x = nx; y = ny; z = nz; 
}

vec3 vec3::operator+(vec3 v) { return vec3(v.x+x, v.y+y, v.z+z); }
vec3 vec3::operator-(vec3 v) { return vec3(x-v.x, y-v.y, z-v.z); }
vec3 vec3::operator*(double c) { return vec3(x*c, y*c, z*c); }
vec3 vec3::operator/(double c) { return vec3(x/c, y/c, z/c); }

vec4::vec4() {}
vec4::vec4 (double nt, double nr, double nth, double nph) { 
    t = nt; r = nr; th = nth; ph = nph; 
}

vec4 vec4::operator+(vec4 v) { return vec4(v.t+t, v.r+r, v.th+th, v.ph+ph); }
vec4 vec4::operator-(vec4 v) { return vec4(t-v.t, r-v.r, th-v.th, ph-v.ph); }
vec4 vec4::operator*(double c) { return vec4(t*c, r*c, th*c, ph*c); }
vec4 vec4::operator/(double c) { return vec4(t/c, r/c, th/c, ph/c); }

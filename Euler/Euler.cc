// Author: Matthew Wraith

#include "Euler.h"

// Constructor for the Euler simulation
// Get the coordinates from the position and velocity
Euler::Euler(vec4 p, vec4 v) {
    // Set the initial position
    init[0] = p.t; 
    init[1] = p.r; 
    init[2] = p.th; 
    init[3] = p.ph;
    init[4] = v.t; 
    init[5] = v.r; 
    init[6] = v.th;
    init[7] = v.ph;

    // set x to init.
    resetPosition();
}

// Get the position of the particle.
vec4 Euler::getPosition() {
    vec4 p;

    p.t = x[0];
    p.r = x[1];
    p.th = x[2];
    p.ph = x[3];

    return p;
}

// Copy the initial position and velocity into the current position.
// This resets the particle. If the particle falls into the black hole, the
// particle will reset.
void Euler::resetPosition() {
    for (int i = 0; i < MAXVAR; i++)
        x[i] = init[i];
}

// The equations for the Kerr metric are insane...
// I used Mathematica and some hand calculations to generate these equations.
//
// I've done serious tests on them. They're the correct equations.
// These are in Boyer-Lindquist Coordinates.
//
// This is a set of second order differential equations.
// euler() uses this function to solve the differential equation
//
// This takes the old position/velocity, and converts it to a new one.
void Euler::takeDerivs(double *XT, double *XF) {
    // These are defined in Euler.h
    const double M = MASS, a = ANGM/MASS;

    // Find the first derivatives
    XF[0] = XT[4];
    XF[1] = XT[5];
    XF[2] = XT[6];
    XF[3] = XT[7];


    // Find the second derivatives
    // tau is proper time.
    
    // t'' - d^2t/dtau^2
    XF[4] = (M*(XT[5]*((a*a - 2*pow(XT[1], 2) + a*a*cos(2*XT[2]))*(pow(a, 4) +
                        2*pow(XT[1], 4) + 3*a*a*XT[1]*(-2*M+XT[1]) + a*a*(a*a +
                            XT[1]*(6*M + XT[1]))*cos(2*XT[2]))*XT[4] +
                    8*a*(pow(XT[1], 4)*(a*a + 3*pow(XT[1], 2)) +
                        4*a*a*pow(XT[1], 4)*pow(cos(XT[2]), 2) + (- pow(a, 6) +
                            a*a*pow(a*XT[1], 2))*pow(cos(XT[2]),
                            4))*pow(sin(XT[2]), 2)*XT[7]) +
                a*a*XT[1]*XT[6]*(2*(pow(a, 4) + 2*pow(XT[1], 3)*(-8*M + XT[1]) +
                        a*a*XT[1]*(-14*M + 3*XT[1]) + a*a*(a*a + XT[1]*(-2*M +
                                XT[1]))*cos(2*XT[2]))*sin(2*XT[2])*XT[4] -
                    8*a*(a*a + XT[1]*(-2*M + XT[1]))*cos(XT[2])*(a*a +
                        2*pow(XT[1], 2) + a*a*cos(2*XT[2]))*pow(sin(XT[2]),
                        3)*XT[7])))/(2*(pow(XT[1], 2) +
                    pow(a*cos(XT[2]),2))*(2*pow(a*XT[1], 2)*(a*a + 2*M*M -
                        2*M*XT[1] + pow(XT[1], 2))*pow(cos(XT[2]), 2) + pow(a,
                        4)*(a*a + XT[1]*(-2*M + XT[1]))*pow(cos(XT[2]), 4) +
                    pow(XT[1], 2)*(pow(XT[1], 3) *(-2*M + XT[1]) + a*a*(4*M*M +
                            pow(XT[1], 2)) - 8*a*a*M*M*cos(2*XT[2]))));

    // r'' - d^2r/dtau^2
    XF[5] = (-(pow(pow(XT[1], 2) + a*a*pow(cos(XT[2]), 2), 2)*(XT[1]*(a*a -
                        M*XT[1]) + a*a*(M - XT[1])*pow(cos(XT[2]),
                            2))*pow(XT[5], 2))/(a*a + XT[1]*(-2*M + XT[1])) +
            (a*a + XT[1]*(-2*M + XT[1]))*(-M*pow(XT[1], 2) +
                a*a*M*pow(cos(XT[2]), 2))*pow(XT[4], 2) +
            2*a*a*cos(XT[2])*pow(pow(XT[1], 2) + a*a*pow(cos(XT[2]), 2),
                2)*sin(XT[2])*XT[5]*XT[6] + XT[1]*(a*a + XT[1]*(-2*M +
                        XT[1]))*pow(pow(XT[1], 2) + a*a*pow(cos(XT[2]), 2),
                        2)*pow(XT[6], 2) - 2*a*M*(a*a + XT[1]*(-2*M +
                                XT[1]))*(a*a - 2*pow(XT[1], 2) +
                                a*a*cos(2*XT[2]))*pow(sin(XT[2]), 2)*XT[4]*XT[7]
            - (a*a + XT[1]*(-2*M + XT[1]))*(a*a*M*pow(XT[1], 2) - pow(XT[1], 5)
                - a*a*(a*a*M + pow(XT[1], 2)*(M + 2*XT[1]))*pow(cos(XT[2]), 2) +
                pow(a, 4)*(M - XT[1])*pow(cos(XT[2]), 4))*pow(sin(XT[2])*XT[7],
                2))/pow(pow(XT[1], 2) + a*a*pow(cos(XT[2]), 2), 3); 

    // th' - d^2theta/dtau^2
    XF[6] = (-(a*a*cos(XT[2])*pow(pow(XT[1], 2) + pow(a*cos(XT[2]), 2),
                    2)*sin(XT[2])*pow(XT[5], 2))/(a*a + XT[1]*(-2*M + XT[1])) +
            a*a*M*XT[1]*sin(2*XT[2])*pow(XT[4], 2) - 2*XT[1]*pow(pow(XT[1], 2) +
                pow(a*cos(XT[2]), 2), 2)*XT[5]*XT[6] +
            a*a*cos(XT[2])*pow(pow(XT[1], 2) + pow(a*cos(XT[2]), 2),
                2)*sin(XT[2])*pow(XT[6], 2) - 4*a*M*XT[1]*(a*a + pow(XT[1],
                        2))*sin(2*XT[2])*XT[4]*XT[7] + cos(XT[2])*pow(pow(XT[1],
                            2) + pow(a*cos(XT[2]), 2), 2)*sin(XT[2])*(a*a -
                            2*M*XT[1] + pow(XT[1], 2) + (2*M*XT[1]*(a*a +
                                    pow(XT[1], 2)))/(pow(XT[1], 2) +
                                pow(a*cos(XT[2]), 2)) + (2*a*a*M*XT[1]*(a*a +
                                    pow(XT[1], 2))*pow(sin(XT[2]),
                                    2))/pow(pow(XT[1], 2) + pow(a*cos(XT[2]),
                                        2), 2))*pow(XT[7], 2))/pow(pow(XT[1], 2)
                                + pow(a*cos(XT[2]), 2), 3); 

    // ph' - d^2phi/dtau^2
    XF[7] = (2*XT[5]*(2*a*M*(-pow(XT[1], 4) + pow(a*cos(XT[2]), 4))*XT[4] + 
      (-pow(a, 4)*(a*a*M + XT[1]*(2*M*M - 2*M*XT[1] + 3*pow(XT[1], 2)))*
      pow(cos(XT[2]), 4) + pow(a, 6)*(M - XT[1])*pow(cos(XT[2]), 6) 
      + pow(XT[1], 3)*((2*M - XT[1])*pow(XT[1], 3) + a*a*M*(2*M + XT[1]) -
          4*a*a*M*M*cos(2*XT[2])) + XT[1]*pow(a*cos(XT[2]), 2)*(-2*a*a*M*M +
          pow(XT[1], 2)*(2*M*M + 3*M*XT[1] - 3*pow(XT[1], 2)) +
          4*a*a*M*M*cos(2*XT[2])))*XT[7]) - 0.5*XT[6]*(-8*a*M*XT[1]*(a*a +
      XT[1]*(-2*M + XT[1]))*(a*a + 2*pow(XT[1], 2) +
      a*a*cos(2*XT[2]))*cos(XT[2])*XT[4]/sin(XT[2]) + (4*(pow(XT[1], 2) +
          pow(a*cos(XT[2]), 2))*(-(2*M - XT[1])*pow(XT[1], 2)*(pow(XT[1], 3) +
              a*a*(2*M + XT[1])) + 2*a*a*pow(XT[1], 2)*(a*a + 2*M*M - 2*M*M -
              2*M*XT[1] + pow(XT[1], 2))*pow(cos(XT[2]), 2) + pow(a, 4)*(a*a +
              XT[1]*(-2*M + XT[1]))*pow(cos(XT[2]), 4))*cos(XT[2])/sin(XT[2]) +
      2*a*a*M*XT[1]*(a*a + pow(XT[1], 2))*(a*a + 2*XT[1]*(6*M + XT[1]) +
          a*a*cos(2*XT[2]))*sin(2*XT[2]))*XT[7]))/((pow(XT[1], 2) +
  pow(a*cos(XT[2]), 2))*(2*a*a*pow(XT[1], 2)*(a*a + 2*M*M - 2*M*XT[1] +
      pow(XT[1], 2))*pow(cos(XT[2]), 2) + pow(a, 4)*(a*a + XT[1]*(-2*M +
          XT[1]))*pow(cos(XT[2]), 4) + pow(XT[1], 2)*(pow(XT[1], 3)*(-2*M +
              XT[1]) + a*a*(4*M*M + pow(XT[1], 2)) - 8*a*a*M*M*cos(2*XT[2]))));
}

// Do the euler integration of the equations in takeDerivs()
void Euler::euler() {
    int i;
    double dx[MAXVAR];

    takeDerivs(x, dx);

    for (i = 0; i < MAXVAR; i++) {
        x[i] += STEP * dx[i]; // Integrate all of the equations

        if (isnan(x[i])) {
            std::cout << "A particle has fallen into the blackhole!" 
                << std::endl;

            resetPosition();
        }
    }
}

// Integrate and return the position.
vec4 Euler::getNextStep() {
    euler();
    return getPosition();
}



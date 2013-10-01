#include <math.h>
#include "Main.h"
#include "Odesolver.h"

double dtsave;

void Derivs(double t, double *XT, double *XF) {
    const double M = MASS, a = ANGM/MASS;

    XF[1] = XT[5];
    XF[2] = XT[6];
    XF[3] = XT[7];
    XF[4] = XT[8];

    //Yes, this happened.
    XF[5] = (M*(XT[6]*((a*a - 2*pow(XT[2], 2) + a*a*cos(2*XT[3]))*(pow(a, 4) + 2*pow(XT[2], 4) + 3*a*a*XT[2]*(-2*M+XT[2]) + a*a*(a*a + XT[2]*(6*M + XT[2]))*cos(2*XT[3]))*XT[5] + 8*a*(pow(XT[2], 4)*(a*a + 3*pow(XT[2], 2)) + 4*a*a*pow(XT[2], 4)*pow(cos(XT[3]), 2) + (- pow(a, 6) + a*a*pow(a*XT[2], 2))*pow(cos(XT[3]), 4))*pow(sin(XT[3]), 2)*XT[8]) + a*a*XT[2]*XT[7]*(2*(pow(a, 4) + 2*pow(XT[2], 3)*(-8*M + XT[2]) + a*a*XT[2]*(-14*M + 3*XT[2]) + a*a*(a*a + XT[2]*(-2*M + XT[2]))*cos(2*XT[3]))*sin(2*XT[3])*XT[5] - 8*a*(a*a + XT[2]*(-2*M + XT[2]))*cos(XT[3])*(a*a + 2*pow(XT[2], 2) + a*a*cos(2*XT[3]))*pow(sin(XT[3]), 3)*XT[8])))/(2*(pow(XT[2], 2) + pow(a*cos(XT[3]),2))*(2*pow(a*XT[2], 2)*(a*a + 2*M*M - 2*M*XT[2] + pow(XT[2], 2))*pow(cos(XT[3]), 2) + pow(a, 4)*(a*a + XT[2]*(-2*M + XT[2]))*pow(cos(XT[3]), 4) + pow(XT[2], 2)*(pow(XT[2], 3) *(-2*M + XT[2]) + a*a*(4*M*M + pow(XT[2], 2)) - 8*a*a*M*M*cos(2*XT[3]))));

    //omg, it happened again.
    XF[6] = (-(pow(pow(XT[2], 2) + a*a*pow(cos(XT[3]), 2), 2)*(XT[2]*(a*a - M*XT[2]) + a*a*(M - XT[2])*pow(cos(XT[3]), 2))*pow(XT[6], 2))/(a*a + XT[2]*(-2*M + XT[2])) + (a*a + XT[2]*(-2*M + XT[2]))*(-M*pow(XT[2], 2) + a*a*M*pow(cos(XT[3]), 2))*pow(XT[5], 2) + 2*a*a*cos(XT[3])*pow(pow(XT[2], 2) + a*a*pow(cos(XT[3]), 2), 2)*sin(XT[3])*XT[6]*XT[7] + XT[2]*(a*a + XT[2]*(-2*M + XT[2]))*pow(pow(XT[2], 2) + a*a*pow(cos(XT[3]), 2), 2)*pow(XT[7], 2) - 2*a*M*(a*a + XT[2]*(-2*M + XT[2]))*(a*a - 2*pow(XT[2], 2) + a*a*cos(2*XT[3]))*pow(sin(XT[3]), 2)*XT[5]*XT[8] - (a*a + XT[2]*(-2*M + XT[2]))*(a*a*M*pow(XT[2], 2) - pow(XT[2], 5) - a*a*(a*a*M + pow(XT[2], 2)*(M + 2*XT[2]))*pow(cos(XT[3]), 2) + pow(a, 4)*(M - XT[2])*pow(cos(XT[3]), 4))*pow(sin(XT[3])*XT[8], 2))/pow(pow(XT[2], 2) + a*a*pow(cos(XT[3]), 2), 3); 

    XF[7] = (-(a*a*cos(XT[3])*pow(pow(XT[2], 2) + pow(a*cos(XT[3]), 2), 2)*sin(XT[3])*pow(XT[6], 2))/(a*a + XT[2]*(-2*M + XT[2])) + a*a*M*XT[2]*sin(2*XT[3])*pow(XT[5], 2) - 2*XT[2]*pow(pow(XT[2], 2) + pow(a*cos(XT[3]), 2), 2)*XT[6]*XT[7] + a*a*cos(XT[3])*pow(pow(XT[2], 2) + pow(a*cos(XT[3]), 2), 2)*sin(XT[3])*pow(XT[7], 2) - 4*a*M*XT[2]*(a*a + pow(XT[2], 2))*sin(2*XT[3])*XT[5]*XT[8] + cos(XT[3])*pow(pow(XT[2], 2) + pow(a*cos(XT[3]), 2), 2)*sin(XT[3])*(a*a - 2*M*XT[2] + pow(XT[2], 2) + (2*M*XT[2]*(a*a + pow(XT[2], 2)))/(pow(XT[2], 2) + pow(a*cos(XT[3]), 2)) + (2*a*a*M*XT[2]*(a*a + pow(XT[2], 2))*pow(sin(XT[3]), 2))/pow(pow(XT[2], 2) + pow(a*cos(XT[3]), 2), 2))*pow(XT[8], 2))/pow(pow(XT[2], 2) + pow(a*cos(XT[3]), 2), 3); 

    XF[8] = (2*XT[6]*(2*a*M*(-pow(XT[2], 4) + pow(a*cos(XT[3]), 4))*XT[5] + (-pow(a, 4)*(a*a*M + XT[2]*(2*M*M - 2*M*XT[2] + 3*pow(XT[2], 2)))*pow(cos(XT[3]), 4) + pow(a, 6)*(M - XT[2])*pow(cos(XT[3]), 6) + pow(XT[2], 3)*((2*M - XT[2])*pow(XT[2], 3) + a*a*M*(2*M + XT[2]) - 4*a*a*M*M*cos(2*XT[3])) + XT[2]*pow(a*cos(XT[3]), 2)*(-2*a*a*M*M + pow(XT[2], 2)*(2*M*M + 3*M*XT[2] - 3*pow(XT[2], 2)) + 4*a*a*M*M*cos(2*XT[3])))*XT[8]) - 0.5*XT[7]*(-8*a*M*XT[2]*(a*a + XT[2]*(-2*M + XT[2]))*(a*a + 2*pow(XT[2], 2) + a*a*cos(2*XT[3]))*cos(XT[3])*XT[5]/sin(XT[3]) + (4*(pow(XT[2], 2) + pow(a*cos(XT[3]), 2))*(-(2*M - XT[2])*pow(XT[2], 2)*(pow(XT[2], 3) + a*a*(2*M + XT[2])) + 2*a*a*pow(XT[2], 2)*(a*a + 2*M*M - 2*M*M - 2*M*XT[2] + pow(XT[2], 2))*pow(cos(XT[3]), 2) + pow(a, 4)*(a*a + XT[2]*(-2*M + XT[2]))*pow(cos(XT[3]), 4))*cos(XT[3])/sin(XT[3]) + 2*a*a*M*XT[2]*(a*a + pow(XT[2], 2))*(a*a + 2*XT[2]*(6*M + XT[2]) + a*a*cos(2*XT[3]))*sin(2*XT[3]))*XT[8]))/((pow(XT[2], 2) + pow(a*cos(XT[3]), 2))*(2*a*a*pow(XT[2], 2)*(a*a + 2*M*M - 2*M*XT[2] + pow(XT[2], 2))*pow(cos(XT[3]), 2) + pow(a, 4)*(a*a + XT[2]*(-2*M + XT[2]))*pow(cos(XT[3]), 4) + pow(XT[2], 2)*(pow(XT[2], 3)*(-2*M + XT[2]) + a*a*(4*M*M + pow(XT[2], 2)) - 8*a*a*M*M*cos(2*XT[3]))));
}


void rk4(double *y, double *dydt, int n, double t, double h, double *yout) {
    int i;
    double th,hh,h6;
    double dym[MAXVAR], dyt[MAXVAR], yt[MAXVAR];

    hh = 0.5* h;
    h6 = h/6;
    th = t + hh;

    for (i=1; i<=n; i++) yt[i] = y[i] + hh * dydt[i];

    Derivs(th,yt,dyt);

    for (i=1; i<=n; i++) yt[i] = y[i] + hh * dyt[i];

    Derivs(th,yt,dym);

    for (i=1; i<=n; i++) {
        yt[i] = y[i] + h*dym[i];
        dym[i] = dyt[i] + dym[i];
    }

    Derivs(t+h,yt,dyt);

    for (i=1; i<=n; i++) yout[i] = y[i]+h6*(dydt[i]+dyt[i]+2.0*dym[i]);
}

void rkqc(double *y, double *dydt, int n, double *t, double htry, double eps, double *yscal, double *hdid, double *hnext) {
// LABEL: e1
const double pgrow=-0.20,
             pshrnk=-0.25,
             fcor=0.06666666,   // 1/15
             un = 1.0,
             safety=0.9,
             errcon=6e-4,
             tiny= 1e-20;    

    int i;
    double tsav,hh,h,temp,errmax;
    double dysav[MAXVAR], ysav[MAXVAR], ytemp[MAXVAR];

    tsav= *t;         // Save begin time
    for (i=1; i<=n; i++) {
        ysav[i] = y[i];
        dysav[i]= dydt[i];
    }

    h = htry;        //define increment for a try value
e1: hh = 0.5*h;      //take 2 half time steps
    rk4(ysav,dysav,n,tsav,hh,ytemp);
    *t = tsav + hh;
    Derivs(*t,ytemp,dydt);
    rk4(ytemp,dydt,n,*t,hh,y);
    *t = tsav + h;
    if (*t == tsav)
        cout << " Increment too small of independant variable" << endl;

    rk4(ysav,dysav,n,tsav,h,ytemp);
    errmax = 0;      //Evaluate error
    temp = 0;
    for (i=1; i<=n; i++) {
        ytemp[i] = y[i] - ytemp[i];   //ytemp = estimated error
        if (yscal[i]>tiny)  temp = fabs(ytemp[i]/yscal[i]);
        if (errmax < temp)  errmax = temp;
    }
    errmax = errmax/eps;     //real error / requirement
    if (errmax > un) {       //Error too big, reduce h
        h = safety*h*exp(pshrnk*log(errmax));
        goto e1;               //start again
    } else {                   //the step has been a success!
        *hdid = h;              //Calculate next time step
        if (errmax > errcon)
            *hnext=safety*h*exp(pgrow*log(errmax));
        else
            *hnext = 4.0*h;
    }
    for (i=1; i<=n; i++) y[i] += ytemp[i]*fcor;
}

void odeint(double *ystart, int nvar, double t1, double t2, double eps, double *h1, double hmin, int *nok, int *nbad) {
// LABEL: e99

    const int maxstp = 10000;
    const double two = 2.0, zero = 0.0;  

     int nstp,i;
     double tsav,t,hnext,hdid,h;
     double yscal[MAXVAR], y[MAXVAR], dydt[MAXVAR];

     dtsave = zero;  //not used here

     t = t1;
     if (t2 > t1) 
       h = fabs(*h1);
     else
       h = - fabs(*h1);
     *nok = 0;
     *nbad = 0;
     for (i=1; i<=nvar; i++)  y[i] = ystart[i];
     tsav = t - dtsave*two;
     for (nstp=1; nstp<=maxstp; nstp++) {
         Derivs(t,y,dydt);
         for (i=1; i<=nvar; i++)  yscal[i] = fabs(y[i])+fabs(dydt[i]*h);
         if (((t+h-t2)*(t+h-t1)) > zero)  h = t2 - t;
         rkqc(y,dydt,nvar,&t,h,eps,yscal,&hdid,&hnext);
         if (hdid == h) 
           *nok = *nok + 1;
         else
           *nbad = *nbad + 1;
         if (((t-t2)*(t2-t1)) >= zero) {
           for (i=1; i<=nvar; i++)  ystart[i] = y[i];
           goto e99;    //it's over
         }
         if (fabs(hnext) < hmin) {
           cout << " Time step too small!" << endl;
           *nok = -1 ;  //error flag
           goto e99;
         }
         h = hnext;
     }
     cout << " Pause in ODEINT - too many time steps!" << endl;
e99: *h1 = h;
} 

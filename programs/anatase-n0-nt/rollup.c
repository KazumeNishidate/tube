#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void roll(void){
  int i;
  double rx, ry, rz;
  double radius, theta;
  double ty, tz;
  radius = tb.LLy/(2.0*PI);

  tb.tx = (double *)calloc(tb.natm, sizeof(double)); // tube
  tb.ty = (double *)calloc(tb.natm, sizeof(double));
  tb.tz = (double *)calloc(tb.natm, sizeof(double));

  // center of the tube (2.0*radius, 2.0*radius, 0.0)
  // axis of the tube : z-direction
  for(i=0;i<tb.natm;i++){
    rx = tb.rx[i];
    ry = tb.ry[i];    
    rz = tb.rz[i];
    theta = ry/radius; // radius*theta = segment of a circle
    ty = (radius+rz)*cos(theta)+2.0*radius;
    tz = (radius+rz)*sin(theta)+2.0*radius;
    tb.tx[i] = ty;
    tb.ty[i] = tz;
    tb.tz[i] = rx;
  }
}




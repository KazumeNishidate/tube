#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void set_param(void){
  tb.n =  10;   // chiral index (n,m)
  tb.m =  4;
  tb.r_cc = 1.42;  // C-C distance (1.42 A)
  
  tb.a1x = tb.r_cc*(3.0/2.0);        // unit vector: a1 x
  tb.a1y = tb.r_cc*(sqrt(3.0)/2.0);  //  	        y
  
  tb.a2x = tb.r_cc*(3.0/2.0);        //  	     a2 x
  tb.a2y = tb.r_cc*(-sqrt(3.0)/2.0); //  	        y

  tb.chx = tb.n*tb.a1x +  tb.m*tb.a2x;  // Chiral vector: x
  tb.chy = tb.n*tb.a1y +  tb.m*tb.a2y;  //                y

  //  pick up a greatest common divisor (GCD)
  tb.d_R = get_gcd(2*tb.m+tb.n, 2*tb.n+tb.m);

  printf("\n");
  printf("  Chiral vector           :Ch = (%d,   %d) \n",tb.n, tb.m);  
  printf("                          :dR =       %d \n",tb.d_R);

  tb.t1  =  (2*tb.m +tb.n)/tb.d_R;  
  tb.t2  = -(2*tb.n +tb.m)/tb.d_R;
  printf("  Translational vector    : T = (%d,  %d) \n",tb.t1,tb.t2);
  
  tb.Tvx = tb.t1*tb.a1x + tb.t2*tb.a2x;
  tb.Tvy = tb.t1*tb.a1y + tb.t2*tb.a2y;

  tb.N = 2*(tb.n*tb.n+tb.m*tb.m+tb.n*tb.m)/tb.d_R;
  printf("  number of hexagons in 1D unit cell of CNT = %d\n\n",tb.N);  

  tb.aax = tb.chx;
  tb.aay = tb.chy;
  tb.bbx = tb.Tvx;
  tb.bby = tb.Tvy;  
  tb.ccx = tb.chx+tb.Tvx;
  tb.ccy = tb.chy+tb.Tvy;  

  printf("  Constructing Chiral vector\n");
  printf("  Atomic Coordinates (X, Y) in angstrom unit.\n");
  printf("   Origin                 : O(0, 0)\n");
  printf("   Chiral point           : A(%f, %f)\n",tb.aax, tb.aay);
  
  tb.L = sqrt(tb.aax*tb.aax + tb.aay*tb.aay); // length of the Chiral
  tb.d_t = tb.L/PI;                           // diameter of the tube
  tb.radius = tb.d_t/2.0;                     // radius of the tube
  
  printf("  Circum ferential length : L   = %f (A)\n",tb.L);
  printf("     Diameter of the tube : d_t = %f (A)\n",tb.L/PI);  
  
  printf("   Trans  point           : B(%f, %f)\n",tb.bbx, tb.bby);
  tb.rtv = sqrt(tb.bbx*tb.bbx + tb.bby*tb.bby);
  
  printf("   Diag   point           : C(%f, %f)\n\n",tb.ccx, tb.ccy);

  tb.theta = 2.0*tb.n + tb.m;
  tb.theta /= 2.0*sqrt(tb.n*tb.n+tb.m*tb.m+tb.n*tb.m);
  tb.theta = acos(tb.theta);
  printf("  Chiral angle           : theta =  %8.6f rad\n",tb.theta);
  printf("                                 = %8.6f deg\n",
	 tb.theta*180.0/PI);

  tb.alpha = tb.aax/sqrt(tb.aax*tb.aax+tb.aay*tb.aay);
  tb.alpha = acos(tb.alpha);
  printf("  Base angle             : alpha  =  %8.6f rad\n",tb.alpha);
  printf("                                  =  %8.6f deg\n\n",
	 tb.alpha*180.0/PI);

  tb.sq[0] = (round(-tb.bbx/4.32)+1)*4; // set the Origin atom number
                                        // it must be a multible of 4
  
  tb.nx = round((tb.aax-tb.bbx)/4.32) + 3;  // 'tb.bbx' may be negative
  tb.ny = round(tb.ccy/2.494) + 6;
  
  tb.LX = tb.radius*4.0;  // setup the supercell
  tb.LY = tb.radius*4.0;
  tb.LZ = tb.rtv;
  
}

void gen_gr(void){
  int i, j, cnt;
  double dx, dy;

  tb.dd = 2.0;
  tb.natm = tb.nx*tb.ny*4;    // total number of atoms of graphene (Gr)
  printf("  number of graphene atoms in this sandbox = %d\n\n",tb.natm);
  tb.rx = (double *)calloc(tb.natm, sizeof(double));  // coordinates of Gr
  tb.ry = (double *)calloc(tb.natm, sizeof(double));  

  tb.rrx = (double *)calloc(tb.natm, sizeof(double)); // rotated Gr
  tb.rry = (double *)calloc(tb.natm, sizeof(double));

  tb.crx = (double *)calloc(tb.natm, sizeof(double)); // cutout
  tb.cry = (double *)calloc(tb.natm, sizeof(double));
  
  dx = 0.0; dy = 0.0; cnt=0;
  for(j=0;j<tb.ny;j++){  
    for(i=0;i<tb.nx;i++){
      tb.rx[cnt] = dx;
      tb.ry[cnt] = dy;
      //      printf("c(%d): %f  %f\n",cnt,tb.rx[cnt], tb.ry[cnt]);
      cnt++;
      dx += tb.r_cc;
      tb.rx[cnt] = dx;
      tb.ry[cnt] = dy;
      //      printf("c(%d): %f  %f\n",cnt,tb.rx[cnt], tb.ry[cnt]);    
      cnt++;
      dx +=  tb.r_cc * sin(PI/6.0);
      dy += -tb.r_cc * cos(PI/6.0);
      tb.rx[cnt] = dx;
      tb.ry[cnt] = dy;
      //      printf("c(%d): %f  %f\n",cnt,tb.rx[cnt], tb.ry[cnt]);    
      cnt++;
      dx += tb.r_cc; 
      tb.rx[cnt] = dx;
      tb.ry[cnt] = dy;
      //      printf("c(%d): %f  %f\n",cnt,tb.rx[cnt], tb.ry[cnt]);
      dx += tb.r_cc * sin(PI/6.0);    
      dy += tb.r_cc * cos(PI/6.0);
      cnt++;
    }
    tb.x_max = dx;
    dx  = 0.0;
    dy += 2.0*tb.r_cc * cos(PI/6.0);    
  }
  tb.y_max = dy;

}

int get_gcd(int n1, int n2){
  while(n1!=n2)
    {
      if(n1 > n2)
	n1 -= n2;
      else
	n2 -= n1;
    }
  return n1;
}


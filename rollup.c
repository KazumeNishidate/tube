#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void check_nn(void){
  int i, j;
  int dup_flag;
  int cnt=0, cnt2=0;
  double rx, ry, rz;
  double dx, dy, dz, dr;
  double rdx, rdy, rdz;

  // tmp address to store the atomic coordinates
  tb.ttx = (double *)calloc(tb.catm, sizeof(double)); 
  tb.tty = (double *)calloc(tb.catm, sizeof(double));
  tb.ttz = (double *)calloc(tb.catm, sizeof(double));
  tb.idi = (int *)calloc(tb.catm, sizeof(int));
  tb.idj = (int *)calloc(tb.catm, sizeof(int));  

  rdx = tb.LX*0.5;
  rdy = tb.LY*0.5;
  rdz = tb.LZ*0.5;  
  for(i=0;i<tb.catm;i++){
    rx = tb.tx[i];
    ry = tb.ty[i];
    rz = tb.tz[i];
    for(j=i+1;j<tb.catm;j++){
      dx = rx - tb.tx[j];
      dy = ry - tb.ty[j];
      dz = rz - tb.tz[j];
      if(dx > rdx) dx -= tb.LX;  // to consider the cyclic BC
      if(dy > rdy) dy -= tb.LY;
      if(dz > rdz) dz -= tb.LZ;
      if(dx <-rdx) dx += tb.LX;
      if(dy <-rdy) dy += tb.LY;
      if(dz <-rdz) dz += tb.LZ;
      
      dr = sqrt(dx*dx + dy*dy + dz*dz);
      
      if(dr < 1.0) {      // dr < 1 angstrom
	tb.idi[cnt] = i;     // duplicated atom pair, i and j
	tb.idj[cnt] = j;
	cnt++;
      }
    }
  }
  printf("   total number of atoms is %d\n\n",tb.catm);
  for(i=0;i<cnt;i++){
    printf("   duplicated atom detected: (%d,  %d)\n",
	   tb.idi[i],tb.idj[i]);
  }

  cnt2=0;
  for(i=0;i<tb.catm;i++){
    dup_flag=0;
    for(j=0;j<cnt;j++){
      if(i==tb.idj[j]) {
	dup_flag=1; // duplication detected
	printf("   eliminating the atom : %d\n",i);
      }
    }
    if(dup_flag==1) continue;
    tb.ttx[cnt2] = tb.tx[i];  
    tb.tty[cnt2] = tb.ty[i];
    tb.ttz[cnt2] = tb.tz[i];
    cnt2++;
  }
  
  if(cnt>0){                    // reset the atomic positions
    tb.catm = cnt2;
    printf("\n   now the total number of atoms is %d\n",tb.catm);    
    for(i=0;i<tb.catm;i++){
      tb.tx[i] = tb.ttx[i];
      tb.ty[i] = tb.tty[i];
      tb.tz[i] = tb.ttz[i];
    }
  }
  free(tb.ttx);
  free(tb.tty);
  free(tb.ttz);
  free(tb.idi);
  free(tb.idj);  
}

void roll(void){
  int i;
  double rx, ry;
  double radius, theta;
  double tx, ty;
  radius = tb.L/(2.0*PI);

  tb.tx = (double *)calloc(tb.catm, sizeof(double)); // tube
  tb.ty = (double *)calloc(tb.catm, sizeof(double));
  tb.tz = (double *)calloc(tb.catm, sizeof(double));

  // center of the tube (2.0*radius, 2.0*radius, 0.0)
  // axis of the tube : z-direction
  for(i=0;i<tb.catm;i++){
    rx = tb.crx[i];
    ry = tb.cry[i];
    theta = rx/radius; // radius*theta = segment of a circle
    tx = radius*cos(theta)+2.0*radius;
    ty = radius*sin(theta)+2.0*radius;
    tb.tx[i] = tx;
    tb.ty[i] = ty;
    tb.tz[i] = ry;
  }
}

void cut_wall(void){
  int i, cnt=0;
  int io, ia, ib;
  double rx, ry;
  double sx, sy, by;
  double ax;

  io = tb.sq[0];
  ia = tb.sq[1];
  ib = tb.sq[2];

  sx = tb.rrx[io];  // origin
  sy = tb.rry[io];
  ax = tb.rrx[ia];  // chiral point
  by = tb.rry[ib];  // translation point  

  for(i=0;i<tb.natm;i++){
    rx = tb.rrx[i];
    ry = tb.rry[i];
    if(rx >= sx-0.01 && rx <= ax+0.01) {
      if(ry >= sy-0.01 && ry <= by+0.01) {
	tb.crx[cnt] =rx-sx;
	tb.cry[cnt] =ry-sy;
	if(i==tb.sq[0]) tb.wall[0] = cnt; // new origin
	if(i==tb.sq[1]) tb.wall[1] = cnt; //     chiral 
	if(i==tb.sq[2]) tb.wall[2] = cnt; //     trans
	if(i==tb.sq[3]) tb.wall[3] = cnt; //     diag
	cnt++;
      }
    }
  }
  tb.catm = cnt;
}

void rot_wall(void){
  int i;
  double alpha;
  double cs, sn;
  double sx, sy, xx, yy, rxx, ryy;

  sx = tb.rx[tb.sq[0]];  // origin
  sy = tb.ry[tb.sq[0]];

  alpha = tb.alpha;
  cs = cos(-alpha);
  sn = sin(-alpha);
  
  for(i=0;i<tb.natm;i++){
    xx = tb.rx[i] - sx;
    yy = tb.ry[i] - sy;
    rxx = cs*xx - sn*yy;
    ryy = sn*xx + cs*yy;
    tb.rrx[i] = rxx + sx;
    tb.rry[i] = ryy + sy;
  }
  
}

void set_wall(void){
  int i, ix, iy;
  int iax, iay, ibx, iby, icx, icy;
  double sx, sy;
  double ax, ay, bx, by, cx, cy;

  sx = tb.rx[tb.sq[0]];  // origin
  sy = tb.ry[tb.sq[0]];
  ax = tb.aax+sx;        // chiral point
  ay = tb.aay+sy;
  bx = tb.bbx+sx;        // translation point
  by = tb.bby+sy;  
  cx = tb.ccx+sx;        // diagonal point
  cy = tb.ccy+sy;

  iax = round(100*ax);
  iay = round(100*ay);  
  ibx = round(100*bx);
  iby = round(100*by);  
  icx = round(100*cx);
  icy = round(100*cy);  

  for(i=0;i<tb.natm;i++){
    ix = round(100.*tb.rx[i]);
    iy = round(100.*tb.ry[i]);
    if(ix == iax && iy == iay) tb.sq[1] = i;
    if(ix == ibx && iy == iby) tb.sq[2] = i;
    if(ix == icx && iy == icy) tb.sq[3] = i;    
  }
  printf("  Shifting the origin on Graphene\n");
  printf("  ID and atomic coordinates\n");
  printf("   Origin                : O(%3d) (%6.4f, %6.4f)\n",tb.sq[0],sx, sy);
  printf("   Chiral point          : A(%4d) (%6.4f, %6.4f)\n",tb.sq[1],tb.rx[tb.sq[1]], tb.ry[tb.sq[1]]);
  printf("   Translational point   : B(%4d) (%6.4f, %6.4f)\n",tb.sq[2],tb.rx[tb.sq[2]], tb.ry[tb.sq[2]]);
  printf("   Diagonal point        : C(%4d) (%6.4f, %6.4f)\n\n\n",tb.sq[3],tb.rx[tb.sq[3]], tb.ry[tb.sq[3]]);  
}

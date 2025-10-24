#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void set_param(void){
  int i;
  double dz;
    
  tb.n =12;   // (0, m) tube
  tb.m = 0;

  tb.Lx = 10.2445;       // dimentions of the cell 
  tb.Ly =  3.7850;
  tb.Lz = 10.0000;
  tb.LLy = tb.Ly*tb.n;

  tb.catm = 12;             // number of atoms in a cell
  tb.natm = tb.catm*tb.n;   // total number of atoms
  tb.rx = (double *)calloc(tb.natm, sizeof(double));  // coordinates
  tb.ry = (double *)calloc(tb.natm, sizeof(double));
  tb.rz = (double *)calloc(tb.natm, sizeof(double));
  tb.ik = (int *)calloc(tb.natm, sizeof(int));        // ion identifier: 0->Ti, 1->O

  // TiO2 anatase (101) band fragment in the cell
  tb.rx[0] = 9.1930; tb.ry[0] = 0.0000; tb.rz[0] = 3.5172; tb.ik[0] = 0;
  tb.rx[1] = 4.0707; tb.ry[1] = 1.8925; tb.rz[1] = 3.5172; tb.ik[1] = 0;
  tb.rx[2] = 6.9814; tb.ry[2] = 1.8925; tb.rz[2] = 4.3965; tb.ik[2] = 0;
  tb.rx[3] = 1.8592; tb.ry[3] = 0.0000; tb.rz[3] = 4.3965; tb.ik[3] = 0;
  tb.rx[4] = 7.3338; tb.ry[4] = 0.0000; tb.rz[4] = 4.2564; tb.ik[4] = 1;
  tb.rx[5] = 2.2115; tb.ry[5] = 1.8925; tb.rz[5] = 4.2564; tb.ik[5] = 1;
  tb.rx[6] = 5.1223; tb.ry[6] = 1.8925; tb.rz[6] = 5.1357; tb.ik[6] = 1;
  tb.rx[7] = 0.0000; tb.ry[7] = 0.0000; tb.rz[7] = 5.1357; tb.ik[7] = 1;
  tb.rx[8] = 3.7184; tb.ry[8] = 0.0000; tb.rz[8] = 3.6573; tb.ik[8] = 1;
  tb.rx[9] = 8.8406; tb.ry[9] = 1.8925; tb.rz[9] = 3.6573; tb.ik[9] = 1;
  tb.rx[10]= 5.9299; tb.ry[10]= 1.8925; tb.rz[10]= 2.7780; tb.ik[10]= 1;
  tb.rx[11]= 0.8076; tb.ry[11]= 0.0000; tb.rz[11]= 2.7780; tb.ik[11]= 1;

  dz = 0.0;
  for(i=0;i<12;i++){   // to reset the z-coordinates
    dz += tb.rz[i]/12.0;
  }  
  for(i=0;i<12;i++){   // <r_z> = 0.0 (A)
    tb.rz[i] -= dz;
  }  
}

void mk_ribbon(void){
  int i, j, cnt;
  double dy;
  for(i=1;i<tb.n;i++){
    dy = i*tb.Ly;
    cnt = i*tb.catm;
    for(j=0;j<tb.catm;j++){
      tb.rx[cnt+j] = tb.rx[j];
      tb.ry[cnt+j] = tb.ry[j]+dy;
      tb.rz[cnt+j] = tb.rz[j];
      tb.ik[cnt+j] = tb.ik[j];
    }
  }
}




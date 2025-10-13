#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void print_omxdat(void){
  int i, cnt=0;
  double radius = tb.L/(2.0*PI);  
  double tx, ty, tz;

  if((omxdat = fopen("./OMX.dat","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# OpenMX data file \n");
  fprintf(omxdat,"# (%d, %d) WS2 nanotube \n",tb.n,tb.m);
  fprintf(omxdat,"#\n \n");

  fprintf(omxdat,"System.CurrrentDirectory         ./    # default=./ \n");
  fprintf(omxdat,"System.Name         nanotube \n");
  fprintf(omxdat,"level.of.stdout       1    # default=1 (1-3)\n");
  fprintf(omxdat,"level.of.fileout      0    # default=1 (1-3)\n \n");
  fprintf(omxdat,"### DATA.PATH    ../../openmx3.9/DFT_DATA19 \n");
  
  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# Definition of Atomic Species \n");
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"Species.Number        2\n");
  fprintf(omxdat,"<Definition.of.Atomic.Species\n");
  fprintf(omxdat,"  W    W7.0-s3p3d2f1   W_PBE19\n");
  fprintf(omxdat,"  S    S7.0-s3p2d2f1   S_PBE19\n");  
  fprintf(omxdat,"Definition.of.Atomic.Species>\n");

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# Atoms\n");
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"Atoms.Number          %d\n",tb.catm/2+tb.catm); // 2 x (MoS2)
  fprintf(omxdat,"Atoms.SpeciesAndCoordinates.Unit   Ang # Ang|AU\n");    
  fprintf(omxdat,"<Atoms.SpeciesAndCoordinates\n");

  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 0) { // W
      cnt++;
      tx = tb.tx[i];
      ty = tb.ty[i];
      tz = tb.tz[i];
      fprintf(omxdat,"%3d   W  %8.5f %8.5f %8.5f   6.0  6.0\n",cnt, tx,ty,tz);
    }
  }

  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 1) { // S
      cnt++;
      tx = tb.tx[i];
      ty = tb.ty[i];
      tx -= 2.0*radius;
      ty -= 2.0*radius;
      tx /= radius;
      ty /= radius;
      tx *= (radius-tb.r_s2/2.0);
      ty *= (radius-tb.r_s2/2.0);
      tx += 2.0*radius;
      ty += 2.0*radius;
      
      tz = tb.tz[i];
      fprintf(omxdat,"%3d   S  %8.5f %8.5f %8.5f   3.0  3.0\n",cnt,tx,ty,tz);
    }
  }
  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 1) { // S
      cnt++;
      tx = tb.tx[i];
      ty = tb.ty[i];
      tx -= 2.0*radius;
      ty -= 2.0*radius;
      tx /= radius;
      ty /= radius;
      tx *= (radius+tb.r_s2/2.0);
      ty *= (radius+tb.r_s2/2.0);
      tx += 2.0*radius;
      ty += 2.0*radius;
      
      tz = tb.tz[i];
      fprintf(omxdat,"%3d   S  %8.5f %8.5f %8.5f   3.0  3.0\n",cnt,tx,ty,tz);
    }
  }
  fprintf(omxdat,"Atoms.SpeciesAndCoordinates>\n");  

  fprintf(omxdat,"Atoms.UnitVectors.Unit             Ang # Ang|AU \n");
  fprintf(omxdat,"<Atoms.UnitVectors\n");
  fprintf(omxdat," %8.5f  0.0    0.0 \n",tb.LX);
  fprintf(omxdat,"  0.0  %8.5f   0.0 \n",tb.LY);
  fprintf(omxdat,"  0.0   0.0   %8.5f\n",tb.LZ);
  fprintf(omxdat,"Atoms.UnitVectors>\n \n");

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# SCF\n");    
  fprintf(omxdat,"#\n \n");    

  fprintf(omxdat,"scf.XcType                 GGA-PBE # LDA|LSDA-CA|LSDA-PW|GGA-PBE \n");
  fprintf(omxdat,"scf.SpinPolarization        off    # On|Off|NC                   \n");
  fprintf(omxdat,"scf.ElectronicTemperature  300.0   # default=300 (K)             \n");
  fprintf(omxdat,"scf.energycutoff           200.0   # default=150 (Ry)            \n");
  fprintf(omxdat,"scf.maxIter                 100    # default=40                  \n");
  fprintf(omxdat,"scf.EigenvalueSolver        band   # DC|Cluster|Band             \n");
  fprintf(omxdat,"scf.Kgrid                  1 1 16  # means n1 x n2 x n3          \n");
  fprintf(omxdat,"scf.Mixing.Type          rmm-diisk # Simple|Rmm-Diis|Gr-Pulay|Kerker|Rmm-Diisk \n");
  fprintf(omxdat,"scf.Init.Mixing.Weight     0.30    # default=0.30                \n");
  fprintf(omxdat,"scf.Min.Mixing.Weight      0.001   # default=0.001              \n");
  fprintf(omxdat,"scf.Max.Mixing.Weight      0.400   # default=0.40               \n");
  fprintf(omxdat,"scf.Mixing.History          20     # default=5                  \n");  
  fprintf(omxdat,"scf.Mixing.StartPulay       5      # default=6                  \n");
  fprintf(omxdat,"scf.criterion             1.0e-8   # default=1.0e-6 (Hartree) \n\n");

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# MD or Geometry Optimization \n");    
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"MD.Type                   nomd     # Nomd|Opt|NVE|NVT_VS|NVT_NH \n");
  fprintf(omxdat,"                                   # Constraint_Opt|DIIS\n");  
  fprintf(omxdat,"MD.maxIter                  1      # default=1 \n");
  fprintf(omxdat,"MD.TimeStep                0.5     # default=0.5 (fs) \n");
  fprintf(omxdat,"MD.Opt.criterion        1.0e-4     # default=1.0e-4 (Hartree/Bohr) \n");      

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# Band dispersion\n");    
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"Band.dispersion            on      # on|off, default=off  \n");
  fprintf(omxdat,"Band.Nkpath                 1     \n");
  fprintf(omxdat,"<Band.kpath \n");
  fprintf(omxdat,"50  0.0000 0.0000 0.0000   0.0000 0.0000 0.5000  G Z\n");  
  fprintf(omxdat,"Band.kpath>\n");  

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# DOS\n");    
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"DosGauss.fileout          off     # on|off, default=off \n");
  fprintf(omxdat,"DosGauss.Num.Mesh         200     # default=200         \n");
  fprintf(omxdat,"DosGauss.Width            0.1     # default=0.2(eV)     \n\n");
  fprintf(omxdat,"DOS.fileout               off     # on|off, default=off \n");
  fprintf(omxdat,"DOS.Erange             -3.0   3.0 # default = -20 20    \n");
  fprintf(omxdat,"DOS.KGrid             1 1 30      # default = Kgrid1 Kgrid2 Kgrid3\n");
  fprintf(omxdat,"\n\n\n");
}

void print_qein(void){
  int i;
  double radius = tb.L/(2.0*PI);  
  double tx, ty, tz;

  if((qein = fopen("./QE.in","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(qein,"! (%d, %d) WS2 nanotube \n",tb.n,tb.m);
  fprintf(qein,"&SYSTEM \n");  
  fprintf(qein,"ibrav = 0 \n");    
  fprintf(qein,"nat = %d \n",tb.catm/2+tb.catm); // 2 x (MoS2)
  
  fprintf(qein,"ntyp = 2 \n");
  fprintf(qein,"/ \n");         
  fprintf(qein,"CELL_PARAMETERS {angstrom} \n");
  fprintf(qein," %8.5f  0.0    0.0 \n",tb.LX);
  fprintf(qein,"  0.0  %8.5f   0.0 \n",tb.LY);
  fprintf(qein,"  0.0   0.0   %8.5f\n",tb.LZ);
  fprintf(qein,"ATOMIC_POSITIONS {angstrom}\n");
  
  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 0) { // W
      tx = tb.tx[i];
      ty = tb.ty[i];
      tz = tb.tz[i];
      fprintf(qein,"W  %8.5f %8.5f %8.5f \n",tx,ty,tz);
    }
  }

  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 1) { // S
      tx = tb.tx[i];
      ty = tb.ty[i];
      tx -= 2.0*radius;
      ty -= 2.0*radius;
      tx /= radius;
      ty /= radius;
      tx *= (radius-tb.r_s2/2.0);
      ty *= (radius-tb.r_s2/2.0);
      tx += 2.0*radius;
      ty += 2.0*radius;
      
      tz = tb.tz[i];
      fprintf(qein,"S  %8.5f %8.5f %8.5f \n",tx,ty,tz);
    }
  }
  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 1) { // S
      tx = tb.tx[i];
      ty = tb.ty[i];
      tx -= 2.0*radius;
      ty -= 2.0*radius;
      tx /= radius;
      ty /= radius;
      tx *= (radius+tb.r_s2/2.0);
      ty *= (radius+tb.r_s2/2.0);
      tx += 2.0*radius;
      ty += 2.0*radius;
      
      tz = tb.tz[i];
      fprintf(qein,"S  %8.5f %8.5f %8.5f \n",tx,ty,tz);
    }
  }

}

void print_tube(void){
  int i;
  double tx, ty, tz;
  double radius = tb.L/(2.0*PI);

  if((tbout = fopen("./fig5_tube.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }

  fprintf(tbout," (%d, %d) nanotube \n",tb.n,tb.m);  
  fprintf(tbout," 1.0 \n");
  fprintf(tbout," %8.5f  0.0    0.0 \n",tb.LX);
  fprintf(tbout,"  0.0  %8.5f   0.0 \n",tb.LY);
  fprintf(tbout,"  0.0   0.0   %8.5f\n",tb.LZ);
  fprintf(tbout,"      W  S \n");
  fprintf(tbout,"      %d %d\n",tb.n_B, tb.n_N*2);
  fprintf(tbout,"      C \n");
  
  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 0) { // W
      tx = tb.tx[i];
      ty = tb.ty[i];
      tz = tb.tz[i];
      fprintf(tbout,"  %8.5f %8.5f %8.5f \n",tx,ty,tz);
    }
  }

  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 1) { // S
      tx = tb.tx[i];
      ty = tb.ty[i];
      tx -= 2.0*radius;
      ty -= 2.0*radius;
      tx /= radius;
      ty /= radius;
      tx *= (radius-tb.r_s2/2.0);
      ty *= (radius-tb.r_s2/2.0);
      tx += 2.0*radius;
      ty += 2.0*radius;
      
      tz = tb.tz[i];
      fprintf(tbout,"  %8.5f %8.5f %8.5f \n",tx,ty,tz);
    }
  }
  for(i=0;i<tb.catm;i++){
    if(tb.BN[i] == 1) { // S
      tx = tb.tx[i];
      ty = tb.ty[i];
      tx -= 2.0*radius;
      ty -= 2.0*radius;
      tx /= radius;
      ty /= radius;
      tx *= (radius+tb.r_s2/2.0);
      ty *= (radius+tb.r_s2/2.0);
      tx += 2.0*radius;
      ty += 2.0*radius;
      
      tz = tb.tz[i];
      fprintf(tbout,"  %8.5f %8.5f %8.5f \n",tx,ty,tz);
    }
  }
  
}

void print_cutwall(void){
  int i;
  int io, ia, ib, ic;
  int n_B=0, n_N=0;
  if((cutout = fopen("./fig4_cutout.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  io = tb.wall[0];
  ia = tb.wall[1];
  ib = tb.wall[2];
  ic = tb.wall[3];  

  for(i=0;i<tb.catm;i++){       // The number of B atoms may not equal to
    if(tb.crBN[i]==0) n_B +=1;  // that of the N atoms because of the 
  }                             // duplicate atoms at the boundaries. 
  for(i=0;i<tb.catm;i++){       // So we count these numbers 
    if(tb.crBN[i]==1) n_N +=1;  // explicitly here.
  }
  
  fprintf(cutout,"nanotube wall \n");
  fprintf(cutout," 1.0 \n");
  fprintf(cutout,"    %8.5f    0.0         0.0 \n",tb.crx[ia]);
  fprintf(cutout,"     0.0      %8.5f     0.0 \n",tb.cry[ib]);
  fprintf(cutout,"     0.0        0.0         5.0 \n");
  fprintf(cutout,"      W   S\n");
  fprintf(cutout,"      %d   %d\n",n_B+4,n_N*2);
  fprintf(cutout,"      Selective dynamics \n");  
  fprintf(cutout,"      C \n");

  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",  // corner Mo 1
	    tb.crx[io],  tb.cry[io]);
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",  // corner Mo 2
	    tb.crx[ia],  tb.cry[ia]);
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",  // corner Mo 3
	    tb.crx[ib],  tb.cry[ib]);
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",  // corner Mo 4
	    tb.crx[ic],  tb.cry[ic]);

  for(i=0;i<tb.catm;i++){
  }
  
  for(i=0;i<tb.catm;i++){
    if(tb.crBN[i]==0){       //  W
      fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",
	      tb.crx[i],  tb.cry[i]);
    }
  }

  for(i=0;i<tb.catm;i++){
    if(tb.crBN[i]==1){       //  S
      fprintf(cutout,"    %8.5f    %8.5f   %8.5f \n", // S_upper
	      tb.crx[i],  tb.cry[i], 2.0+tb.r_s2/2.0);
      fprintf(cutout,"    %8.5f    %8.5f   %8.5f \n", // S_lower
	      tb.crx[i],  tb.cry[i], 2.0-tb.r_s2/2.0);
    }
  }
  
}

void print_rotwall(void){
  int i;
  int io, ia, ib, ic;  
  double dy;
  if((rotwallout = fopen("./fig3_rotated-wall.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(rotwallout,"rotated sheet \n");
  fprintf(rotwallout," 1.0 \n");
  fprintf(rotwallout,"    %8.5f    0.0         0.0 \n",tb.x_max+tb.dd*2.0);
  fprintf(rotwallout,"     0.0       %8.5f     0.0 \n", tb.y_max+tb.dd*2.0);
  fprintf(rotwallout,"     0.0        0.0         5.0 \n");
  io = tb.sq[0];
  ia = tb.sq[1];
  ib = tb.sq[2];
  ic = tb.sq[3];
  
  fprintf(rotwallout,"      O   W   S \n");
  fprintf(rotwallout,"      4   %d   %d \n",tb.natm/2,tb.natm/2);
  fprintf(rotwallout,"      Selective dynamics \n");  
  fprintf(rotwallout,"      C \n");
  
  dy = 2*tb.dd;
  fprintf(rotwallout,"    %8.5f    %8.5f   2.0 \n",
	    tb.rrx[io],  tb.rry[io]+dy);
  fprintf(rotwallout,"    %8.5f    %8.5f   2.0 \n",
	    tb.rrx[ia],  tb.rry[ia]+dy);
  fprintf(rotwallout,"    %8.5f    %8.5f   2.0 \n",
	    tb.rrx[ib],  tb.rry[ib]+dy);
  fprintf(rotwallout,"    %8.5f    %8.5f   2.0 \n",
	    tb.rrx[ic],  tb.rry[ic]+dy);

  for(i=0;i<tb.natm;i++){
    if(tb.BN[i] == 0) continue;
    fprintf(rotwallout,"  %8.5f %8.5f 2.0 \n",
	    tb.rrx[i],  tb.rry[i]+dy);	    
  }
  for(i=0;i<tb.natm;i++){
    if(tb.BN[i] == 1) continue;
    fprintf(rotwallout,"  %8.5f %8.5f 2.0 \n",
	    tb.rrx[i],  tb.rry[i]+dy);
  }
}

void print_gr(void){
  int i;
  if((grout = fopen("./fig1_sandbox.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }

  fprintf(grout,"WS2 sheet \n");
  
  fprintf(grout," 1.0 \n");
  fprintf(grout,"    %8.5f    0.0         0.0 \n",tb.x_max+tb.dd*2.0);
  fprintf(grout,"     0.0       %8.5f     0.0 \n", tb.y_max+tb.dd*2.0);
  
  fprintf(grout,"     0.0        0.0         5.0 \n");
  fprintf(grout,"      W  S \n");
  
  fprintf(grout,"      %d %d\n",tb.natm/2, tb.natm); // Mo and S
  fprintf(grout,"      Selective dynamics \n");  
  fprintf(grout,"      C \n");
  for(i=0;i<tb.natm;i++){
    if(tb.BN[i] == 1) continue;  
    fprintf(grout,"  %8.5f %8.5f 2.0 \n",  // BN=0 -> W
	    tb.rx[i]+tb.dd,  tb.ry[i]+2*tb.dd);
  }
  for(i=0;i<tb.natm;i++){
    if(tb.BN[i] == 0) continue; // BN=1 -> S
    fprintf(grout,"  %8.5f %8.5f  3.50614 \n",  // S_upper
	    tb.rx[i]+tb.dd,  tb.ry[i]+2*tb.dd);
    fprintf(grout,"  %8.5f %8.5f  0.49386 \n",  // S_lower
	    tb.rx[i]+tb.dd,  tb.ry[i]+2*tb.dd);	    
  }

}

void print_cht(void){
  double sx, sy;
  double ax, ay, bx, by, cx, cy;
  double dx=0.0;
  if((chtout = fopen("./fig2_Ch-T-vectors.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  if(tb.Tvx<0.0) dx = -tb.Tvx; // Tvx can be negative
  sx = 0.0+dx+tb.dd;
  sy = 0.0+tb.dd;
  ax = tb.chx+dx+tb.dd;
  ay = tb.chy+tb.dd;
  bx = tb.Tvx+dx+tb.dd;
  by = tb.Tvy+tb.dd;
  cx = tb.ccx+dx+tb.dd;
  cy = tb.ccy+tb.dd;  
  fprintf(chtout,"Ch T vector check: \n");
  fprintf(chtout," 1.0 \n");
  fprintf(chtout," %f   0.0    0.0 \n",ax+tb.dd);
  fprintf(chtout," 0.0   %f   0.0 \n", cy+tb.dd);
  fprintf(chtout,"   0.0   0.0    5.0 \n");
  fprintf(chtout,"      C \n");
  fprintf(chtout,"      4 \n");
  fprintf(chtout,"      Selective dynamics \n");  
  fprintf(chtout,"      C \n");
  fprintf(chtout," %f %f 2.0 \n",sx, sy);  // origin
  fprintf(chtout," %f %f 2.0 \n",ax, ay); // Chiral 
  fprintf(chtout," %f %f 2.0 \n",bx, by); // Trans
  fprintf(chtout," %f %f 2.0 \n",cx, cy);
}



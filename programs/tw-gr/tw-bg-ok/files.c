#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void print_dwall(void){
  int i;
  int io, ia, ib, ic;
  if((dwall = fopen("./fig5_dwall.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  io = tb.wall[0];
  ia = tb.wall[1];
  ib = tb.wall[2];
  ic = tb.wall[3];

  fprintf(dwall,"2nd layer (twisted image) \n");
  fprintf(dwall," 1.0 \n");
  fprintf(dwall,"    %8.5f     0.0         0.0 \n",tb.LX);
  fprintf(dwall,"     0.0      %8.5f     0.0 \n",tb.LY);
  fprintf(dwall,"     0.0        0.0         5.0 \n");
  fprintf(dwall,"      O   C \n");
  fprintf(dwall,"      4   %d \n",tb.catm-4);
  fprintf(dwall,"      Selective dynamics \n");  
  fprintf(dwall,"      C \n");
  fprintf(dwall,"    %8.5f    %8.5f   2.0 \n",
	    tb.brx[io],  tb.bry[io]);
  fprintf(dwall,"    %8.5f    %8.5f   2.0 \n",
	    tb.brx[ia],  tb.bry[ia]);
  fprintf(dwall,"    %8.5f    %8.5f   2.0 \n",
	    tb.brx[ib],  tb.bry[ib]);
  fprintf(dwall,"    %8.5f    %8.5f   2.0 \n",
	    tb.brx[ic],  tb.bry[ic]);
  
  for(i=0;i<tb.catm;i++){
    if(i==io||i==ia||i==ib||i==ic) continue;
    fprintf(dwall,"    %8.5f    %8.5f   2.0 \n",
	    tb.brx[i],  tb.bry[i]);
  }
}

void print_omxdat(void){
  int i;
  double tx, ty, tz;

  if((omxdat = fopen("./OMX.dat","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# OpenMX data file \n");
  fprintf(omxdat,"# (%d, %d) nanotube \n",tb.n,tb.m);
  fprintf(omxdat,"#\n \n");

  fprintf(omxdat,"System.CurrrentDirectory         ./    # default=./ \n");
  fprintf(omxdat,"System.Name         nanotube \n");
  fprintf(omxdat,"level.of.stdout       1    # default=1 (1-3)\n");
  fprintf(omxdat,"level.of.fileout      0    # default=1 (1-3)\n \n");
  fprintf(omxdat,"### DATA.PATH    ../../openmx3.9/DFT_DATA19 \n");
  
  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# Definition of Atomic Species \n");
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"Species.Number        1\n");
  fprintf(omxdat,"<Definition.of.Atomic.Species\n");
  fprintf(omxdat,"  C   C6.0-s2p2d1     C_PBE19\n");
  fprintf(omxdat,"Definition.of.Atomic.Species>\n");

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# Atoms\n");
  fprintf(omxdat,"#\n \n");

  fprintf(omxdat,"Atoms.Number          %d\n",tb.catm);
  fprintf(omxdat,"Atoms.SpeciesAndCoordinates.Unit   Ang # Ang|AU\n");    
  fprintf(omxdat,"<Atoms.SpeciesAndCoordinates\n");
  for(i=0;i<tb.catm;i++){
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    fprintf(omxdat,"%3d C  %8.5f %8.5f %8.5f    2.0  2.0\n",i+1,tx,ty,tz);
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
  fprintf(omxdat,"scf.Kgrid                  5 5 1  # means n1 x n2 x n3          \n");
  fprintf(omxdat,"scf.Mixing.Type           rmm-diis # Simple|Rmm-Diis|Gr-Pulay|Kerker|Rmm-Diisk \n");
  fprintf(omxdat,"scf.Init.Mixing.Weight     0.30    # default=0.30                \n");
  fprintf(omxdat,"scf.Min.Mixing.Weight      0.001   # default=0.001              \n");
  fprintf(omxdat,"scf.Max.Mixing.Weight      0.400   # default=0.40               \n");
  fprintf(omxdat,"scf.Mixing.History          7      # default=5                  \n");  
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
  fprintf(omxdat,"50 0.0000 0.0000 0.0000  0.5000 0.0000 0.0000 G X\n");
  fprintf(omxdat,"Band.kpath>\n");  
  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# DOS\n");    
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"DosGauss.fileout          off     # on|off, default=off \n");
  fprintf(omxdat,"DosGauss.Num.Mesh         200     # default=200         \n");
  fprintf(omxdat,"DosGauss.Width            0.1     # default=0.2(eV)     \n\n");
  fprintf(omxdat,"DOS.fileout               off     # on|off, default=off \n");
  fprintf(omxdat,"DOS.Erange             -3.0   3.0 # default = -20 20    \n");
  fprintf(omxdat,"DOS.KGrid             30 30 1      # default = Kgrid1 Kgrid2 Kgrid3\n");
  fprintf(omxdat,"\n\n\n");
}

void print_qein(void){
  int i;
  double tx, ty, tz;

  if((qein = fopen("./QE.in","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(qein,"! (%d, %d) nanotube \n",tb.n,tb.m);
  fprintf(qein,"&SYSTEM \n");  
  fprintf(qein,"ibrav = 0 \n");    
  fprintf(qein,"nat = %d \n",tb.catm);       
  fprintf(qein,"ntyp = 1 \n");
  fprintf(qein,"/ \n");         
  fprintf(qein,"CELL_PARAMETERS {angstrom} \n");
  fprintf(qein," %8.5f  0.0    0.0 \n",tb.LX);
  fprintf(qein,"  0.0  %8.5f   0.0 \n",tb.LY);
  fprintf(qein,"  0.0   0.0   %8.5f\n",tb.LZ);
  fprintf(qein,"ATOMIC_POSITIONS {angstrom}\n");
  
  for(i=0;i<tb.catm;i++){
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    fprintf(qein,"C  %8.5f %8.5f %8.5f \n",tx,ty,tz);
  }

}

void print_tdwg(void){
  int i;
  double tx, ty, tz;

  if((tbout = fopen("./fig6_tdwg.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }

  fprintf(tbout," (%d, %d) twisted double layer graphene \n",tb.n,tb.m);  
  fprintf(tbout," 1.0 \n");
  fprintf(tbout," %8.5f  0.0    0.0 \n",tb.LX);
  fprintf(tbout,"  0.0  %8.5f   0.0 \n",tb.LY);
  fprintf(tbout,"  0.0   0.0   20.0\n");
  fprintf(tbout,"      C \n");
  fprintf(tbout,"      %d \n",tb.catm);
  fprintf(tbout,"      C \n");
  
  for(i=0;i<tb.catm;i++){
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    fprintf(tbout,"  %8.5f %8.5f %8.5f \n",tx,ty,tz);
  }
  
}

void print_cutwall(void){
  int i;
  int io, ia, ib, ic;
  if((cutout = fopen("./fig4_cutout.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  io = tb.wall[0];
  ia = tb.wall[1];
  ib = tb.wall[2];
  ic = tb.wall[3];
  tb.LX = tb.crx[ia];
  tb.LY = tb.cry[ib];
  
  fprintf(cutout,"1st layer graphene \n");
  fprintf(cutout," 1.0 \n");
  fprintf(cutout,"    %8.5f    0.0         0.0 \n",tb.LX);
  fprintf(cutout,"     0.0      %8.5f     0.0 \n",tb.LY);
  fprintf(cutout,"     0.0        0.0         5.0 \n");
  fprintf(cutout,"      O   C \n");
  fprintf(cutout,"      4   %d \n",tb.catm-4);
  fprintf(cutout,"      Selective dynamics \n");  
  fprintf(cutout,"      C \n");
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",
	    tb.crx[io],  tb.cry[io]);
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",
	    tb.crx[ia],  tb.cry[ia]);
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",
	    tb.crx[ib],  tb.cry[ib]);
  fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",
	    tb.crx[ic],  tb.cry[ic]);
  
  for(i=0;i<tb.catm;i++){
    if(i==io||i==ia||i==ib||i==ic) continue;
    fprintf(cutout,"    %8.5f    %8.5f   2.0 \n",
	    tb.crx[i],  tb.cry[i]);
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
  fprintf(rotwallout,"rotated graphene \n");
  fprintf(rotwallout," 1.0 \n");
  fprintf(rotwallout,"    %8.5f    0.0         0.0 \n",tb.x_max+tb.dd*2.0);
  fprintf(rotwallout,"     0.0       %8.5f     0.0 \n", tb.y_max+tb.dd*2.0);
  fprintf(rotwallout,"     0.0        0.0         5.0 \n");
  fprintf(rotwallout,"      O   C \n");
  fprintf(rotwallout,"      4   %d \n",tb.natm-4);
  fprintf(rotwallout,"      Selective dynamics \n");  
  fprintf(rotwallout,"      C \n");
  io = tb.sq[0];
  ia = tb.sq[1];
  ib = tb.sq[2];
  ic = tb.sq[3];
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
    if(i==io||i==ia||i==ib||i==ic) continue;
    fprintf(rotwallout,"    %8.5f    %8.5f   2.0 \n",
	    tb.rrx[i],  tb.rry[i]+dy);
  }
}

void print_gr(void){
  int i;
  if((grout = fopen("./fig1_sandbox.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(grout,"graphene \n");
  fprintf(grout," 1.0 \n");
  fprintf(grout,"    %8.5f    0.0         0.0 \n",tb.x_max+tb.dd*2.0);
  fprintf(grout,"     0.0       %8.5f     0.0 \n", tb.y_max+tb.dd*2.0);
  fprintf(grout,"     0.0        0.0         5.0 \n");
  fprintf(grout,"      C \n");
  fprintf(grout,"      %d \n",tb.natm);
  fprintf(grout,"      Selective dynamics \n");  
  fprintf(grout,"      C \n");
  for(i=0;i<tb.natm;i++){
    fprintf(grout,"    %8.5f    %8.5f   2.0 \n",
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
  fprintf(chtout,"Ch T vector check: O(10, 10) \n");
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



#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
#include  "tube.h"
#include  "prototypes.h"

void print_omxdat(void){
  int i, cnt=0;
  double tx, ty, tz;

  if((omxdat = fopen("./OMX.dat","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# OpenMX data file \n");
  fprintf(omxdat,"# TiO2(101) (%d, %d) nanotube \n",tb.n,tb.m);
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
  fprintf(omxdat,"  Ti   Ti7.0-s3p2d1     Ti_PBE19\n");
  fprintf(omxdat,"   O    O6.0-s2p2d1      O_PBE19\n");  
  fprintf(omxdat,"Definition.of.Atomic.Species>\n");

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# Atoms\n");
  fprintf(omxdat,"#\n \n");

  fprintf(omxdat,"Atoms.Number          %d\n",tb.natm);
  fprintf(omxdat,"Atoms.SpeciesAndCoordinates.Unit   Ang # Ang|AU\n");    
  fprintf(omxdat,"<Atoms.SpeciesAndCoordinates\n");
  for(i=0;i<tb.natm;i++){      // Ti
    if(tb.ik[i]!=0) continue;   
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    cnt++;
    fprintf(omxdat,"%3d Ti  %8.5f %8.5f %8.5f    6.0  6.0\n",cnt,tx,ty,tz);
  }
  for(i=0;i<tb.natm;i++){      // O
    if(tb.ik[i]!=1) continue;
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    cnt ++;
    fprintf(omxdat,"%3d  O  %8.5f %8.5f %8.5f    3.0  3.0\n",cnt,tx,ty,tz);
  }
  fprintf(omxdat,"Atoms.SpeciesAndCoordinates>\n");  

  fprintf(omxdat,"Atoms.UnitVectors.Unit             Ang # Ang|AU \n");
  fprintf(omxdat,"<Atoms.UnitVectors\n");
  fprintf(omxdat," %8.5f  0.0    0.0 \n",tb.Sx);
  fprintf(omxdat,"  0.0  %8.5f   0.0 \n",tb.Sy);
  fprintf(omxdat,"  0.0   0.0   %8.5f\n",tb.Sz);
  fprintf(omxdat,"Atoms.UnitVectors>\n \n");

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# SCF\n");    
  fprintf(omxdat,"#\n \n");    

  fprintf(omxdat,"scf.XcType                 GGA-PBE # LDA|LSDA-CA|LSDA-PW|GGA-PBE \n");
  fprintf(omxdat,"scf.SpinPolarization        off    # On|Off|NC                   \n");
  fprintf(omxdat,"scf.ElectronicTemperature  300.0   # default=300 (K)             \n");
  fprintf(omxdat,"scf.energycutoff           200.0   # default=150 (Ry)            \n");
  fprintf(omxdat,"scf.maxIter                 200    # default=40                  \n");
  fprintf(omxdat,"scf.EigenvalueSolver        band   # DC|Cluster|Band             \n");
  fprintf(omxdat,"scf.Kgrid                  1 12 1  # means n1 x n2 x n3          \n");
  fprintf(omxdat,"scf.Mixing.Type          rmm-diisk # Simple|Rmm-Diis|Gr-Pulay|Kerker|Rmm-Diisk \n");
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
  fprintf(omxdat,"50  0.0000 0.0000 0.0000   0.0000 0.5000 0.0000  G Z\n");  
  fprintf(omxdat,"Band.kpath>\n");  

  fprintf(omxdat,"#\n");
  fprintf(omxdat,"# DOS\n");    
  fprintf(omxdat,"#\n \n");
  fprintf(omxdat,"DosGauss.fileout          off     # on|off, default=off \n");
  fprintf(omxdat,"DosGauss.Num.Mesh         200     # default=200         \n");
  fprintf(omxdat,"DosGauss.Width            0.1     # default=0.2(eV)     \n\n");
  fprintf(omxdat,"DOS.fileout               off     # on|off, default=off \n");
  fprintf(omxdat,"DOS.Erange             -3.0   3.0 # default = -20 20    \n");
  fprintf(omxdat,"DOS.KGrid             1 30 1      # default = Kgrid1 Kgrid2 Kgrid3\n");
  fprintf(omxdat,"\n\n\n");
}


void print_tube(void){
  int i;
  double tx, ty, tz;
  double radius;

  if((tbout = fopen("./fig3_tube.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }

  radius = tb.LLx/(2.0*PI);
  tb.Sx = 4*radius;
  tb.Sy = tb.Ly;  
  tb.Sz = 4*radius;  
  fprintf(tbout," (%d, %d) nanotube \n",tb.n,tb.m);  
  fprintf(tbout," 1.0 \n");
  fprintf(tbout," %6.3f    0.0    0.0 \n",tb.Sx);
  fprintf(tbout,"  0.0   %6.3f    0.0 \n",tb.Sy);
  fprintf(tbout,"  0.0     0.0  %6.3f \n",tb.Sz);
  fprintf(tbout,"      Ti  O \n");
  fprintf(tbout,"      %d  %d\n",4*tb.m,8*tb.m);
  fprintf(tbout,"      C \n");
  
  for(i=0;i<tb.natm;i++){
    if(tb.ik[i]==1) continue;
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    fprintf(tbout,"  %10.5f %10.5f %10.5f \n",tx,ty,tz);
  }
  for(i=0;i<tb.natm;i++){
    if(tb.ik[i]==0) continue;
    tx = tb.tx[i];
    ty = tb.ty[i];
    tz = tb.tz[i];
    fprintf(tbout,"  %10.5f %10.5f %10.5f \n",tx,ty,tz);
  }
  
}


void print_ribbon(){
  int i;
  if((rbnout = fopen("./fig2_ribbon.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(rbnout,"(0, %d)  TiO2 anatase (101) ribbon unit \n",tb.m);
  fprintf(rbnout," 1.0 \n");
  fprintf(rbnout,"    %8.5f    0.0         0.0 \n",tb.LLx);
  fprintf(rbnout,"     0.0       %8.5f     0.0 \n", tb.Ly);
  fprintf(rbnout,"     0.0        0.0         5.0 \n");
  fprintf(rbnout,"      Ti  O \n");
  fprintf(rbnout,"      %d  %d \n", 4*tb.m, 8*tb.m);
  fprintf(rbnout,"      Selective dynamics \n");  
  fprintf(rbnout,"      C \n");
  for(i=0;i<tb.natm;i++){
    if(tb.ik[i]==0) { // it is Ti
      fprintf(rbnout,"    %8.5f    %8.5f   %8.5f \n",
	      tb.rx[i],tb.ry[i],tb.rz[i]);
    }
  }
  for(i=0;i<tb.natm;i++){
    if(tb.ik[i]==1) { // it is O
      fprintf(rbnout,"    %8.5f    %8.5f   %8.5f \n",
	      tb.rx[i],tb.ry[i],tb.rz[i]);
    }
  }

  
}
void print_unit(){
  int i;
  if((uout = fopen("./fig1_sandbox.vasp","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  fprintf(uout,"TiO2 anatase (101) ribbon unit \n");
  fprintf(uout," 1.0 \n");
  fprintf(uout,"    %8.5f    0.0         0.0 \n",tb.Lx);
  fprintf(uout,"     0.0       %8.5f     0.0 \n", tb.Ly);
  fprintf(uout,"     0.0        0.0         5.0 \n");
  fprintf(uout,"      Ti  O \n");
  fprintf(uout,"      4   8 \n");
  fprintf(uout,"      Selective dynamics \n");  
  fprintf(uout,"      C \n");
  for(i=0;i<tb.catm;i++){
    fprintf(uout,"    %8.5f    %8.5f   %8.5f \n",
	    tb.rx[i],tb.ry[i],tb.rz[i]+2.5);
  }
}

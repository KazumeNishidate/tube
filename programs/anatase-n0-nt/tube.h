#include  <stdio.h>
#include  <sys/types.h>
FILE *uout, *rbnout, *tbout, *omxdat;

#ifndef  PI
#define  PI         3.1415926535897932385
#endif

typedef	struct {
  int n, m;       // (n,m) tube
  int catm;       // number of atoms in a 2D cell
  int natm;       // total number of atoms
  double Lx, Ly, Lz, LLx, LLy;     // cell size
  double Sx, Sy, Sz;          // supercell
  double *rx, *ry, *rz;
  int *ik;
  double *tx, *ty, *tz;       // tube
  
} tube_parameters;

tube_parameters tb;


#include  <stdio.h>
#include  <sys/types.h>
FILE *chtout, *grout, *wallout, *rotwallout, *cutout, *tbout, *qein;

#ifndef  PI
#define  PI         3.1415926535897932385
#endif

typedef	struct {
  int nx, ny;  // size of graphene sheet (Gr)
  int natm;    // number of carbon atoms in the Gr
  int catm;    // number of carbon atoms in the cut Gr
  double *rx, *ry, *rrx, *rry, *crx, *cry;
  double *tx,  *ty,  *tz;  // tube coordinates
  double *ttx, *tty, *ttz; //
  int    *idi, *idj;       // duplication ID
  int    *BN;     // B or N
  int    *crBN;   // B or N on the 2D fragment
  int    *id_BN;  // duplication ID for B or N
  int    n_B, n_N;  // number of B or N of the tube
  
  double x_max, y_max;   //  maximum coordinates of the Gr
  double dd;   // edge width of the Gr
  
  int n;  // Chiral index (n, m)
  int m;
  int g;  // GCM
  double r_cc;
  double a1x, a1y, a2x, a2y;  // unit vector of Gr
  double chx, chy;  // Chiral vector
  int d_R;          // result of the GCD(2m+n, 2n+m)
  int t1, t2;
  double Tvx, Tvy;  // Translational vector
  double rtv;       // length of the Translational vector
  double L;         // circumferential length of the (n, m) tube
  double d_t;       // diameter of the tube
  int N;            // number of hexagons in 1D unit cell of CNT
  int sq[4];        // define the square region
  int wall[4];
  
  double aax, aay, bbx, bby, ccx, ccy; // define the rectangle area
  double oa_s, oa_t; // OA: y = oa_s*x + oa_t
  double ob_s, ob_t; // OB: y = ob_s*x + ob_t   
  double theta;
  double alpha;
  double radius;     // radius of the tube
  double LX, LY, LZ; // supercell dimension
  
} tube_parameters;

tube_parameters tb;



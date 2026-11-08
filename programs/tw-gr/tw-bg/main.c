#include  <stdlib.h>
#include  <stdio.h>
#include  "tube.h"
#include  "prototypes.h"

int  main(void)
{
  set_param();    // parameter setup

  gen_gr();       // generate the graphene sandbox
  print_gr();
  print_cht();
  
  set_wall();     // make up the wall for CNT
  
  rot_wall();     // rotate the wall
  print_rotwall();

  cut_wall();     
  print_cutwall();
  print_dwall();
  
  mk_tdwg();      // make the twisted graphene bilayer
  check_nn();
  print_tdwg();

  print_qein();   // generate the input file for QE
  print_omxdat(); // generate the input file for OpenMX
  return 0;
}




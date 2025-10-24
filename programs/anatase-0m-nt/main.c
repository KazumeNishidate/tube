#include  <stdlib.h>
#include  <stdio.h>
#include  "tube.h"
#include  "prototypes.h"

int  main(void)
{
  set_param();    // parameter setup
  print_unit();
  mk_ribbon();
  print_ribbon();
  roll();
  print_tube();
  print_omxdat();
  
  return 0;
}




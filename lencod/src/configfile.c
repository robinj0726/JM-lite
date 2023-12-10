#include "global.h"
#include "configfile.h"

void Configure (VideoParameters *p_Vid, InputParameters *p_Inp, int ac, char *av[])
{
  memset (&cfgparams, 0, sizeof (InputParameters));
  //Set default parameters.
  printf ("Setting Default Parameters...\n");
  InitParams(Map);

}
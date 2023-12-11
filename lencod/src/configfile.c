#include "global.h"
#include "configfile.h"

void Configure (VideoParameters *p_Vid, InputParameters *p_Inp, int ac, char *av[])
{
  memset (&cfgparams, 0, sizeof (InputParameters));
  //Set default parameters.
  printf ("Setting Default Parameters...\n");
  InitParams(Map);

  // (0:Disable Display of Encoder Params 1: Enable)
  p_Inp->DisplayEncParams = 1; 

  if (p_Inp->DisplayEncParams)
    DisplayEncoderParams(Map);
}

static int DisplayEncoderParams(Mapping *Map)
{
  int i = 0;

  printf("******************************************************\n");
  printf("*               Encoder Parameters                   *\n");
  printf("******************************************************\n");
  while (Map[i].TokenName != NULL)
  {
    if (Map[i].Type == 0)
      printf("Parameter %s = %d\n",Map[i].TokenName,* (int *) (Map[i].Place));
    else if (Map[i].Type == 1)
      printf("Parameter %s = ""%s""\n",Map[i].TokenName,(char *)  (Map[i].Place));
    else if (Map[i].Type == 2)
      printf("Parameter %s = %.2f\n",Map[i].TokenName,* (double *) (Map[i].Place));
      i++;
  }
  printf("******************************************************\n");
  return -1;
}

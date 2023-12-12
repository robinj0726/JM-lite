#include "global.h"
#include "configfile.h"

char *GetConfigFileContent (char *Filename)
{
  return NULL;
}

int InitParams(Mapping *Map)
{
  int i = 0;

  while (Map[i].TokenName != NULL)
  {
    if (Map[i].Type == 0)
        * (int *) (Map[i].Place) = (int) Map[i].Default;
    else if (Map[i].Type == 2)
    * (double *) (Map[i].Place) = Map[i].Default;
      i++;
  }
  return -1;
}

int DisplayParams(Mapping *Map, char *message)
{
  int i = 0;

  printf("******************************************************\n");
  printf("*               %s                   *\n", message);
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
  return i;
}

void ParseContent (InputParameters *p_Inp, Mapping *Map, char *buf, int bufsize)
{
  *p_Inp = cfgparams;
}
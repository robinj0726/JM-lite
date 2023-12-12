#define INCLUDED_BY_CONFIGFILE_C

#include "global.h"
#include "config_common.h"
#include "configfile.h"
#include "img_io.h"

static void PatchInp                (VideoParameters *p_Vid, InputParameters *p_Inp);

void Configure (VideoParameters *p_Vid, InputParameters *p_Inp, int ac, char *av[])
{
  char *content = NULL;
  char *filename=DEFAULTCONFIGFILENAME;

  memset (&cfgparams, 0, sizeof (InputParameters));
  //Set default parameters.
  printf ("Setting Default Parameters...\n");
  InitParams(Map);

  printf ("Parsing Configfile %s", filename);
  content = GetConfigFileContent (filename);
  // if (NULL==content)
  //   error (errortext, 300);
  ParseContent (p_Inp, Map, NULL, 0);
  printf ("\n");

  PatchInp(p_Vid, p_Inp);

  cfgparams = *p_Inp;

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

static void PatchInp (VideoParameters *p_Vid, InputParameters *p_Inp)
{
  ParseVideoType(&p_Inp->input_file1);
  ParseFrameNoFormatFromString (&p_Inp->input_file1);

  // (0:Disable Display of Encoder Params 1: Enable)
  p_Inp->DisplayEncParams = 1; 
  strcpy(p_Inp->input_file1.fname, "foreman_part_qcif.yuv");

}
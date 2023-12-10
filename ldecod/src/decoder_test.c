#include "win32.h"
#include "h264decoder.h"

#define BITSTREAM_FILENAME  "test.264"
#define DECRECON_FILENAME   "test_dec.yuv"
#define ENCRECON_FILENAME   "test_rec.yuv"

static void Configure(InputParameters *p_Inp, int ac, char *av[])
{
  //char *config_filename=NULL;
  //char errortext[ET_SIZE];
  memset(p_Inp, 0, sizeof(InputParameters));
  strcpy(p_Inp->infile, BITSTREAM_FILENAME); //! set default bitstream name
  strcpy(p_Inp->outfile, DECRECON_FILENAME); //! set default output file name
  strcpy(p_Inp->reffile, ENCRECON_FILENAME); //! set default reference file name

  p_Inp->bDisplayDecParams = 0;
  if(!p_Inp->bDisplayDecParams)
  {
    fprintf(stdout,"--------------------------------------------------------------------------\n");
    fprintf(stdout," Input H.264 bitstream                  : %s \n",p_Inp->infile);
    fprintf(stdout," Output decoded YUV                     : %s \n",p_Inp->outfile);
    //fprintf(stdout," Output status file                     : %s \n",LOGFILE);
    fprintf(stdout," Input reference file                   : %s \n",p_Inp->reffile);

    fprintf(stdout,"--------------------------------------------------------------------------\n");
  }
}

int main(int argc, char **argv)
{
    InputParameters InputParams;

    //get input parameters;
    Configure(&InputParams, argc, argv);

    //open decoder;
    // iRet = OpenDecoder(&InputParams);

    return 0;
}
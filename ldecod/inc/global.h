#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "win32.h"
#include "defines.h"

// input parameters from configuration file
typedef struct inp_par
{
  char infile[FILE_NAME_SIZE];                       //!< H.264 inputfile
  char outfile[FILE_NAME_SIZE];                      //!< Decoded YUV 4:2:0 output
  char reffile[FILE_NAME_SIZE];                      //!< Optional YUV 4:2:0 reference file for SNR measurement

  int bDisplayDecParams;
} InputParameters;

// video parameters
typedef struct video_par
{
  struct inp_par      *p_Inp;
} VideoParameters;

typedef struct decoder_params
{
  InputParameters   *p_Inp;          //!< Input Parameters
  VideoParameters   *p_Vid;          //!< Image Parameters
  int64              bufferSize;     //!< buffersize for tiff reads (not currently supported)
  int                UsedBits;      // for internal statistics, is adjusted by read_se_v, read_ue_v, read_u_1
  FILE              *p_trace;        //!< Trace file
  int                bitcounter;
} DecoderParams;

#endif
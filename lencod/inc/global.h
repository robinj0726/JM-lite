#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "defines.h"
#include "win32.h"
#include "params.h"
#include "ifunctions.h"

char errortext[ET_SIZE]; //!< buffer for error message for exit with error()

typedef struct inp_par_enc InputParameters;

typedef struct video_par
{
  InputParameters          *p_Inp;
  struct decoded_picture_buffer *p_Dpb_layer[MAX_NUM_DPB_LAYERS];

  int num_of_layers; 

  struct stat_parameters  *p_Stats;

} VideoParameters;

typedef struct encoder_params
{
  InputParameters   *p_Inp;          //!< Input Parameters
  VideoParameters   *p_Vid;          //!< Image Parameters
  FILE              *p_trace;        //!< Trace file
  int64              bufferSize;     //!< buffer size for tiff reads (not currently supported)
} EncoderParams;

extern void free_encoder_memory        (VideoParameters *p_Vid, InputParameters *p_Inp);

extern void error(char *text, int code);

#endif
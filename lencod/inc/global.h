#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "defines.h"
#include "win32.h"
#include "params.h"

typedef struct inp_par_enc InputParameters;

typedef struct video_par
{
  InputParameters          *p_Inp;
  struct decoded_picture_buffer *p_Dpb_layer[MAX_NUM_DPB_LAYERS];

} VideoParameters;

typedef struct encoder_params
{
  InputParameters   *p_Inp;          //!< Input Parameters
  VideoParameters   *p_Vid;          //!< Image Parameters
  FILE              *p_trace;        //!< Trace file
  int64              bufferSize;     //!< buffer size for tiff reads (not currently supported)
} EncoderParams;

#endif
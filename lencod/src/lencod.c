#include <stdio.h>

#include "global.h"
#include "mbuffer.h"

EncoderParams   *p_Enc = NULL;

static void alloc_video_params( VideoParameters **p_Vid)
{
  *p_Vid = (VideoParameters *) calloc(1, sizeof(VideoParameters));

  (*p_Vid)->p_Dpb_layer[0]     = (DecodedPictureBuffer *) calloc(MAX_NUM_DPB_LAYERS, sizeof(DecodedPictureBuffer));
  {
    int i;
    for(i=1; i<MAX_NUM_DPB_LAYERS; i++)
    {
      (*p_Vid)->p_Dpb_layer[i] = (*p_Vid)->p_Dpb_layer[i-1] + 1;
      (*p_Vid)->p_Dpb_layer[i]->layer_id = i;
    }
  }

}

static void alloc_params( InputParameters **p_Inp )
{
  *p_Inp = (InputParameters *) calloc(1, sizeof(InputParameters));
}

static void alloc_encoder( EncoderParams **p_Enc)
{
  *p_Enc = (EncoderParams *) calloc(1, sizeof(EncoderParams));

  alloc_video_params(&((*p_Enc)->p_Vid));
  alloc_params(&((*p_Enc)->p_Inp));
  (*p_Enc)->p_trace = NULL;
  (*p_Enc)->bufferSize = 0;

}

int main(int argc, char **argv)
{
  init_time();

  alloc_encoder(&p_Enc);

  return 0;
}
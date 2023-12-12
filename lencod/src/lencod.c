#include <stdio.h>

#include "global.h"
#include "mbuffer.h"

EncoderParams   *p_Enc = NULL;

static void init_encoder        (VideoParameters *p_Vid, InputParameters *p_Inp);
static void encode_sequence     (VideoParameters *p_Vid, InputParameters *p_Inp);

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

  (*p_Inp)->top_left          = NULL;
  (*p_Inp)->bottom_right      = NULL;
  (*p_Inp)->slice_group_id    = NULL;
  (*p_Inp)->run_length_minus1 = NULL;
}

static void alloc_encoder( EncoderParams **p_Enc)
{
  *p_Enc = (EncoderParams *) calloc(1, sizeof(EncoderParams));

  alloc_video_params(&((*p_Enc)->p_Vid));
  alloc_params(&((*p_Enc)->p_Inp));
  (*p_Enc)->p_trace = NULL;
  (*p_Enc)->bufferSize = 0;

}

static void free_encoder (EncoderParams *p_Enc)
{
  free_pointer( p_Enc );
}

static void free_params (InputParameters *p_Inp)
{
  if ( p_Inp != NULL )
  {
    free_pointer( p_Inp->top_left );
    free_pointer( p_Inp->bottom_right );
    free_pointer( p_Inp->slice_group_id );
    free_pointer( p_Inp->run_length_minus1 );
    free_pointer( p_Inp );
  }
}

int main(int argc, char **argv)
{
  init_time();

  alloc_encoder(&p_Enc);

  Configure (p_Enc->p_Vid, p_Enc->p_Inp, argc, argv);

  // init encoder
  init_encoder(p_Enc->p_Vid, p_Enc->p_Inp);

  // encode sequence
  encode_sequence(p_Enc->p_Vid, p_Enc->p_Inp);

  // terminate sequence
  free_encoder_memory(p_Enc->p_Vid, p_Enc->p_Inp);

  free_params (p_Enc->p_Inp);  
  free_encoder(p_Enc);

  return 0;
}

static void init_encoder(VideoParameters *p_Vid, InputParameters *p_Inp)
{
  p_Vid->p_Inp = p_Inp;

  //set coding layer number;
  p_Vid->num_of_layers = p_Inp->num_of_views;

  // Open Files
  OpenFiles(&p_Inp->input_file1);

  information_init(p_Vid, p_Inp, p_Vid->p_Stats);
}

static void encode_sequence(VideoParameters *p_Vid, InputParameters *p_Inp)
{
}

void free_encoder_memory(VideoParameters *p_Vid, InputParameters *p_Inp)
{

}

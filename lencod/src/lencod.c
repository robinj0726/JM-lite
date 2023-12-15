#include "global.h"
#include "mbuffer.h"

EncoderParams   *p_Enc = NULL;

static void init_encoder        (VideoParameters *p_Vid, InputParameters *p_Inp);
static void encode_sequence     (VideoParameters *p_Vid, InputParameters *p_Inp);

static void alloc_video_params( VideoParameters **p_Vid)
{
  if ((*p_Vid = (VideoParameters *) calloc(1, sizeof(VideoParameters)))==NULL) 
    no_mem_exit("alloc_video_params: p_Vid");
  // if ((((*p_Vid)->p_Dist)  = (DistortionParams *) calloc(1, sizeof(DistortionParams)))==NULL) 
  //   no_mem_exit("alloc_video_params: p_Dist");
  if ((((*p_Vid)->p_Stats) = (StatParameters *) calloc(1, sizeof(StatParameters)))==NULL) 
    no_mem_exit("alloc_video_params: p_Stats");
  if (((*p_Vid)->p_Dpb_layer[0]     = (DecodedPictureBuffer *) calloc(MAX_NUM_DPB_LAYERS, sizeof(DecodedPictureBuffer)))==NULL) 
    no_mem_exit("alloc_video_params: p_Dpb_layer");
  {
    int i;
    for(i=1; i<MAX_NUM_DPB_LAYERS; i++)
    {
      (*p_Vid)->p_Dpb_layer[i] = (*p_Vid)->p_Dpb_layer[i-1] + 1;
      (*p_Vid)->p_Dpb_layer[i]->layer_id = i;
    }
  }
  //if ((((*p_Vid)->p_Quant)  = (QuantParameters *) calloc(1, sizeof(QuantParameters)))==NULL) 
  //  no_mem_exit("alloc_video_params: p_Quant");
  //if ((((*p_Vid)->p_QScale)  = (ScaleParameters *) calloc(1, sizeof(ScaleParameters)))==NULL) 
  //  no_mem_exit("alloc_video_params: p_QScale");
  //if ((((*p_Vid)->p_SEI)  = (SEIParameters *) calloc(1, sizeof(SEIParameters)))==NULL) 
  //  no_mem_exit("alloc_video_params: p_SEI");


  (*p_Vid)->p_dec = -1;
#if (MVC_EXTENSION_ENABLE)
  (*p_Vid)->p_dec2 = -1;
#endif
  (*p_Vid)->p_log = NULL;
  (*p_Vid)->f_annexb = NULL;
  // Init rtp related info
  (*p_Vid)->f_rtp = NULL;
  (*p_Vid)->CurrentRTPTimestamp = 0;         
  (*p_Vid)->CurrentRTPSequenceNumber = 0;
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

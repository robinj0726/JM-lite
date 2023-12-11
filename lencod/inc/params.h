#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "frame.h"
#include "io_video.h"

struct inp_par_enc
{
  int ProfileIDC;                       //!< value of syntax element profile_idc
  int LevelIDC;                         //!< value of syntax element level_idc

  int num_of_views;                     //!< number of views to encode (1=1view, 2=2views)

  VideoDataFile   input_file1;          //!< Input video file1

  unsigned int *top_left;                         //!< top_left and bottom_right store values indicating foregrounds
  unsigned int *bottom_right;
  byte *slice_group_id;                   //!< slice_group_id is for slice group type being 6
  int *run_length_minus1;                //!< run_length_minus1 is for slice group type being 0

  int DisplayEncParams;

};
#endif
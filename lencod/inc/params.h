#ifndef _PARAMS_H_
#define _PARAMS_H_

struct inp_par_enc
{
  int ProfileIDC;                       //!< value of syntax element profile_idc
  int LevelIDC;                         //!< value of syntax element level_idc

  unsigned int *top_left;                         //!< top_left and bottom_right store values indicating foregrounds
  unsigned int *bottom_right;
  byte *slice_group_id;                   //!< slice_group_id is for slice group type being 6
  int *run_length_minus1;                //!< run_length_minus1 is for slice group type being 0

};
#endif
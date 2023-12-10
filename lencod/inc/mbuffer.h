#ifndef _MBUFFERENC_H_
#define _MBUFFERENC_H_

#include "global.h"

typedef struct decoded_picture_buffer
{
  VideoParameters *p_Vid;
  InputParameters *p_Inp;

  int layer_id;

} DecodedPictureBuffer;

#endif
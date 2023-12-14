#ifndef _DEFINES_H_
#define _DEFINES_H_

#define JM                  "19 (FRExt)"
#define VERSION             "19.0"
#define EXT_VERSION         "(FRExt)"

#define MAX_NUM_DPB_LAYERS      2

#define FILE_NAME_SIZE  255

#define ET_SIZE 300      //!< size of error text buffer
#define INIT_FRAME_RATE 30

// Quantization parameter range
#define MIN_QP          0
#define MAX_QP          51
#define SHIFT_QP        12

//  Available MB modes
enum {
  PSKIP        =  0,
  BSKIP_DIRECT =  0,
  P16x16       =  1,
  P16x8        =  2,
  P8x16        =  3,
  SMB8x8       =  4,
  SMB8x4       =  5,
  SMB4x8       =  6,
  SMB4x4       =  7,
  P8x8         =  8,
  I4MB         =  9,
  I16MB        = 10,
  IBLOCK       = 11,
  SI4MB        = 12,
  I8MB         = 13,
  IPCM         = 14,
  MAXMODE      = 15
} MBModeTypes;

#endif
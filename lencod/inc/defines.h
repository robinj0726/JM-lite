#ifndef _DEFINES_H_
#define _DEFINES_H_

#define JM                  "19 (FRExt)"
#define VERSION             "19.0"
#define EXT_VERSION         "(FRExt)"

#define IMGTYPE                   1    //!< Define imgpel size type. 0 implies byte (cannot handle >8 bit depths) and 1 implies unsigned short

//AVC Profile IDC definitions
enum {
  NO_PROFILE     =  0,       //!< disable profile checking for experimental coding (enables FRExt, but disables MV)
  FREXT_CAVLC444 = 44,       //!< YUV 4:4:4/14 "CAVLC 4:4:4"
  BASELINE       = 66,       //!< YUV 4:2:0/8  "Baseline"
  MAIN           = 77,       //!< YUV 4:2:0/8  "Main"
  EXTENDED       = 88,       //!< YUV 4:2:0/8  "Extended"
  FREXT_HP       = 100,      //!< YUV 4:2:0/8  "High"
  FREXT_Hi10P    = 110,      //!< YUV 4:2:0/10 "High 10"
  FREXT_Hi422    = 122,      //!< YUV 4:2:2/10 "High 4:2:2"
  FREXT_Hi444    = 244,      //!< YUV 4:4:4/14 "High 4:4:4"
  MULTIVIEW_HIGH = 118,      //!< YUV 4:2:0/8  "Multiview High"
  STEREO_HIGH    = 128       //!< YUV 4:2:0/8  "Stereo High"
} ProfileIDC;

#define MAX_NUM_DPB_LAYERS      2

#define FILE_NAME_SIZE  255

#define ET_SIZE 300      //!< size of error text buffer
#define INIT_FRAME_RATE 30

// Quantization parameter range
#define MIN_QP          0
#define MAX_QP          51
#define SHIFT_QP        12

// Direct Mode types
enum {
  DIR_TEMPORAL = 0, //!< Temporal Direct Mode
  DIR_SPATIAL  = 1 //!< Spatial Direct Mode
} DirectModes;

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
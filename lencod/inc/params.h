#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "types.h"
#include "frame.h"
#include "io_video.h"

struct inp_par_enc
{
  int ProfileIDC;                       //!< value of syntax element profile_idc
  int LevelIDC;                         //!< value of syntax element level_idc
  int IntraProfile;                     //!< Enable Intra profiles

  int no_frames;                        //!< number of frames to be encoded
  int qp[NUM_SLICE_TYPES];              //!< QP values for all slice types
  int qpsp;                             //!< QPSP quantization value
  int search_range[2];                  /*!< search range - integer pel search and 16x16 blocks.  The search window is
                                             generally around the predicted vector. Max vector is 2xmcrange.  */
  int num_ref_frames_org;
  int P_List0_refs_org[2];                  //!< number of reference picture in list 0 in P pictures
  int B_List0_refs_org[2];                  //!< number of reference picture in list 0 in B pictures
  int B_List1_refs_org[2];                  //!< number of reference picture in list 1 in B pictures

  FrameFormat source;                   //!< source related information
  FrameFormat output;                   //!< output related information
  int yuv_format;                       //!< YUV format (0=4:0:0, 1=4:2:0, 2=4:2:2, 3=4:4:4)
  int intra_upd;                        /*!< For error robustness. 0: no special action. 1: One GOB/frame is intra coded
                                             as regular 'update'. 2: One GOB every 2 frames is intra coded etc.
                                             In connection with this intra update, restrictions is put on motion vectors
                                             to prevent errors to propagate from the past                                */

  int num_of_views;                     //!< number of views to encode (1=1view, 2=2views)

  VideoDataFile   input_file1;          //!< Input video file1
  char outfile       [FILE_NAME_SIZE];  //!< H.264 compressed output bitstream
  char ReconFile     [FILE_NAME_SIZE];  //!< Reconstructed Pictures (view 0 for MVC profile)
  char ReconFile2    [FILE_NAME_SIZE];  //!< Reconstructed Pictures (view 1)
  char TraceFile     [FILE_NAME_SIZE];  //!< Trace Outputs
  char StatsFile     [FILE_NAME_SIZE];  //!< Stats File

  int idr_period;                       //!< IDR picture period
  int intra_period;                     //!< intra picture period

  // B pictures
  int qpBRSOffset;                      //!< QP for reference B slice coded pictures

  // SP/SI Pictures
  int sp_periodicity;                   //!< The periodicity of SP-pictures

  int BRefPictures;                  //!< B coded reference pictures replace P pictures (0: not used, 1: used)
  int HierarchicalCoding;

  int symbol_mode;                   //!< Specifies the mode the symbols are mapped on bits
  int of_mode;                       //!< Specifies the mode of the output file
  int partition_mode;                //!< Specifies the mode of data partitioning

  int full_search;

  int rdopt;
  int Distortion[TOTAL_DIST_TYPES];

  unsigned int *top_left;                         //!< top_left and bottom_right store values indicating foregrounds
  unsigned int *bottom_right;
  byte *slice_group_id;                   //!< slice_group_id is for slice group type being 6
  int *run_length_minus1;                //!< run_length_minus1 is for slice group type being 0

  int DisplayEncParams;
  int Verbose;

  int PicInterlace;           //!< picture adaptive frame/field
  int MbInterlace;            //!< macroblock adaptive frame/field
  int IntraBottom;            //!< Force Intra Bottom at GOP periods.

  int OnTheFlyFractMCP;         //!< On the fly interpolation mode

  // Chroma interpolation and buffering
  int ChromaMEEnable;
  int MEErrorMetric[3];
  int ModeDecisionMetric;

  int Transform8x8Mode;

  // Search Algorithm
  SearchType SearchMode[2];

  // EPZS related parameters
  int EPZSPattern;
  int EPZSDual;
  int EPZSFixed;
  int EPZSAggressiveWindow;
#if (MVC_EXTENSION_ENABLE)
  int EPZSTemporal[2];
#else
  int EPZSTemporal;  
#endif
  int EPZSSpatialMem;
  int EPZSBlockType;
#if (MVC_EXTENSION_ENABLE)
  int EnableEnhLayerEPZSScalers;
  int EPZSMinThresScale[2];
  int EPZSMaxThresScale[2];
  int EPZSMedThresScale[2];
  int EPZSSubPelThresScale[2];
#else
  int EPZSMinThresScale;
  int EPZSMaxThresScale;
  int EPZSMedThresScale;
  int EPZSSubPelThresScale;
#endif
  int EPZSSubPelME;
  int EPZSSubPelMEBiPred;

};
#endif
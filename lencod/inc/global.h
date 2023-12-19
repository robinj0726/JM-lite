#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "defines.h"
#include "win32.h"
#include "typedefs.h"
#include "params.h"
#include "ifunctions.h"

char errortext[ET_SIZE]; //!< buffer for error message for exit with error()

typedef struct inp_par_enc InputParameters;

typedef struct video_par
{
  InputParameters          *p_Inp;
//   pic_parameter_set_rbsp_t *active_pps;
//   seq_parameter_set_rbsp_t *active_sps;
//   struct sei_params        *p_SEI;
//   struct decoders          *p_decs;
//   CodingParameters         *p_CurrEncodePar;
//   CodingParameters         *p_EncodePar[MAX_NUM_DPB_LAYERS];

//   int number;                  //!< current image number to be encoded (in first layer)  
//   int LevelIndex;              //!< mapped level idc
//   int MaxVmvR[6];              //!< maximum vertical motion vector
//   int MaxHmvR[6];              //!< maximum horizontal motion vector
//   int current_mb_nr;
//   short current_slice_nr;
//   short type;
//   PictureStructure structure;  //!< picture structure
//   int base_dist;
//   int num_ref_frames;          //!< number of reference frames to be used
//   int max_num_references;      //!< maximum number of reference pictures that may occur
//   int masterQP;                //!< Master quantization parameter
//   int qp;                      //!< quant for the current frame
//   int qpsp;                    //!< quant for the prediction frame of SP-frame

//   int prev_frame_no; // POC200301
//   int consecutive_non_reference_pictures; // POC200301

//   // prediction structure
//   int frm_struct_buffer;      //!< length of the frame struct buffer (this may also be a define)
//   int last_idr_code_order;
//   int last_idr_disp_order;
//   int last_mmco_5_code_order; //!< it is a good idea to re-initialize POCs after such a frame: while seemingly not required it is critical for good implicit WP performance (I *THINK*) since POCs are set internally to zero after an MMCO=5 command.
//   int last_mmco_5_disp_order;
//   int curr_frm_idx;           //!< frame we wish to code in coding order (points also to p_frm)
//   int FrameNumOffset;         //!< POC type 1
//   int prevFrameNumOffset;     //!< POC type 1
//   unsigned int prevFrameNum;  //!< POC type 1
//   SeqStructure    *p_pred;
//   FrameUnitStruct *p_curr_frm_struct;
//   PicStructure    *p_curr_pic;
//   SliceStructure  *p_curr_slice;
//   int pic_struct;
//   struct search_window searchRange;
  
//   //Hierarchical Motion Estimation structure
//   struct hme_info *pHMEInfo;  //!< HME information
//   int    is_hme;
 
//   ImageData imgData;           //!< Image data to be encoded
//   ImageData imgData0;          //!< Input Image Data
//   ImageData imgData1;
//   ImageData imgData2;
//   ImageData imgData3;
//   // Data needed for 3:2 pulldown or temporal interleaving
//   ImageData imgData32;           //!< Image data to be encoded
//   ImageData imgData4;
//   ImageData imgData5;
//   ImageData imgData6;
//   ImageData imgRefData;
//   ImageData origData0;
//   ImageData origData1;

//   ImageData imgDataOpt1;
//   ImageData imgDataOpt2;


//   int   num_slices_wp;
//   int   wp_parameters_set; 
//   short ****wp_weights;   // explicit WP weights
//   short ****wp_offsets;   // explicit WP offsets
//   short *****wbp_weight;  // implicit WP weights

//   struct image_structure imgSRC;
//   struct image_structure imgREF;
//   struct image_structure imgREF0;
//   struct image_structure imgREF1;
//   struct image_structure imgRGB_src;
//   struct image_structure imgRGB_ref;
//   int       **imgY_sub_tmp;           //!< Y picture temporary component (Quarter pel)
//   imgpel    **imgY_com;               //!< Encoded luma images
//   imgpel   **imgUV_com[2];              //!< Encoded croma images

//   imgpel    **imgY_com_buf[2];               //!< Encoded luma images
//   imgpel   **imgUV_com_buf[2][2];              //!< Encoded croma images

//   imgpel    **pCurImg;                //!< Reference image. Luma for other profiles, can be any component for 4:4:4
//   // global picture format dependend buffers, mem allocation in image.c
//   imgpel    **pImgOrg[MAX_PLANE];

//   imgpel    **pCurImgRef;
//   imgpel    **pImgOrgRef[MAX_PLANE];

//   Picture *p_frame_pic;
//   Picture **frame_pic;
// #if (MVC_EXTENSION_ENABLE)
//   Picture **field_pic_ptr;
//   Picture **field_pic1;
//   Picture **field_pic2;
// #else
//   Picture **field_pic;
// #endif

//   Picture *frame_pic_si;

//   byte *MapUnitToSliceGroupMap;

//   byte *buf;
//   byte *ibuf;

// #ifdef _LEAKYBUCKET_
//   long *Bit_Buffer;
//   unsigned long total_frame_buffer;
// #endif

//   unsigned int log2_max_frame_num_minus4;
//   unsigned int log2_max_pic_order_cnt_lsb_minus4;
//   unsigned int max_frame_num;
//   unsigned int max_pic_order_cnt_lsb;

//   int64  me_tot_time;
//   int64  tot_time;
//   int64  me_time;

//   byte mixedModeEdgeFlag;

//   int *RefreshPattern;
//   int *IntraMBs;
//   int WalkAround;
//   int NumberOfMBs;
//   int NumberIntraPerPicture;

//   short start_me_refinement_hp; //!< if set then recheck the center position when doing half-pel motion refinement
//   short start_me_refinement_qp; //!< if set then recheck the center position when doing quarter-pel motion refinement

//   // Motion Estimation
//   struct umhex_struct *p_UMHex;
//   struct umhex_smp_struct *p_UMHexSMP;
//   struct me_full_fast *p_ffast_me;

//   struct search_window *p_search_window;

//   // EPZS
//   struct epzs_struct *sdiamond;
//   struct epzs_struct *square;
//   struct epzs_struct *ediamond;
//   struct epzs_struct *ldiamond;
//   struct epzs_struct *sbdiamond;
//   struct epzs_struct *pmvfast;
//   struct epzs_struct *search_rpu_square;
//   struct epzs_struct *SP_M2DRPU;
//   struct epzs_struct *SP_M2DRPU4MM;

//   // RDOQ
//   int precalcUnaryLevelTab[128][MAX_PREC_COEFF];
//   int AdaptRndWeight;
//   int AdaptRndCrWeight;


//   //////////////////////////////////////////////////////////////////////////
//   // B pictures
//   // motion vector : forward, backward, direct
//   byte  MBPairIsField;     //!< For MB level field/frame coding tools

//   // Buffers for rd optimization with packet losses, Dim. Kontopodis
//   byte **pixel_map;   //!< Shows the latest reference frame that is reliable for each pixel
//   byte **refresh_map; //!< Stores the new values for pixel_map
//   int intras;         //!< Counts the intra updates in each frame.
//   int iInterViewMBs;  
//   int RCMinQP;
//   int RCMaxQP;

//   float framerate;

//   int is_v_block;
//   int mb_y_upd;
//   int mb_y_intra;              //!< which GOB to intra code
//   char **ipredmode;            //!< intra prediction mode
//   char **ipredmode8x8;         //!< help storage for 8x8 modes, inserted by YV
//   //fast intra prediction;
//   char **ipredmode4x4_line;     //!< intra prediction mode
//   char **ipredmode8x8_line;     //!< help storage for 8x8 modes, inserted by YV

//   int cod_counter;             //!< Current count of number of skipped macroblocks in a row
//   int ***nz_coeff;             //!< number of coefficients per block (CAVLC)
//   int ***nz_coeff_buf[2];
//   int pix_x;                   //!< current pixel horizontal
//   int pix_y;                   //!< current pixel vertical


//   imgpel min_IPCM_value;
//   // Cabac related parameters (we can put these in a structure)
//   int pic_bin_count;

//   // Adaptive rounding
//   int ****ARCofAdj4x4;         //!< Transform coefficients for 4x4 luma/chroma. 
//   int ****ARCofAdj8x8;         //!< Transform coefficients for 4x4 luma/chroma. 

//   ImageData tempData1, tempData2, tempData3, tempData4;
//   imgpel **tempImg;

//   Picture       *currentPicture; //!< The coded picture currently in the works (typically p_frame_pic, p_Vid->field_pic[0], or p_Vid->field_pic[1])
//   struct slice  *currentSlice;                                //!< pointer to current Slice data struct
//   Macroblock    *mb_data;                                   //!< array containing all MBs of a whole frame
//   Block8x8Info  *b8x8info;                                  //!< block 8x8 information for RDopt

//   //FAST_REFPIC_DECISION
//   int           mb_refpic_used; //<! [2][16] for fast reference decision;
//   int           parent_part_refpic_used; //<! [2][16] for fast reference decision;
//   int           submb_parent_part_refpic_used;//<! [2][16] for fast reference decision;
//   //end;
//   short   *intra_block;

//   int frame_no;
//   int fld_type;                        //!< top or bottom field
//   byte fld_flag;
//   unsigned int rd_pass;

//   int  redundant_coding;
//   int  key_frame;
//   int  redundant_ref_idx;
//   int  frm_no_in_file;

//   char DFDisableIdc;
//   char DFAlphaC0Offset;
//   char DFBetaOffset;

//   char direct_spatial_mv_pred_flag;              //!< Direct Mode type to be used (0: Temporal, 1: Spatial)

//   int shift_cr_x2;

//   int num_ref_idx_l0_active;
//   int num_ref_idx_l1_active;

//   Boolean field_mode;     //!< For MB level field/frame -- field mode on flag
//   Boolean top_field;      //!< For MB level field/frame -- top field flag

//   int layer;              //!< which layer this picture belonged to

//   int AdaptiveRounding;   //!< Adaptive Rounding parameter based on JVT-N011

//   int redundant_pic_cnt;

//   Boolean mb_aff_frame_flag;    //!< indicates frame with mb aff coding

//   //the following should probably go in sequence parameters
//   unsigned int pic_order_cnt_type;

//   // for poc mode 1
//   Boolean      delta_pic_order_always_zero_flag;
//   int          offset_for_non_ref_pic;
//   int          offset_for_top_to_bottom_field;
//   unsigned int num_ref_frames_in_pic_order_cnt_cycle;
//   int          offset_for_ref_frame[1];

//   //the following is for slice header syntax elements of poc
//   // for poc mode 0.
//   unsigned int pic_order_cnt_lsb;
//   int          delta_pic_order_cnt_bottom;
//   // for poc mode 1.
//   int          delta_pic_order_cnt[2];

//   int          frm_iter;   //!< frame variations to create (useful for multiple coding passes)

//   unsigned int field_picture;
//   signed int toppoc;       //!< poc for this frame or field
//   signed int bottompoc;    //!< for completeness - poc of bottom field of a frame (always = poc+1)
//   signed int framepoc;     //!< min (toppoc, bottompoc)
//   signed int ThisPOC;      //!< current picture POC
//   unsigned int frame_num;    //!< frame_num for this frame

//   unsigned int PicSizeInMbs;

//   //the following should probably go in picture parameters
//   Boolean bottom_field_pic_order_in_frame_present_flag; // ????????

//   //the following are sent in the slice header
//   //  int delta_pic_order_cnt[2];
//   int nal_reference_idc;

//   int     adaptive_ref_pic_buffering_flag;
//   int     no_output_of_prior_pics_flag;
//   Boolean long_term_reference_flag;

//   DecRefPicMarking_t *dec_ref_pic_marking_buffer;
//   int* mvbits;

//   int     max_mvd;  //for MVD overflow checking;
//   int*    refbits;

//   // rate control variables
//   int NumberofCodedMacroBlocks;
//   int BasicUnitQP;
//   int NumberofMBTextureBits;
//   int NumberofMBHeaderBits;
//   unsigned int BasicUnit;
//   byte write_macroblock;
//   byte bot_MB;
//   int write_mbaff_frame;

//   int last_pic_bottom_field;
//   int last_has_mmco_5;
//   int pre_frame_num;

//   int slice_group_change_cycle;

//   int max_qp_delta;
//   int min_qp_delta;

//   // Lagrangian Parameters
//   LambdaParams **lambda;  
//   double  **lambda_md;     //!< Mode decision Lambda
//   double ***lambda_me;     //!< Motion Estimation Lambda
//   int    ***lambda_mf;     //!< Integer formatted Motion Estimation Lambda
//   double  **lambda_rdoq;   //!< RDOQ Lambda
//   double **lambda_mf_factor; //!< Motion Estimation Lamda Scale Factor

//   LambdaParams **lambda_buf[2];  
//   double  **lambda_md_buf[2];     //!< Mode decision Lambda
//   double ***lambda_me_buf[2];     //!< Motion Estimation Lambda
//   int    ***lambda_mf_buf[2];     //!< Integer formatted Motion Estimation Lambda
//   double  **lambda_rdoq_buf[2];   //!< RDOQ Lambda
//   double **lambda_mf_factor_buf[2]; //!< Motion Estimation Lamda Scale Factor

//   uint32 dc_pred_value;                 //!< DC prediction value for current component
//   short max_imgpel_value;              //!< max value that one picture element (pixel) can take (depends on pic_unit_bitdepth)

//   struct edge_info *p_edge;

//   int chroma_qp_offset[2];      //!< offset for qp for chroma [0-Cb, 1-Cr]

//   int auto_crop_right;
//   int auto_crop_bottom;

//   short checkref;
//   int last_valid_reference;
//   int bytes_in_picture;

//   int64 last_bit_ctr_n;

//   int AverageFrameQP;
//   int SumFrameQP;

//   int ChromaArrayType;
//   Macroblock    *mb_data_JV[MAX_PLANE];  //!< mb_data to be used during 4:4:4 independent mode encoding
//   char colour_plane_id;    //!< colour_plane_id of the current coded slice (valid only when separate_colour_plane_flag is 1)

//   int lastIntraNumber;
//   int lastINTRA;
//   int last_ref_idc;
//   int idr_refresh;

  int p_dec;                      //!< decoded image file handle
#if (MVC_EXTENSION_ENABLE)
  int p_dec2;                     //!< decoded image file handle for view 1
#endif
//   int frame_statistic_start;
//   int initial_Bframes;
//   int cabac_encoding;

//   unsigned int primary_pic_type;

//   int frameOffsetTotal[2][MAX_REFERENCE_PICTURES]; 
//   int frameOffsetCount[2][MAX_REFERENCE_PICTURES]; 
//   short frameOffset[2][MAX_REFERENCE_PICTURES];
//   int frameOffsetAvail;
//   int view_id;
// #if (MVC_EXTENSION_ENABLE)
//   int sec_view_force_fld;    //!< if view 0 is coded as FLD then force also view to be coded as FLD as well
//   int prev_view_is_anchor;

//   int temp0_nal_reference_idc;
//   int temp0_non_idr_flag[2];
//   int temp0_priority_id;
//   int temp0_view_id;
//   int temp0_temporal_id;
//   int temp0_anchor_pic_flag[2];
//   int temp0_inter_view_flag[2];

//   int non_idr_flag[2];
//   int priority_id;
//   int temporal_id;
//   int anchor_pic_flag[2];
//   int inter_view_flag[2];

//   PrevCodingStats prev_cs;
//   int MVCInterViewReorder;
//   struct storable_picture *proc_picture;
// #endif

//   double *mb16x16_cost_frame;
//   double mb16x16_cost;

//   int **lrec;
//   int ***lrec_uv;
//   Boolean sp2_frame_indicator;
//   int number_sp2_frames;

//   Boolean giRDOpt_B8OnlyFlag;

//   int  frameNuminGOP;
//   // Redundant picture
//   imgpel **imgY_tmp;
//   imgpel **imgUV_tmp[2];
//   imgpel **imgY_tmp_buf[2];
//   imgpel **imgUV_tmp_buf[2][2];

//   // RDOQ related parameters
//   //int Intra_Selected; 

//   int CbCr_predmode_8x8[4]; 
//   distblk ****motion_cost;
//   int*** initialized;
//   int*** modelNumber;
//   int    bipred_enabled[MAXMODE];


//   int num_mb_per_slice;
//   int number_of_slices;

//   int  imgpel_abs_range;
// #if (JM_MEM_DISTORTION)
//   int* imgpel_abs;
//   int* imgpel_quad;
// #endif

//   GOP_DATA *gop_structure;
//   byte *MBAmap;
//   unsigned int PicSizeInMapUnits;
//   int FirstMBInSlice[MAXSLICEGROUPIDS];

//   MotionVector* spiral_search;
//   MotionVector* spiral_hpel_search;
//   MotionVector* spiral_qpel_search;

//   // files
  FILE *p_log;                     //!< SNR file

  // generic output file
  FILE **f_out;
  // ANNEX B output file
  FILE *f_annexb; 
  // RTP output file
  FILE *f_rtp;
  int CurrentRTPTimestamp;             //!< The RTP timestamp of the current packet,
  //! incremented with all P and I frames
  uint16 CurrentRTPSequenceNumber;     //!< The RTP sequence number of the current packet
  //!< incremented by one for each sent packet

//   // This should be the right location for this
//   //struct storable_picture **listX[6];
//   //char listXsize[6];  

//   DistortionParams *p_Dist;
  struct stat_parameters  *p_Stats;
//   pic_parameter_set_rbsp_t *PicParSet[MAXPPS];
//   //struct decoded_picture_buffer *p_Dpb;
  struct decoded_picture_buffer *p_Dpb_layer[MAX_NUM_DPB_LAYERS];
//   struct frame_store            *out_buffer;
//   struct storable_picture       *enc_picture;
//   struct storable_picture       **enc_frame_picture;
//   struct storable_picture       **enc_field_picture;
//   struct storable_picture       *enc_frame_picture_JV[MAX_PLANE];  //!< enc_frame to be used during 4:4:4 independent mode encoding
//   struct quant_params           *p_Quant;
//   struct scaling_list           *p_QScale;

//   // rate control
//   RCGeneric   *p_rc_gen;
//   RCGeneric   *p_rc_gen_init, *p_rc_gen_best;
//   RCQuadratic *p_rc_quad;
//   RCQuadratic *p_rc_quad_init, *p_rc_quad_best;

//   double entropy[128];
//   double enorm  [128];
//   double probability[128];


//   FILE       *expSFile;
//   struct exp_seq_info *expSeq;
//   // Weighted prediction
//   struct wpx_object   *pWPX;

//   // Wavelet PSNR
//   int ***wavREF[NUM_WAVELET_LEVEL+1];
//   int ***wavSRC[NUM_WAVELET_LEVEL+1];
//   double JND[NUM_WAVELET_LEVEL][4];
//   int *temp_low, *temp_high;

// #ifdef BEST_NZ_COEFF
//   int gaaiMBAFF_NZCoeff[4][12];
// #endif


//   int offset_y, offset_cr;
//   int wka0, wka1, wka2, wka3, wka4;
//   int EvaluateDBOff;
//   int TurnDBOff;
//   // Note that these function pointers definitely affect now parallelization since they are only
//   // allocated once. We need to add such info at maybe within picture information or at a lower level
//   // RC
//   int  (*updateQP)                (struct video_par *p_Vid, InputParameters *p_Inp, RCQuadratic *p_quad, RCGeneric *p_gen, int topfield);
//   void (*rc_update_pict_frame_ptr)(struct video_par *p_Vid, InputParameters *p_Inp, RCQuadratic *p_quad, RCGeneric *p_gen, int nbits);
//   void (*rc_update_picture_ptr)   (struct video_par *p_Vid, InputParameters *p_Inp, int bits);
//   void (*rc_init_pict_ptr)        (struct video_par *p_Vid, InputParameters *p_Inp, RCQuadratic *p_quad, RCGeneric *p_gen, int fieldpic, int topfield, int targetcomputation, float mult);
  
//   //Various
//   void (*buf2img)              (imgpel** imgX, unsigned char* buf, int size_x, int size_y, int o_size_x, int o_size_y, int symbol_size_in_bytes, int bitshift);
//   void (*getNeighbour)         (Macroblock *currMB, int xN, int yN, int mb_size[2], PixelPos *pix);
//   void (*get_mb_block_pos)     (BlockPos *PicPos, int mb_addr, short *x, short *y);
//   int  (*WriteNALU)            (struct video_par *p_Vid, NALU_t *n, FILE **f_out);     //! Hides the write function in Annex B or RTP
//   void (*error_conceal_picture)(struct video_par *p_Vid, struct storable_picture *enc_pic, int decoder);
//   distblk (*estimate_distortion)(Macroblock *currMB, int block, int block_size, short mode, short pdir, distblk min_rdcost);
//   // function pointer for different ways of obtaining chroma interpolation
//   void (*OneComponentChromaPrediction4x4)   (Macroblock *currMB, imgpel* , int , int , MotionVector ** , struct storable_picture *listX, int );
  
//   // deblocking
//   void (*GetStrengthVer)    (byte Strength[16], Macroblock *MbQ, int edge, int mvlimit);
//   void (*GetStrengthHor)    (byte Strength[16], Macroblock *MbQ, int edge, int mvlimit);
//   void (*EdgeLoopLumaHor)   (ColorPlane pl, imgpel** Img, byte Strength[16], Macroblock *MbQ, int edge, int width);
//   void (*EdgeLoopLumaVer)   (ColorPlane pl, imgpel** Img, byte Strength[16], Macroblock *MbQ, int edge);
//   void (*EdgeLoopChromaVer)(imgpel** Img, byte Strength[16], Macroblock *MbQ, int edge, int uv);
//   void (*EdgeLoopChromaHor)(imgpel** Img, byte Strength[16], Macroblock *MbQ, int edge, int width, int uv);

//   // We should move these at the slice level at some point.
//   void (*EstimateWPBSlice) (struct slice *currSlice);
//   void (*EstimateWPPSlice) (struct slice *currSlice, int offset);
//   int  (*TestWPPSlice)     (struct slice *currSlice, int offset);
//   int  (*TestWPBSlice)     (struct slice *currSlice, int method);
//   distblk  (*distortion4x4)(short*, distblk);
//   distblk  (*distortion8x8)(short*, distblk);

//   // ME distortion Function pointers. We need to move this to the MB or slice level
//   distblk (*computeUniPred[6])   (struct storable_picture *ref1, struct me_block *, distblk , MotionVector * );
//   distblk (*computeBiPred1[3])   (struct storable_picture *ref1, struct storable_picture *ref2, struct me_block*, distblk , MotionVector *, MotionVector *);
//   distblk (*computeBiPred2[3])   (struct storable_picture *ref1, struct storable_picture *ref2, struct me_block*, distblk , MotionVector *, MotionVector *);

//   seq_parameter_set_rbsp_t *sps[MAX_NUM_DPB_LAYERS];
//   FrameFormat output_format[MAX_NUM_DPB_LAYERS];
  int num_of_layers; 
//   int dpb_layer_id;

//   BlockPos *PicPos;

//   //deprecative varialbes, they will be removed in future, so donot add varaibles here;
  ColorFormat yuv_format;
//   int P444_joined;
//   short bitdepth_luma;
//   short bitdepth_chroma;
//   int bitdepth_scale[2];
//   int bitdepth_luma_qp_scale;
//   int bitdepth_chroma_qp_scale;
//   int bitdepth_lambda_scale;
//   uint32 dc_pred_value_comp[MAX_PLANE]; //!< component value for DC prediction (depends on component pel bit depth)
//   int max_pel_value_comp      [MAX_PLANE];       //!< max value that one picture element (pixel) can take (depends on pic_unit_bitdepth)
//   int max_imgpel_value_comp_sq   [MAX_PLANE];       //!< max value that one picture element (pixel) can take (depends on pic_unit_bitdepth)
//   int num_blk8x8_uv;
//   int num_cdc_coeff;
//   short mb_cr_size_x;
//   short mb_cr_size_y;
//   int mb_size[MAX_PLANE][2];
//   int max_bitCount;
  int width;                   //!< Number of pels
//   int width_padded;            //!< Width in pels of padded picture
//   int width_blk;               //!< Number of columns in blocks
//   int width_cr;                //!< Number of pels chroma
  int height;                  //!< Number of lines
//   int height_padded;           //!< Number in lines of padded picture
//   int height_blk;              //!< Number of lines in blocks
//   int height_cr;               //!< Number of lines  chroma
//   int height_cr_frame;         //!< Number of lines  chroma frame
//   int size;                    //!< Luma Picture size in pels
//   int size_cr;                 //!< Chroma Picture size in pels
//   int padded_size_x;  
//   int padded_size_x_m8x8;
//   int padded_size_x_m4x4;
//   int cr_padded_size_x;
//   int cr_padded_size_x_m8;
//   int cr_padded_size_x2;
//   int cr_padded_size_x4;
//   int pad_size_uv_x;
//   int pad_size_uv_y;
//   unsigned char chroma_mask_mv_y;
//   unsigned char chroma_mask_mv_x;
//   int chroma_shift_y, chroma_shift_x;
//   int shift_cr_x, shift_cr_y;

//   unsigned int PicWidthInMbs;
//   unsigned int PicHeightInMapUnits;
//   unsigned int FrameHeightInMbs;
//   unsigned int FrameSizeInMbs;
//   //end;
} VideoParameters;

typedef struct encoder_params
{
  InputParameters   *p_Inp;          //!< Input Parameters
  VideoParameters   *p_Vid;          //!< Image Parameters
  FILE              *p_trace;        //!< Trace file
  int64              bufferSize;     //!< buffer size for tiff reads (not currently supported)
} EncoderParams;

extern void free_encoder_memory        (VideoParameters *p_Vid, InputParameters *p_Inp);

extern void error(char *text, int code);

static inline int is_FREXT_profile(unsigned int profile_idc) 
{
  // we allow all FRExt tools, when no profile is active
  return ( profile_idc==NO_PROFILE || profile_idc==FREXT_HP || profile_idc==FREXT_Hi10P || profile_idc==FREXT_Hi422 || profile_idc==FREXT_Hi444 || profile_idc == FREXT_CAVLC444 );
}


static inline int is_MVC_profile(unsigned int profile_idc)
{
  return ( (0)
#if (MVC_EXTENSION_ENABLE)
  || (profile_idc == MULTIVIEW_HIGH) || (profile_idc == STEREO_HIGH)
#endif
    );
}

// static inline int is_intra(Macroblock *curr_MB)
// {
//   return ((curr_MB)->mb_type==SI4MB || (curr_MB)->mb_type==I4MB || (curr_MB)->mb_type==I16MB || (curr_MB)->mb_type==I8MB || (curr_MB)->mb_type==IPCM);
// }

#endif
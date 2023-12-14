#include "global.h"
#include "enc_statistics.h"

static const char DistortionType[3][20] = {"SAD", "SSE", "Hadamard SAD"};

void information_init ( VideoParameters *p_Vid, InputParameters *p_Inp, StatParameters *p_Stats)
{
  int i;
  static const char yuv_types[4][10] = {"YUV 4:0:0", "YUV 4:2:0", "YUV 4:2:2", "YUV 4:4:4"};
  switch (p_Inp->Verbose)
  {
  case 0:
  case 1:
  default:
    printf("------------------------------- JM %4.4s %7.7s -------------------------------\n", VERSION, EXT_VERSION);
    break;
  case 2:
    printf("--------------------------------------- JM %4.4s %7.7s ----------------------------------------\n", VERSION, EXT_VERSION);
    break;
  case 3:
    printf("------------------------------------------ JM %4.4s %7.7s ------------------------------------------\n", VERSION, EXT_VERSION);
    break;
  }

  fprintf(stdout,  " Input YUV file                    : %s \n", p_Inp->input_file1.fname);
#if (MVC_EXTENSION_ENABLE)
  if(p_Inp->num_of_views==2)
    fprintf(stdout,  " Input YUV file 2                  : %s \n", p_Inp->input_file2.fname);
#endif

  fprintf(stdout,  " Output H.264 bitstream            : %s \n", p_Inp->outfile);
  if (p_Vid->p_dec != -1)
    fprintf(stdout,  " Output YUV file                   : %s \n", p_Inp->ReconFile);
#if (MVC_EXTENSION_ENABLE)
  if(p_Inp->num_of_views==2)
  {
    if (p_Vid->p_dec2 != -1)
      fprintf(stdout,  " Output YUV file 2                 : %s \n", p_Inp->ReconFile2);
  }
#endif
  fprintf(stdout,  " YUV Format                        : %s \n", &yuv_types[p_Vid->yuv_format][0]);//p_Vid->yuv_format==YUV422?"YUV 4:2:2":(p_Vid->yuv_format==YUV444)?"YUV 4:4:4":"YUV 4:2:0");
  fprintf(stdout,  " Frames to be encoded              : %d\n", p_Inp->no_frames);
  if (p_Inp->Verbose != 0)
  {
    fprintf(stdout,  " Freq. for encoded bitstream       : %3.2f\n", p_Inp->output.frame_rate);
    fprintf(stdout,  " PicInterlace / MbInterlace        : %d/%d\n", p_Inp->PicInterlace, p_Inp->MbInterlace);
    fprintf(stdout,  " Transform8x8Mode                  : %d\n", p_Inp->Transform8x8Mode);

    for (i=0; i<3; i++)
    {
      fprintf(stdout," ME Metric for Refinement Level %1d  : %s\n", i, DistortionType[p_Inp->MEErrorMetric[i]]);
    }
    fprintf(stdout,  " Mode Decision Metric              : %s\n", DistortionType[p_Inp->ModeDecisionMetric]);

    if( p_Inp->OnTheFlyFractMCP )
    {
      fprintf(stdout," On-the-fly interpolation mode     : OTF_L%d\n", p_Inp->OnTheFlyFractMCP );
    }

    switch ( p_Inp->ChromaMEEnable )
    {
    case 1:
      fprintf(stdout," Motion Estimation for components  : YCbCr\n");
      break;
    default:
      fprintf(stdout," Motion Estimation for components  : Y\n");
      break;
    }

    fprintf(stdout,  " Image format                      : %dx%d (%dx%d)\n", p_Inp->output.width[0], p_Inp->output.height[0], p_Vid->width,p_Vid->height);

    if (p_Inp->intra_upd)
      fprintf(stdout," Error robustness                  : On\n");
    else
      fprintf(stdout," Error robustness                  : Off\n");
    fprintf(stdout,  " Search range                      : %d\n", p_Inp->search_range[0]);
#if (MVC_EXTENSION_ENABLE)
    if ( p_Inp->SepViewInterSearch )
    {
      fprintf(stdout,  " Search range (view 1)             : %d\n", p_Inp->search_range[1]);
    }
#endif

    fprintf(stdout,  " Total number of references        : %d\n", p_Inp->num_ref_frames_org);
    fprintf(stdout,  " References for P slices           : %d\n", p_Inp->P_List0_refs_org[0] ? p_Inp->P_List0_refs_org[0] : p_Inp->num_ref_frames_org);
    fprintf(stdout,  " References for B slices (L0, L1)  : %d, %d\n", 
      p_Inp->B_List0_refs_org[0] ? p_Inp->B_List0_refs_org[0] : p_Inp->num_ref_frames_org, 
      p_Inp->B_List1_refs_org[0] ? p_Inp->B_List1_refs_org[0] : p_Inp->num_ref_frames_org);

    if ( p_Vid->num_of_layers > 1 )
    {
      fprintf(stdout,  " View 1 refs for P slices          : %d\n", p_Inp->P_List0_refs_org[1] ? p_Inp->P_List0_refs_org[1] : p_Inp->num_ref_frames_org);
      fprintf(stdout,  " View 1 refs for B slices (L0, L1) : %d, %d\n", 
        p_Inp->B_List0_refs_org[1] ? p_Inp->B_List0_refs_org[1] : p_Inp->num_ref_frames_org, 
        p_Inp->B_List1_refs_org[1] ? p_Inp->B_List1_refs_org[1] : p_Inp->num_ref_frames_org);
    }

    // Sequence Type
    fprintf(stdout,  " Sequence type                     :");
    if (p_Stats->NumberBFrames > 0 && p_Inp->HierarchicalCoding)
    {
      fprintf(stdout, " Hierarchy (QP: I %d, P %d, B %d) \n",
        p_Inp->qp[I_SLICE], p_Inp->qp[P_SLICE], p_Inp->qp[B_SLICE]);
    }
    else if (p_Stats->NumberBFrames > 0)
    {
      char seqtype[80];
      int i,j;

      strcpy (seqtype,"I");

      for (j=0; j < 2; j++)
      {
        for (i=0; i < p_Stats->NumberBFrames; i++)
        {
          if (p_Inp->BRefPictures)
            strncat(seqtype,"-RB", imax(0, (int) (79 - strlen(seqtype))));
          else
            strncat(seqtype,"-B", imax(0, (int) (79 - strlen(seqtype))));
        }
        strncat(seqtype,"-P", imax(0, (int) (79 - strlen(seqtype))));
      }
      if (p_Inp->BRefPictures)
        fprintf(stdout, " %s (QP: I %d, P %d, RB %d) \n", seqtype, p_Inp->qp[I_SLICE], p_Inp->qp[P_SLICE], iClip3(0, 51, p_Inp->qp[B_SLICE] + p_Inp->qpBRSOffset));
      else
        fprintf(stdout, " %s (QP: I %d, P %d, B %d) \n", seqtype, p_Inp->qp[I_SLICE], p_Inp->qp[P_SLICE], p_Inp->qp[B_SLICE]);
    }
    else if (p_Stats->NumberBFrames == 0 && (p_Inp->intra_period == 1 || p_Inp->idr_period == 1)) 
      fprintf(stdout, " IIII (QP: I %d) \n", p_Inp->qp[I_SLICE]);
    else if (p_Stats->NumberBFrames == 0 && p_Inp->sp_periodicity == 0) 
      fprintf(stdout, " IPPP (QP: I %d, P %d) \n", p_Inp->qp[I_SLICE], p_Inp->qp[P_SLICE]);
    else 
      fprintf(stdout, " I-P-P-SP-P (QP: I %d, P %d, SP (%d, %d)) \n",  p_Inp->qp[I_SLICE], p_Inp->qp[P_SLICE], p_Inp->qp[SP_SLICE], p_Inp->qpsp);

    // report on entropy coding  method
    if (p_Inp->symbol_mode == CAVLC)
      fprintf(stdout," Entropy coding method             : CAVLC\n");
    else
      fprintf(stdout," Entropy coding method             : CABAC\n");

    fprintf(stdout,  " Profile/Level IDC                 : (%d,%d)\n", p_Inp->ProfileIDC, p_Inp->LevelIDC);

    if (p_Inp->SearchMode[0] == UM_HEX)
      fprintf(stdout,  " Motion Estimation Scheme          : HEX\n");
    else if (p_Inp->SearchMode[0] == UM_HEX_SIMPLE)
      fprintf(stdout,  " Motion Estimation Scheme          : SHEX\n");
    else if (p_Inp->SearchMode[0] == EPZS)
    {
      fprintf(stdout,  " Motion Estimation Scheme          : EPZS\n");
      // EPZSOutputStats(p_Inp, stdout, 0);
    }
    else if (p_Inp->SearchMode[0] == FAST_FULL_SEARCH)
      fprintf(stdout,  " Motion Estimation Scheme          : Fast Full Search\n");
    else
      fprintf(stdout,  " Motion Estimation Scheme          : Full Search\n");

#if (MVC_EXTENSION_ENABLE)
    if ( p_Inp->SepViewInterSearch )
    {
      if (p_Inp->SearchMode[1] == UM_HEX)
        fprintf(stdout,  " Motion Estimation Scheme          : HEX\n");
      else if (p_Inp->SearchMode[1] == UM_HEX_SIMPLE)
        fprintf(stdout,  " Motion Estimation Scheme          : SHEX\n");
      else if (p_Inp->SearchMode[1] == EPZS)
      {
        fprintf(stdout,  " Motion Estimation Scheme          : EPZS\n");
        EPZSOutputStats(p_Inp, stdout, 0);
      }
      else if (p_Inp->SearchMode[1] == FAST_FULL_SEARCH)
        fprintf(stdout,  " Motion Estimation Scheme          : Fast Full Search\n");
      else
        fprintf(stdout,  " Motion Estimation Scheme          : Full Search\n");
    }
#endif

    if (p_Inp->full_search == 2)
      fprintf(stdout," Search range restrictions         : none\n");
    else if (p_Inp->full_search == 1)
      fprintf(stdout," Search range restrictions         : older reference frames\n");
    else
      fprintf(stdout," Search range restrictions         : smaller blocks and older reference frames\n");

    if (p_Inp->rdopt)
      fprintf(stdout," RD-optimized mode decision        : used\n");
    else
      fprintf(stdout," RD-optimized mode decision        : not used\n");

    switch(p_Inp->partition_mode)
    {
    case PAR_DP_1:
      fprintf(stdout," Data Partitioning Mode            : 1 partition \n");
      break;
    case PAR_DP_3:
      fprintf(stdout," Data Partitioning Mode            : 3 partitions \n");
      break;
    default:
      fprintf(stdout," Data Partitioning Mode            : not supported\n");
      break;
    }

    switch(p_Inp->of_mode)
    {
    case PAR_OF_ANNEXB:
      fprintf(stdout," Output File Format                : H.264/AVC Annex B Byte Stream Format \n");
      break;
    case PAR_OF_RTP:
      fprintf(stdout," Output File Format                : RTP Packet File Format \n");
      break;
    default:
      fprintf(stdout," Output File Format                : not supported\n");
      break;
    }
  }


  switch (p_Inp->Verbose)
  {
  case 0:
  default:
    printf("-------------------------------------------------------------------------------\n");
    printf("\nEncoding. Please Wait.\n\n");
    break;    
  case 1:
#if (MVC_EXTENSION_ENABLE)
    if (p_Inp->num_of_views == 2)
    {
      printf("------------------------------------------------------------------------------------\n");
      printf("Frame     View Bit/pic    QP   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld Ref  \n");
      printf("------------------------------------------------------------------------------------\n");
    }
    else
#endif
    {
    printf("-------------------------------------------------------------------------------\n");
    printf("Frame     Bit/pic    QP   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld Ref  \n");
    printf("-------------------------------------------------------------------------------\n");
    }
    break;
  case 2:
#if (MVC_EXTENSION_ENABLE)
    if (p_Inp->num_of_views == 2)
    {
      if (p_Inp->Distortion[SSIM] == 1)
      {
        printf("----------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Frame     View Bit/pic WP QP   QL   SnrY    SnrU    SnrV   SsimY   SsimU   SsimV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
        printf("----------------------------------------------------------------------------------------------------------------------------------\n");
      }
      else
      {
        printf("---------------------------------------------------------------------------------------------------------\n");
        printf("Frame     View Bit/pic WP QP   QL   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
        printf("---------------------------------------------------------------------------------------------------------\n");
      }
    }
    else
#endif
    {
    if (p_Inp->Distortion[SSIM] == 1)
    {
      printf("---------------------------------------------------------------------------------------------------------------------------\n");
      printf("Frame     Bit/pic WP QP   QL   SnrY    SnrU    SnrV   SsimY   SsimU   SsimV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
      printf("---------------------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
      printf("---------------------------------------------------------------------------------------------------\n");
      printf("Frame     Bit/pic WP QP   QL   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
      printf("---------------------------------------------------------------------------------------------------\n");
    }
    }
    break;
  case 3:
#if (MVC_EXTENSION_ENABLE)
    if (p_Inp->num_of_views == 2)
    {
      if (p_Inp->Distortion[SSIM] == 1)
      {
        printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Frame      View Bit/pic NVB WP QP   QL   SnrY    SnrU    SnrV   SsimY   SsimU   SsimV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
      }
      else
      {
        printf("---------------------------------------------------------------------------------------------------------------\n");
        printf("Frame      View Bit/pic NVB WP QP   QL   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
      }
    }
    else
#endif
    {
    if (p_Inp->Distortion[SSIM] == 1)
    {
      printf("--------------------------------------------------------------------------------------------------------------------------------\n");
      printf("Frame      Bit/pic NVB WP QP   QL   SnrY    SnrU    SnrV   SsimY   SsimU   SsimV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
      printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
      printf("--------------------------------------------------------------------------------------------------------\n");
      printf("Frame      Bit/pic NVB WP QP   QL   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
      printf("--------------------------------------------------------------------------------------------------------\n");
    }
    }
    break;
  case 4:
#if (MVC_EXTENSION_ENABLE)
    if (p_Inp->num_of_views == 2)
    {
      if (p_Inp->Distortion[SSIM] == 1)
      {
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("Frame     View Bit/pic   Filler NVB  WP QP   QL   SnrY    SnrU    SnrV   SsimY   SsimU   SsimV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
      }
      else
      {
        printf("-------------------------------------------------------------------------------------------------------------------------\n");
        printf("Frame     View Bit/pic   Filler NVB  WP QP   QL   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
        printf("-------------------------------------------------------------------------------------------------------------------------\n");
      }
    }
    else
#endif
    {
    if (p_Inp->Distortion[SSIM] == 1)
    {
      printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
      printf("Frame      Bit/pic   Filler NVB  WP QP   QL   SnrY    SnrU    SnrV   SsimY   SsimU   SsimV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
      printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
      printf("------------------------------------------------------------------------------------------------------------------\n");
      printf("Frame      Bit/pic   Filler NVB  WP QP   QL   SnrY    SnrU    SnrV    Time(ms) MET(ms) Frm/Fld   I D L0 L1 RDP Ref\n");
      printf("------------------------------------------------------------------------------------------------------------------\n");
    }
    }
    break;
  }
}

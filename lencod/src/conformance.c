#include "global.h"
#include "conformance.h"

void profile_check(InputParameters *p_Inp)
{
  if((p_Inp->ProfileIDC != BASELINE ) &&
     (p_Inp->ProfileIDC != MAIN ) &&
     (p_Inp->ProfileIDC != EXTENDED ) &&
     (p_Inp->ProfileIDC != FREXT_HP    ) &&
     (p_Inp->ProfileIDC != FREXT_Hi10P ) &&
#if (MVC_EXTENSION_ENABLE)
     (p_Inp->ProfileIDC != MULTIVIEW_HIGH )      &&  // MVC multiview high profile
     (p_Inp->ProfileIDC != STEREO_HIGH )         &&  // MVC stereo high profile
#endif
     (p_Inp->ProfileIDC != FREXT_Hi422 ) &&
     (p_Inp->ProfileIDC != FREXT_Hi444 ) &&
     (p_Inp->ProfileIDC != FREXT_CAVLC444 )&&
     (p_Inp->ProfileIDC != NO_PROFILE))
  {
#if (MVC_EXTENSION_ENABLE)
    snprintf(errortext, ET_SIZE, "Profile must be in\n\n  66 (Baseline),\n  77 (Main),\n  88 (Extended),\n 100 (High),\n 110 (High 10 or High 10 Intra)\n"
      " 122 (High 4:2:2 or High 4:2:2 Intra),\n 244 (High 4:4:4 predictive or High 4:4:4 Intra),\n  44 (CAVLC 4:4:4 Intra)\n 118 (MVC profile),\n 0 (no profile checking)\n");
#else
    snprintf(errortext, ET_SIZE, "Profile must be in\n\n  66 (Baseline),\n  77 (Main),\n  88 (Extended),\n 100 (High),\n 110 (High 10 or High 10 Intra)\n"
      " 122 (High 4:2:2 or High 4:2:2 Intra),\n 244 (High 4:4:4 predictive or High 4:4:4 Intra),\n  44 (CAVLC 4:4:4 Intra),\n 0 (no profile checking)\n");
#endif
    error (errortext, 500);
  }
  if (p_Inp->ProfileIDC == NO_PROFILE)
  {
    printf("WARNING: ProfileIDC equal to 0 disables profile checking. \nThis allows experimental coding, but will create non-conforming streams!\n");
    return;
  }

  if ((p_Inp->partition_mode) && (p_Inp->symbol_mode==CABAC))
  {
    snprintf(errortext, ET_SIZE, "Data partitioning and CABAC is not supported in any profile.");
    error (errortext, 500);
  }

  if (p_Inp->redundant_pic_flag)
  {
    if (p_Inp->ProfileIDC != BASELINE)
    {
      snprintf(errortext, ET_SIZE, "Redundant pictures are only allowed in Baseline profile (ProfileIDC = 66).");
      error (errortext, 500);
    }
  }

  if ((p_Inp->partition_mode) && (p_Inp->ProfileIDC!=EXTENDED))
  {
    snprintf(errortext, ET_SIZE, "Data partitioning is only allowed in Extended profile (ProfileIDC = 88).");
    error (errortext, 500);
  }

  if (p_Inp->ChromaIntraDisable && p_Inp->FastCrIntraDecision)
  {
    fprintf( stderr, "\n Warning: ChromaIntraDisable and FastCrIntraDecision cannot be combined together.\n Using only Chroma Intra DC mode.\n");
    p_Inp->FastCrIntraDecision=0;
  }
  
  if ((p_Inp->sp_periodicity) && (p_Inp->ProfileIDC != EXTENDED ))
  {
    snprintf(errortext, ET_SIZE, "SP pictures are only allowed in Extended profile (ProfileIDC = 88).");
    error (errortext, 500);
  }

  // baseline
  if (p_Inp->ProfileIDC == BASELINE )
  {
    if ((p_Inp->NumberBFrames || p_Inp->BRefPictures==2) && p_Inp->PReplaceBSlice == 0)
    {
      snprintf(errortext, ET_SIZE, "B slices are not allowed in Baseline profile (ProfileIDC = 66).");
      error (errortext, 500);
    }
    if (p_Inp->WeightedPrediction)
    {
      snprintf(errortext, ET_SIZE, "Weighted prediction is not allowed in Baseline profile (ProfileIDC = 66).");
      error (errortext, 500);
    }
    if (p_Inp->WeightedBiprediction)
    {
      snprintf(errortext, ET_SIZE, "Weighted prediction is not allowed in Baseline profile (ProfileIDC = 66).");
      error (errortext, 500);
    }
    if (p_Inp->symbol_mode == CABAC)
    {
      snprintf(errortext, ET_SIZE, "CABAC is not allowed in Baseline profile (ProfileIDC = 66).");
      error (errortext, 500);
    }
    if ((p_Inp->PicInterlace) ||(p_Inp->MbInterlace))
    {
      snprintf(errortext, ET_SIZE, "Interlace tools are not allowed in Baseline profile (ProfileIDC = 66).");
      error (errortext, 500);
    }
    if (p_Inp->GenerateMultiplePPS != 0)
    {
      snprintf(errortext, ET_SIZE, "GenerateMultiplePPS is not supported for Baseline profile because it requires enabling Weighted prediction.\n");
      error (errortext, 400);
    }
  }

  // main
  if (p_Inp->ProfileIDC == MAIN )
  {
    if (p_Inp->num_slice_groups_minus1)
    {
      snprintf(errortext, ET_SIZE, "num_slice_groups_minus1>0 (FMO) is not allowed in Main profile (ProfileIDC = 77).");
      error (errortext, 500);
    }
  }

  // extended
  if (p_Inp->ProfileIDC == EXTENDED )
  {
    if (!p_Inp->directInferenceFlag)
    {
      snprintf(errortext, ET_SIZE, "direct_8x8_inference flag must be equal to 1 in Extended profile (ProfileIDC = 88).");
      error (errortext, 500);
    }

    if (p_Inp->symbol_mode == CABAC)
    {
      snprintf(errortext, ET_SIZE, "CABAC is not allowed in Extended profile (ProfileIDC = 88).");
      error (errortext, 500);
    }
  }

  //FRExt
  if ( p_Inp->separate_colour_plane_flag )
  {
    if( p_Inp->yuv_format!=3 )
    {
      fprintf( stderr, "\nWarning: SeparateColourPlane has only effect in 4:4:4 chroma mode (YUVFormat=3),\n         disabling SeparateColourPlane.");
      p_Inp->separate_colour_plane_flag = 0;
    }

    if ( p_Inp->ChromaMEEnable )
    {
      snprintf(errortext, ET_SIZE, "\nChromaMEEnable is not allowed when SeparateColourPlane is enabled.");
      error (errortext, 500);
    }
  }

  // CAVLC 4:4:4 Intra
  if ( p_Inp->ProfileIDC == FREXT_CAVLC444 )
  {
    if ( p_Inp->symbol_mode != CAVLC )
    {
      snprintf(errortext, ET_SIZE, "\nCABAC is not allowed in CAVLC 4:4:4 Intra profile (ProfileIDC = 44).");
      error (errortext, 500);
    }
    if ( !p_Inp->IntraProfile )
    {
      fprintf (stderr, "\nWarning: ProfileIDC equal to 44 implies an Intra only profile, setting IntraProfile = 1.");
      p_Inp->IntraProfile = 1;
    }
  }

  // Intra only profiles
  if (p_Inp->IntraProfile && ( !is_FREXT_profile(p_Inp->ProfileIDC)))
  {
    snprintf(errortext, ET_SIZE, "\nIntraProfile is allowed only with FRExt profiles.");
    error (errortext, 500);
  }

  if (p_Inp->IntraProfile && !p_Inp->idr_period) 
  {
    snprintf(errortext, ET_SIZE, "\nIntraProfile requires IDRPeriod >= 1.");
    error (errortext, 500);
  }

  if (p_Inp->IntraProfile && p_Inp->intra_period != 1) 
  {
    snprintf(errortext, ET_SIZE, "\nIntraProfile requires IntraPeriod equal 1.");
    error (errortext, 500);
  }

  if (p_Inp->IntraProfile && p_Inp->num_ref_frames) 
  {
    fprintf( stderr, "\nWarning: Setting NumberReferenceFrames to 0 in IntraProfile.");
    p_Inp->num_ref_frames = 0;
  }

  if (p_Inp->IntraProfile == 0 && p_Inp->num_ref_frames == 0) 
  {
    snprintf(errortext, ET_SIZE, "\nProfiles other than IntraProfile require NumberReferenceFrames > 0.");
    error (errortext, 500);
  }

  if(p_Inp->Transform8x8Mode && ( !is_FREXT_profile (p_Inp->ProfileIDC)))
  {
    snprintf(errortext, ET_SIZE, "\nTransform8x8Mode may be used only with FRExt profiles.");
    error (errortext, 500);
  }

  if(p_Inp->ScalingMatrixPresentFlag && ( !is_FREXT_profile(p_Inp->ProfileIDC) ))
  {
    snprintf(errortext, ET_SIZE, "\nScalingMatrixPresentFlag may be used only with FRExt profiles.");
    error (errortext, 500);
  }

  if(p_Inp->yuv_format==YUV422 && ( p_Inp->ProfileIDC != FREXT_Hi422 && p_Inp->ProfileIDC !=FREXT_Hi444 && p_Inp->ProfileIDC!=FREXT_CAVLC444 ))
  {
    snprintf(errortext, ET_SIZE, "\nFRExt Profile(YUV Format) Error!\nYUV422 can be used only with ProfileIDC %d or %d or %d\n",FREXT_Hi422, FREXT_Hi444, FREXT_CAVLC444);
    error (errortext, 500);
  }
  if(p_Inp->yuv_format==YUV444 && ( p_Inp->ProfileIDC != FREXT_Hi444 && p_Inp->ProfileIDC!=FREXT_CAVLC444 ))
  {
    snprintf(errortext, ET_SIZE, "\nFRExt Profile(YUV Format) Error!\nYUV444 can be used only with ProfileIDC %d or %d.\n",FREXT_Hi444, FREXT_CAVLC444);
    error (errortext, 500);
  }

  // check RDoptimization mode and profile. FMD does not support Frex Profiles.
  if (p_Inp->rdopt==2 && ( is_FREXT_profile(p_Inp->ProfileIDC)))
  {
    snprintf(errortext, ET_SIZE, "Fast Mode Decision methods not supported in FREX Profiles");
    error (errortext, 500);
  }

#if (MVC_EXTENSION_ENABLE)
  if( is_MVC_profile(p_Inp->ProfileIDC) && p_Inp->num_of_views != 2)
  {
    snprintf(errortext, ET_SIZE, "NumberOfViews must be two if ProfileIDC is set to 118 (Multiview High Profile). Otherwise (for a single view) please select a non-multiview profile such as 100.");
    error (errortext, 500);
  }

  //  if (p_Inp->PicInterlace == 2 && p_Inp->MVCInterViewReorder != 0)
  //  {
  //    snprintf(errortext, ET_SIZE, "MVCInterViewReorder not supported with Adaptive Frame Field Coding");
  //    error (errortext, 500);
  //  }

  if(p_Inp->MVCInterViewReorder)
  {
    if ( !is_MVC_profile(p_Inp->ProfileIDC) )
    {
      snprintf(errortext, ET_SIZE, "ProfileIDC must be 118, 128, 134, or 135 to use MVCInterViewReorder=1.");
      error (errortext, 500);
    }
  }
  if ( is_MVC_profile(p_Inp->ProfileIDC) )
  {
    if (p_Inp->ReferenceReorder > 1)
    {
      snprintf(errortext, ET_SIZE, "ReferenceReorder > 1 is not supported with the Multiview (118) or Stereo High (128) profiles and is therefore disabled. \n");
      p_Inp->ReferenceReorder = 0;
    }
    if ( (p_Inp->PocMemoryManagement) && (p_Inp->PicInterlace > 0) )
    {
      snprintf(errortext, ET_SIZE, "PocMemoryManagement>0 is not supported with the Multiview (118) or Stereo High (128) profiles and is therefore disabled. \n");
      p_Inp->PocMemoryManagement = 0;
    }
  }
  // RTP is not defined for MVC yet
  if (p_Inp->of_mode == PAR_OF_RTP && ( is_MVC_profile( p_Inp->ProfileIDC ) ))
  {
    snprintf(errortext, ET_SIZE, "RTP output mode is not compatible with MVC profiles.");
    error (errortext, 500);
  }

#endif

}

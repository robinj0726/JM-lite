#include "global.h"

// Other definitions
static const char EPZS_PATTERN[6][20] = { "Diamond", "Square", "Extended Diamond", "Large Diamond", "SBP Large Diamond", "PMVFAST" };
static const char EPZS_DUAL_PATTERN[7][20] =
{ "Disabled", "Diamond", "Square", "Extended Diamond", "Large Diamond", "SBP Large Diamond", "PMVFAST" };
static const char EPZS_FIXED_PREDICTORS[4][20] = { "Disabled", "All P", "All P + B", "Aggressive" };
static const char EPZS_OTHER_PREDICTORS[2][20] = { "Disabled", "Enabled" };
static const char EPZS_SUBPEL_METHOD[3][20]    = { "Full", "Basic", "Enhanced" };

void
EPZSOutputStats (InputParameters * p_Inp, FILE * stat, short stats_file)
{
  if (stats_file == 1)
  {
    fprintf (stat, " EPZS Pattern                 : %s\n", EPZS_PATTERN[p_Inp->EPZSPattern]);
    fprintf (stat, " EPZS Dual Pattern            : %s\n", EPZS_DUAL_PATTERN[p_Inp->EPZSDual]);
    fprintf (stat, " EPZS Fixed Predictors        : %s\n", EPZS_FIXED_PREDICTORS[p_Inp->EPZSFixed]);
    fprintf (stat, " EPZS Aggressive Predictors   : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSAggressiveWindow]);
#if (MVC_EXTENSION_ENABLE)
    if (p_Inp->num_of_views == 2)
    {
      fprintf (stat, " BL EPZS Temporal Predictors  : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal[0]]);
      fprintf (stat, " EL EPZS Temporal Predictors  : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal[1]]);
    }
    else
    {
      fprintf (stat, " EPZS Temporal Predictors     : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal[0]]);
    }
#else
    fprintf (stat, " EPZS Temporal Predictors     : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal]);
#endif
    fprintf (stat, " EPZS Spatial Predictors      : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSSpatialMem]);
#if (MVC_EXTENSION_ENABLE)
    if ( (p_Inp->num_of_views == 2) && (p_Inp->EnableEnhLayerEPZSScalers) )
    {
      fprintf (stat, " BL EPZS Threshold Multipliers     : (%d %d %d)\n", p_Inp->EPZSMedThresScale[0], p_Inp->EPZSMinThresScale[0], p_Inp->EPZSMaxThresScale[0]);
      fprintf (stat, " EL EPZS Threshold Multipliers     : (%d %d %d)\n", p_Inp->EPZSMedThresScale[1], p_Inp->EPZSMinThresScale[1], p_Inp->EPZSMaxThresScale[1]);
    }
    else
    {
      fprintf (stat, " EPZS Threshold Multipliers   : (%d %d %d)\n", p_Inp->EPZSMedThresScale[0], p_Inp->EPZSMinThresScale[0], p_Inp->EPZSMaxThresScale[0]);
    }
#else
    fprintf (stat, " EPZS Threshold Multipliers   : (%d %d %d)\n", p_Inp->EPZSMedThresScale, p_Inp->EPZSMinThresScale, p_Inp->EPZSMaxThresScale);
#endif
    fprintf (stat, " EPZS Subpel ME               : %s\n", EPZS_SUBPEL_METHOD[p_Inp->EPZSSubPelME]);
    fprintf (stat, " EPZS Subpel ME BiPred        : %s\n", EPZS_SUBPEL_METHOD[p_Inp->EPZSSubPelMEBiPred]);
  }
  else
  {
    fprintf (stat, " EPZS Pattern                      : %s\n", EPZS_PATTERN[p_Inp->EPZSPattern]);
    fprintf (stat, " EPZS Dual Pattern                 : %s\n", EPZS_DUAL_PATTERN[p_Inp->EPZSDual]);
    fprintf (stat, " EPZS Fixed Predictors             : %s\n", EPZS_FIXED_PREDICTORS[p_Inp->EPZSFixed]);
    fprintf (stat, " EPZS Aggressive Predictors        : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSAggressiveWindow]);

#if (MVC_EXTENSION_ENABLE)
    if (p_Inp->num_of_views == 2)
    {
      fprintf (stat, " BL EPZS Temporal Predictors       : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal[0]]);
      fprintf (stat, " EL EPZS Temporal Predictors       : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal[1]]);
    }
    else
    {
      fprintf (stat, " EPZS Temporal Predictors          : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal[0]]);
    }
#else
    fprintf (stat, " EPZS Temporal Predictors          : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSTemporal]);
#endif
    fprintf (stat, " EPZS Spatial Predictors           : %s\n", EPZS_OTHER_PREDICTORS[p_Inp->EPZSSpatialMem]);
#if (MVC_EXTENSION_ENABLE)
    if ( (p_Inp->num_of_views == 2) && (p_Inp->EnableEnhLayerEPZSScalers) )
    {
      fprintf (stat, " BL EPZS Threshold Multipliers     : (%d %d %d)\n", p_Inp->EPZSMedThresScale[0], p_Inp->EPZSMinThresScale[0], p_Inp->EPZSMaxThresScale[0]);
      fprintf (stat, " EL EPZS Threshold Multipliers     : (%d %d %d)\n", p_Inp->EPZSMedThresScale[1], p_Inp->EPZSMinThresScale[1], p_Inp->EPZSMaxThresScale[1]);
    }
    else
    {
      fprintf (stat, " EPZS Threshold Multipliers        : (%d %d %d)\n", p_Inp->EPZSMedThresScale[0], p_Inp->EPZSMinThresScale[0], p_Inp->EPZSMaxThresScale[0]);
    }
#else
    fprintf (stat, " EPZS Threshold Multipliers        : (%d %d %d)\n", p_Inp->EPZSMedThresScale, p_Inp->EPZSMinThresScale, p_Inp->EPZSMaxThresScale);
#endif
    fprintf (stat, " EPZS Subpel ME                    : %s\n", EPZS_SUBPEL_METHOD[p_Inp->EPZSSubPelME]);
    fprintf (stat, " EPZS Subpel ME BiPred             : %s\n", EPZS_SUBPEL_METHOD[p_Inp->EPZSSubPelMEBiPred]);
  }
}

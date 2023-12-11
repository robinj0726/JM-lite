#include "global.h"

void error(char *text, int code)
{
  fprintf(stderr, "%s\n", text);
  // flush_dpb(p_Enc->p_Vid->p_Dpb_layer[0], &p_Enc->p_Inp->output);
  // flush_dpb(p_Enc->p_Vid->p_Dpb_layer[1], &p_Enc->p_Inp->output);
  exit(code);
}
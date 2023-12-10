#ifndef _CONFIG_COMMON_H_
#define _CONFIG_COMMON_H_

//! Maps parameter name to its address, type etc.
typedef struct {
  char *TokenName;    //!< name
  void *Place;        //!< address
  int Type;           //!< type:  0-int, 1-char[], 2-double
  double Default;     //!< default value
  int param_limits;   //!< 0: no limits, 1: both min and max, 2: only min (i.e. no negatives), 3: special case for QPs since min needs bitdepth_qp_scale
  double min_limit;
  double max_limit;
  int    char_size;   //!< Dimension of type char[]
} Mapping;

extern int  InitParams            (Mapping *Map);
extern int DisplayParams(Mapping *Map, char *message);
#endif


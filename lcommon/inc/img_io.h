#ifndef _IMG_IO_H_
#define _IMG_IO_H_

#include "io_video.h"

extern void ParseFrameNoFormatFromString (VideoDataFile *input_file);
extern void OpenFiles                    (VideoDataFile *input_file);
extern void CloseFiles                   (VideoDataFile *input_file);
extern VideoFileType ParseVideoType      (VideoDataFile *input_file);

#endif
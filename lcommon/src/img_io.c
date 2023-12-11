#include "global.h"
#include "img_io.h"

void ParseFrameNoFormatFromString (VideoDataFile *input_file)
{
  char *p1, *p2, *tail;  
  char *fn         = input_file->fname;
  char *fhead      = input_file->fhead;
  char *ftail      = input_file->ftail;
  int  *zero_pad   = &input_file->zero_pad;
  int  *num_digits = &input_file->num_digits;

  *zero_pad = 0;
  *num_digits = -1;
  p1 = p2 = fn;
  while (p1 != NULL && p2 != NULL) 
  {
    // Search for first '_'
    p1 = strstr( p1, "%");
    if (p1 == NULL)
      break;

    strncpy(fhead, fn, p1 - fn);

    // Search for end character of x_size (first 'x' after last '_')
    p2 = strstr( p1, "d");

    // If no 'x' is found, exit
    if (p2 == NULL)    
      break;
    
    // Try conversion of number
    *p2 = 0;

    if (*(p1 + 1) == '0')
      *zero_pad = 1;

    *num_digits = strtol( p1 + 1, &tail, 10);

    // If there are characters left in the string, or the string is null, discard conversion
    if (*tail != '\0' || *(p1 + 1) == '\0') 
    {
      *p2 = 'd';
      p1 = tail;
      continue;
    }

    // Conversion was correct. Restore string
    *p2 = 'd';

    tail++;
    strncpy(ftail, tail, (int) strlen(tail));
    break;
  }

  if (input_file->vdtype == VIDEO_TIFF)
  {
    input_file->is_concatenated = 0;
  }
  else
    input_file->is_concatenated = (*num_digits == -1) ? 1 : 0;
}

void OpenFiles( VideoDataFile *input_file)
{
  if (input_file->is_concatenated == 1)
  {
    if ((int) strlen(input_file->fname) == 0)
    {
      snprintf(errortext, ET_SIZE, "No input sequence name was provided. Please check settings.");
      error (errortext, 500);
    }

    if ((input_file->f_num = open(input_file->fname, OPENFLAGS_READ)) == -1)
    {
      snprintf(errortext, ET_SIZE, "Input file %s does not exist",input_file->fname);
      error (errortext, 500);
    }
  }
}

void CloseFiles(VideoDataFile *input_file)
{
  if (input_file->f_num != -1)
    close(input_file->f_num);
  input_file->f_num = -1;
}

VideoFileType ParseVideoType (VideoDataFile *input_file)
{
  char *format;

  format = input_file->fname + (int) strlen(input_file->fname) - 3;

  if (strcasecmp (format, "yuv") == 0)
  {
    input_file->vdtype = VIDEO_YUV;
    input_file->format.yuv_format = YUV420;
    input_file->avi = NULL;
  }
  else if (strcasecmp (format, "rgb") == 0)
  {
    input_file->vdtype = VIDEO_RGB;
    input_file->format.yuv_format = YUV444;
    input_file->avi = NULL;
  }
  else if (strcasecmp (format, "tif") == 0)
  {
    input_file->vdtype = VIDEO_TIFF;
    input_file->avi = NULL;
  }
  else if (strcasecmp (format, "avi") == 0) 
  {
    input_file->vdtype = VIDEO_AVI;
  }
  else
  {
    //snprintf(errortext, ET_SIZE, "ERROR: video file format not supported");
    //error (errortext, 500);
    input_file->vdtype = VIDEO_YUV;
    input_file->format.yuv_format = YUV420;
    input_file->avi = NULL;
  }

  return input_file->vdtype;
}

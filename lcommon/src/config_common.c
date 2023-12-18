#include "global.h"
#include "configfile.h"

static int  ParameterNameToMapIndex (Mapping *Map, char *s);

#define MAX_ITEMS_TO_PARSE  10000

char *GetConfigFileContent (char *Filename)
{
  long FileSize;
  FILE *f;
  char *buf;

  if (NULL == (f = fopen (Filename, "r")))
  {
      snprintf (errortext, ET_SIZE, "Cannot open configuration file %s.", Filename);
      return NULL;
  }

  if (0 != fseek (f, 0, SEEK_END))
  {
    snprintf (errortext, ET_SIZE, "Cannot fseek in configuration file %s.", Filename);
    return NULL;
  }

  FileSize = ftell (f);

  if (FileSize < 0 || FileSize > 150000)
  {
    snprintf (errortext, ET_SIZE, "\nUnreasonable Filesize %ld reported by ftell for configuration file %s.", FileSize, Filename);
    return NULL;
  }
  if (0 != fseek (f, 0, SEEK_SET))
  {
    snprintf (errortext, ET_SIZE, "Cannot fseek in configuration file %s.", Filename);
    return NULL;
  }

  if ((buf = malloc (FileSize + 1))==NULL) no_mem_exit("GetConfigFileContent: buf");

  // Note that ftell() gives us the file size as the file system sees it.  The actual file size,
  // as reported by fread() below will be often smaller due to CR/LF to CR conversion and/or
  // control characters after the dos EOF marker in the file.

  FileSize = (long) fread (buf, 1, FileSize, f);
  buf[FileSize] = '\0';


  fclose (f);
  return buf;
}

static int ParameterNameToMapIndex (Mapping *Map, char *s)
{
  int i = 0;

  while (Map[i].TokenName != NULL)
    if (0==strcasecmp (Map[i].TokenName, s))
      return i;
    else
      i++;
  return -1;
}

int InitParams(Mapping *Map)
{
  int i = 0;

  while (Map[i].TokenName != NULL)
  {
    if (Map[i].Type == 0)
        * (int *) (Map[i].Place) = (int) Map[i].Default;
    else if (Map[i].Type == 2)
    * (double *) (Map[i].Place) = Map[i].Default;
      i++;
  }
  return -1;
}

int DisplayParams(Mapping *Map, char *message)
{
  int i = 0;

  printf("******************************************************\n");
  printf("*               %s                   *\n", message);
  printf("******************************************************\n");
  while (Map[i].TokenName != NULL)
  {
    if (Map[i].Type == 0)
      printf("Parameter %s = %d\n",Map[i].TokenName,* (int *) (Map[i].Place));
    else if (Map[i].Type == 1)
      printf("Parameter %s = ""%s""\n",Map[i].TokenName,(char *)  (Map[i].Place));
    else if (Map[i].Type == 2)
      printf("Parameter %s = %.2f\n",Map[i].TokenName,* (double *) (Map[i].Place));
      i++;
  }
  printf("******************************************************\n");
  return i;
}

void ParseContent (InputParameters *p_Inp, Mapping *Map, char *buf, int bufsize)
{
  char *items[MAX_ITEMS_TO_PARSE] = {NULL};
  int MapIdx;
  int item = 0;
  int InString = 0, InItem = 0;
  char *p = buf;
  char *bufend = &buf[bufsize];
  int IntContent;
  double DoubleContent;
  int i;

  // Stage one: Generate an argc/argv-type list in items[], without comments and whitespace.
  // This is context insensitive and could be done most easily with lex(1).

  while (p < bufend)
  {
    switch (*p)
    {
    case 13:
      ++p;
      break;
    case '#':                 // Found comment
      *p = '\0';              // Replace '#' with '\0' in case of comment immediately following integer or string
      while (*p != '\n' && p < bufend)  // Skip till EOL or EOF, whichever comes first
        ++p;
      InString = 0;
      InItem = 0;
      break;
    case '\n':
      InItem = 0;
      InString = 0;
      *p++='\0';
      break;
    case ' ':
    case '\t':              // Skip whitespace, leave state unchanged
      if (InString)
        p++;
      else
      {                     // Terminate non-strings once whitespace is found
        *p++ = '\0';
        InItem = 0;
      }
      break;

    case '"':               // Begin/End of String
      *p++ = '\0';
      if (!InString)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      else
        InItem = 0;
      InString = ~InString; // Toggle
      break;

    default:
      if (!InItem)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      p++;
    }
  }

  item--;

  for (i=0; i<item; i+= 3)
  {
    if (0 > (MapIdx = ParameterNameToMapIndex (Map, items[i])))
    {
      //snprintf (errortext, ET_SIZE, " Parsing error in config file: Parameter Name '%s' not recognized.", items[i]);
      //error (errortext, 300);
      printf ("\n\tParsing error in config file: Parameter Name '%s' not recognized.", items[i]);
      i -= 2 ;
      continue;
    }
    if (strcasecmp ("=", items[i+1]))
    {
      snprintf (errortext, ET_SIZE, " Parsing error in config file: '=' expected as the second token in each line.");
      error (errortext, 300);
    }

    // Now interpret the Value, context sensitive...

    switch (Map[MapIdx].Type)
    {
    case 0:           // Numerical
      if (1 != sscanf (items[i+2], "%d", &IntContent))
      {
        snprintf (errortext, ET_SIZE, " Parsing error: Expected numerical value for Parameter of %s, found '%s'.", items[i], items[i+2]);
        error (errortext, 300);
      }
      * (int *) (Map[MapIdx].Place) = IntContent;
      printf (".");
      break;
    case 1:
      if (items[i + 2] == NULL)
        memset((char *) Map[MapIdx].Place, 0, Map[MapIdx].char_size);
      else
        strncpy ((char *) Map[MapIdx].Place, items [i+2], Map[MapIdx].char_size);
      printf (".");
      break;
    case 2:           // Numerical double
      if (1 != sscanf (items[i+2], "%lf", &DoubleContent))
      {
        snprintf (errortext, ET_SIZE, " Parsing error: Expected numerical value for Parameter of %s, found '%s'.", items[i], items[i+2]);
        error (errortext, 300);
      }
      * (double *) (Map[MapIdx].Place) = DoubleContent;
      printf (".");
      break;
    default:
      error ("Unknown value type in the map definition of configfile.h",-1);
    }
  }
  *p_Inp = cfgparams;
}
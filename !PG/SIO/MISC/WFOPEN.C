/*-

FUNCTION NAME:  wfopen
 PROTOTYPE IN:  MISC.H
        LEVEL:  3
      LIBRARY:  MISC.LIB
  DESCRIPTION:  Continually prompts for name of output file until file is
                successfully opened or the user aborts.
      RETURNS:  FILE *:  the FILE pointer or NIL if open unsuccessful.
     COMMENTS:  Asks permission before overwriting a pre-existing file.
                The filename buffer passed must be long enough to hold the
                largest valid system name.
*/

#include  <stdio.h>
#include  <sio\siodef.h>
#include  <ctype.h>
#include  <string.h>

/* 1: user prompt string           */
/* 2: file name buffer             */

FILE *wfopen(char *promptstr, char *fnbuff)
{
     FILE *wfp;
     char locbuff[10];
     for (EVER)
          {
          printf("\n%s: ",promptstr);
          gets(fnbuff);
          if (strcmp(fnbuff,"") == 0)
               return NIL;
          fclose(wfp = fopen(fnbuff, "rb"));      /* open it for reading      */
          if (wfp == NIL)                        /* doesn't already exist    */
               return (fopen(fnbuff, "wb"));
          printf("\n%s already exists. Overwrite\a?  ", fnbuff);
          gets(locbuff);
          if (toupper(locbuff[0]) == 'Y')
               return (fopen(fnbuff, "wb"));
          }
}

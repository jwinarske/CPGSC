/*-

FUNCTION NAME:  rfopen
 PROTOTYPE IN:  MISC.H
        LEVEL:  3
      LIBRARY:  MISC.LIB
  DESCRIPTION:  Continually prompts for filename until file is opened for
                reading or the user aborts.
     COMMENTS:  The file name buffer passed must be long enough to hold the
                largest valid system name.
*/


#include  <stdio.h>
#include  <sio/siodef.h>
#include  <errno.h>
#include  <string.h>

#ifndef gets
extern char *gets(char *buffer);
#endif

/* 1: user prompt string           */
/* 2: file name buffer             */

FILE *rfopen(char *promptstr, char *fnbuff)
{
     FILE *rfp;
     do
          {
          printf("\n%s: ",promptstr);
          gets(fnbuff);
          if (strcmp(fnbuff,"") == 0)        /* user typed CR to exit        */
               return NIL;
          if ( (rfp = fopen(fnbuff, "rb")) == NIL)        /* open failure     */
               if (errno == ENOENT)
                    printf("%s not found.", fnbuff);
               else
                    printf("\nOpen error on %s.", fnbuff);  /* error message */
          } while (rfp == NIL);                   /* repeat until open succeeds   */
     return rfp;
}

/*-

FUNCTION NAME:  s_fputs
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Output string to SIO under control of the soctl_
                structure.
     COMMENTS:  The local function s_fflush clears s_fputc's
                single-character buffer.
*/

#include <stdio.h>
#include <sio/siodef.h>
#include <sio/buos.h>

static void s_fflush(SIO *siop)
{
     if (siop->s_octl->flushflag &&  !siop->s_octl->rawflag)
          s_fputc(siop, siop->s_octl->lastc);
}

void s_fputs(SIO *siop, char *str)
{
     while (*str != '\0')
          s_fputc(siop, *str++);
     s_fflush(siop);
     if (siop->s_octl->consflag == TRUE)
          putchar('\n');
}

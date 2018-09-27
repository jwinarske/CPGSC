/*-
FUNCTION NAME:  cbuff
        LEVEL: 3
 PROTOTYPE IN:  TERM.H
  DESCRIPTION:  Subfunction for capturing serial data into a disk file using
               C's internal FILE buffer.
      RETURNS:  int:  1 if a disk write error occurred, otherwise 0.
     COMMENTS:  Flow control supported.  Size of buffer is given by
                the constant BUFSIZ in STDIO.H.
*/

#define BYTESLEFT  25                  /* buffer remaining after XPAUSE      */
#define XPAUSE    BUFSIZ - BYTESLEFT   /* bytes before sending flow control  */

#include <stdio.h>
#include <sio\siodef.h>
#include <sio\sioctl.h>
#include <sio\buos.h>
#include <sio\key.h>

int cbuff(SIO *siop, FILE *rcvfp)
{
     extern ULONG bytetot;
     int    buffcnt = 0, error = 0;          /*    bytes in C's I/O buffer   */
     int c;             /* must be int for negative returns */
     long  i;     printf("C's %d buffer in use.\n",BUFSIZ);
     s_ipush(siop);
     for (EVER)
          {
          if ( (c = inkey()) == (int) siop->s_octl->kbortc)  /* get keyboard byte  */
               break;                        /* end download if abort        */
          if (c != -1)
               s_fputc(siop, c);             /* transmit keyboard byte       */
          if ( (c = s_fgetc(siop)) < 0)      /* now check SIO for byte       */
               continue;
          putc(c, rcvfp);
          ++bytetot;
          if (++buffcnt == XPAUSE )          /* C's I/O buffer almost full?  */
               {
               flowoff(siop);                     /* Send flow-off to sender */
               s_icntrl(siop, SET, T_OUTFLAG, ON); /*1 tsec for late arrivers*/
               for (i = BYTESLEFT; i > 0; i--)    /* wait for sender to stop */
                    {
                    if ( (c = s_fgetc(siop)) == TIMEOUT)
                         break;              /* timeout, so sender is paused */
                    else if (c == IGNORE)
                         continue;
                    else
                         {
                         putc(c, rcvfp);     /* catch slow pokes, too        */
                         ++buffcnt; ++bytetot;
                         }
                    }
               if (c != TIMEOUT)             /* sender didn't respond        */
                    puts("\nRemote ignored flow-off request.\a");
               error = fflush(rcvfp) != 0;
               s_icntrl(siop, T_OUTFLAG, OFF); /* restore zero wait on input */
               if (s_icntrl(siop, GET, CONSFLAG) == OFF)
                    printf("%lu total bytes written.\r", bytetot);
               buffcnt = 0;
               flowon(siop);                    /* release sender stuck         */
               if (error)                    /* disk error ends capture      */
                    break;
               }
          }
     puts("\nExit Menu");
     s_ipop(siop);
     return error;                    /* return 0 if no error, 1 if error  */
}
	
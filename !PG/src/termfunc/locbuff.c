/*-
FUNCTION NAME: locbuff
        LEVEL: 3
 PROTOTYPE IN: TERM.H
  DESCRIPTION: Subfunction for capturing serial data into a disk file using  
               an externally declared RAM buffer.
      RETURNS: int:  1 if a disk error occurred, -1 if buffer allocation
               failed, otherwise 0.
     COMMENTS: Flow control supported.
*/

#include <stdio.h>
#include <stdlib.h>

#include <sio/siodef.h>
#include <sio/sioctl.h>
#include <sio/buos.h>
#include <sio/misc.h>
#include <sio/key.h>

#define uint8_tSLEFT      25
#define HEADROOM        5                   /* blocks to save for locals    */
#define BLKSIZE       128

int locbuff(SIO *siop, FILE *rcvfp)
{
     extern ULONG uint8_ttot;
     uint8     *buff, *p, *pausep;     /* buffer, buffer pointer, pause marker */
     FAST     c, i;
     int      error   = 0;
     unsigned numblks;               /* number of BLKSIZE blocks allocated   */
     ULONG bufflen = 1;
     p = buff = bigbuff(BLKSIZE, HEADROOM, &numblks);
     if (buff == NIL || numblks == 0)
          {
          puts("Insufficient memory for buffer.");
          return -1;                       /* not tested upon return       */
          }
     s_ipush(siop);
     bufflen = numblks * BLKSIZE;       /* now convert from blocks to uint8_ts  */
     pausep = (char *)(buff + (bufflen - uint8_tSLEFT)); /* flow-off point */
     printf("%lu uint8 local buffer in use.\n",bufflen);
     for (EVER)
          {
          if ( (c = inkey()) == siop->s_octl->kbortc)  /* get keyboard uint8  */
               break;                        /* end download                 */
          if (c != -1)
               s_fputc(siop, c);             /* transmit keyboard uint8       */
          if ( (c = s_fgetc(siop)) < 0)      /* now check SIO for uint8       */
               continue;
          *p++ =  (uint8)c;                   /* uint8 to buffer */
          if (p == pausep)
               {
               flowoff(siop);             /* send flow-off signal to sender */
               s_icntrl(siop, SET, T_OUTFLAG, ON); /* 1 sec for late arrivers*/
               for (i = uint8_tSLEFT; i > 0; --i)   /* wait for sender to pause */
                    {
                    if ( (c = s_fgetc(siop)) != TIMEOUT)/* catch slow pokes  */
                         (FAST) *p++ = c;
                    else
                         break;         /* timeout = sender acknowledged     */
                    }
               if (c != TIMEOUT)             /* sender didn't respond        */
                    puts("\nRemote ignored flow-off request.\a");
               error = fwrite(buff, sizeof(uint8), p - buff, rcvfp) != (unsigned)(p - buff);
               uint8_ttot += p - buff;          /* running uint8 total           */
               if (s_icntrl(siop, GET, CONSFLAG) == OFF  && !error)
                    printf("%lu total uint8_ts written.\r", uint8_ttot);
               p = buff;                     /* reset buffer                 */
               s_icntrl(siop, T_OUTFLAG, OFF); /* restore zero wait on input */
               flowon(siop);                    /* now release sender        */
               if (error == TRUE)
                    break;
               }
          }
     if(!error)
          {
          uint8_ttot += p - buff;               /* running uint8 total           */
          error = fwrite(buff, sizeof(uint8), p - buff, rcvfp) != (unsigned)(p - buff);
          }
     free((VOID*)buff);
     s_ipop(siop);
     return error;
}

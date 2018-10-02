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

#define BYTESLEFT      25
#define HEADROOM        5                   /* blocks to save for locals    */
#define BLKSIZE       128

int locbuff(SIO *siop, FILE *rcvfp)
{
     extern ULONG bytetot;
     uint8_t     *buff, *p, *pausep;     /* buffer, buffer pointer, pause marker */
     FAST     c, i;
     int      error   = 0;
     uint16_t numblks;               /* number of BLKSIZE blocks allocated   */
     ULONG bufflen = 1;
     p = buff = bigbuff(BLKSIZE, HEADROOM, &numblks);
     if (buff == NIL || numblks == 0)
          {
          puts("Insufficient memory for buffer.");
          return -1;                       /* not tested upon return       */
          }
     s_ipush(siop);
     bufflen = numblks * BLKSIZE;       /* now convert from blocks to bytes  */
     pausep = (uint8_t *)(buff + (bufflen - BYTESLEFT)); /* flow-off point */
     printf("%lu byte local buffer in use.\n",bufflen);
     for (EVER)
          {
          if ( (c = inkey()) == siop->s_octl->kbortc)  /* get keyboard byte  */
               break;                        /* end download                 */
          if (c != -1)
               s_fputc(siop, c);             /* transmit keyboard byte       */
          if ( (c = s_fgetc(siop)) < 0)      /* now check SIO for byte       */
               continue;
          *p++ =  (uint8_t)c;                   /* byte to buffer */
          if (p == pausep)
               {
               flowoff(siop);             /* send flow-off signal to sender */
               s_icntrl(siop, SET, T_OUTFLAG, ON); /* 1 sec for late arrivers*/
               for (i = BYTESLEFT; i > 0; --i)   /* wait for sender to pause */
                    {
                    if ( (c = s_fgetc(siop)) != TIMEOUT)/* catch slow pokes  */
                         *p++ = (uint8_t)c;
                    else
                         break;         /* timeout = sender acknowledged     */
                    }
               if (c != TIMEOUT)             /* sender didn't respond        */
                    puts("\nRemote ignored flow-off request.\a");
               error = fwrite(buff, sizeof(uint8_t), p - buff, rcvfp) != (unsigned)(p - buff);
               bytetot += (ULONG)(p - buff);          /* running byte total           */
               if (s_icntrl(siop, GET, CONSFLAG, 0) == OFF  && !error)
                    printf("%lu total bytes written.\r", bytetot);
               p = buff;                     /* reset buffer                 */
               s_icntrl(siop, T_OUTFLAG, OFF, 0); /* restore zero wait on input */
               flowon(siop);                    /* now release sender        */
               if (error == TRUE)
                    break;
               }
          }
     if(!error)
          {
          bytetot += (ULONG)(p - buff);               /* running byte total           */
          error = fwrite(buff, sizeof(uint8_t), p - buff, rcvfp) != (unsigned)(p - buff);
          }
     free((VOID*)buff);
     s_ipop(siop);
     return error;
}

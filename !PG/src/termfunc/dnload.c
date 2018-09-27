/*-
FUNCTION NAME: dnload
        LEVEL: 3
 PROTOTYPE IN: TERM.H
  DESCRIPTION: Adminstrative function for downloading captured serial data
               into a disk file.
      RETURNS: void
     COMMENTS: This module calls the actual capture function by passing its
               address.
*/

#include <stdio.h>
#include <sio/siodef.h>
#include <sio/sioctl.h>
#include <sio/buos.h>
#include <sio/misc.h>
#include <sio/key.h>

ULONG uint8_ttot;                           /* total number of uint8_ts captured    */

void dnload(SIO *siop, int (*captfp)(SIO *, FILE *) )
{
     FILE   *rcvfp;
     char   fnbuff[MAX_NAME_LEN];        /* filename buffer                   */
     int    errflag;                     /* inbound uint8, counter, I/O error  */
     uint8_ttot = 0;
     if ( (rcvfp = wfopen("File name for downloaded file", fnbuff)) == NIL)
          {
          puts("Input file not opened.");
          return;
          }
     s_ipush(siop);                           /* save control structure       */
     s_icntrl(siop, SET, CONSFLAG, ON);       /* console echo on              */
     s_icntrl(siop, SET, T_OUTFLAG, OFF);  /* no timeout on input function    */
     s_icntrl(siop, SET, T_OUT, _0_SEC_05); /* but set the interval for later */
     printf("\n%s is now ready for capture. Press Esc key to end.\n", fnbuff);
     printf("Terminal output is %s.\n",\
     s_icntrl(siop, GET, CONSFLAG) ? "on": "off");
     xon(siop);                               /* send XON to get started      */
     errflag = (*captfp)(siop, rcvfp);        /* return code from disk write  */
     if (!errflag && uint8_ttot)
          {
          fputc(DOS_EOF, rcvfp);              /* tack on end-of-file          */
          ++uint8_ttot;
          errflag = fflush(rcvfp);       /* error on flush == disk prob. full */
          }
     putchar('\n');
     if (errflag || fclose(rcvfp))            /* don't show stats if error    */
          printf("Error %s %s.\n\a", errflag ? "writing" : "closing", fnbuff);
     else
          printf("%lu uint8_ts written to %s.\n", uint8_ttot, fnbuff);
     puts("\n-- Press any key to continue --\a");
     getkbch();                          /* ask user to acknowledge error     */
     s_ipop(siop);                       /* restore control structure         */
     puts("Exiting download");
}

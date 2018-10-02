/*-
FUNCTION NAME: upload
        LEVEL: 3
 PROTOTYPE IN: TERM.H
  DESCRIPTION: Function to transmit (upload) a file.
     COMMENTS: XON-XOFF flow control is supported.
*/

#include <stdio.h>
#include "sio/siodef.h"
#include "sio/sioctl.h"
#include "sio/misc.h"
#include "sio/key.h"
#include "sio/buos.h"

void upload(SIO *siop)
{
     FILE *xmitfp;                /* return type declarations     */
     char fnbuff[MAX_NAME_LEN];
     int c;
     int errflag = 0;
     putchar('\n');                          /* now open file, return *FILE  */
     if ( (xmitfp = rfopen("Name of file to upload", fnbuff, MAX_NAME_LEN)) == NIL)
          return;                            /* user terminated upload       */
     s_opush(siop);                          /* save output structure_       */
//     s_ocntrl(siop, SET, IB_DLY, _0_SEC_1);/* interuint8_t delay of .1 secs   */
//     s_ocntrl(siop, SET, IL_DLYFLAG, ON);  /* interline delay for slow ttys*/
     s_ocntrl(siop, SET, CONSFLAG, ON);      /* turn on console output       */
     while ( (c = getc(xmitfp)) != EOF)      /*   transmit the file          */
          {
          if (s_keybort(siop))          /* transfer aborted from keyboard?   */
               break;
          s_fputc(siop, c);
          }
     putchar('\n');
     errflag = ferror(xmitfp);         /* see if getc ended with an error    */
     if (errflag || fclose(xmitfp))    /* if read or close error             */
          printf("Error %s %s.\n\a", errflag ? "reading" : "closing", fnbuff);
     s_opop(siop);                     /* restore output control structure_  */
     puts("End of upload.\n\n-- Press any key to continue --");
     getkbch();
     puts("Exit upload.");
}

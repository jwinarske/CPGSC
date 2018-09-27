/*-
FUNCTION NAME:  s_close
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Modifications in support of interrupt I/O.
      RETURNS:  SIO*
*/

#include <stdio.h>            /*//*/
#include <stdlib.h>
#include <sio/siodef.h>
#include <sio/buos.h>
#include <sio/uart.h>
#include <sio/level0.h>
#include <malloc.h> /*//*/

int s_close(SIO *siop)
{
     extern struct SIOLIST __siolist[];      /* list of available SIO   */
     extern int __maxsios;        /* global -- maximum number of serial ports */
     int i;
     if (siop == NIL)
          return NO_CLOSE;
     /* Mark this sio closed in siolist */
     for (i = 0 ;i < __maxsios; i++)
          if ( (siop == __siolist[i].siop) && (__siolist[i].sio_openflag == OPEN))
               {
               __siolist[i].sio_openflag = CLOSED;
               break;
               }
     if ( i == __maxsios)                   /* no match in list */
          return NO_CLOSE;

     /* Enable interrupts to them that wants it */
     if ( __siolist[siop->devnum].intrpt_supp == TRUE)
        {
//        printf("Memory avail = %u\n", _memavl());    /*//*/
        if (siop->intrpt_status.rs232_on == TRUE)
             siop->intrpt_status.rs232_on   = rs232_ioff(siop);

        if (siop->intrpt_status.serr_on == TRUE)
             siop->intrpt_status.serr_on = serr_ioff(siop);

        if (siop->intrpt_status.rcv_on == TRUE)
             siop->intrpt_status.rcv_on     = rcv_ioff(siop);

        if (siop->intrpt_status.tx_on == TRUE)
             siop->intrpt_status.tx_on      = tx_ioff(siop, WAIT_TIL_FINISH);
//        printf("Memory avail = %u\n", _memavl());  /*//*/
        }
     __sysintroff(siop, siop->devnum);  /* shut down SIO interrupt system */
     s_restore(siop);                /* restore uart as found */
     siop->devnum  = VIRGIN;          /* install dummy device number  */
     return 0;
}


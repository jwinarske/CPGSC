/*-
FUNCTION NAME: tx_iwrite
  DESCRIPTION: Submits a block of data for interrupt-driven transmission.
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.H
     RETURNS : Q_OK if there was room in the queue, Q_FULL if
               not, or Q_BUF2BIG if the buffer passed is larger
               than the local buffer.
*/

#include <stdio.h>
#include <sio\siodef.h>
#include <sio\misc.h>
#include <sio\U16x50.H>          /* isr_tx prototype */
#include <memory.h>              /* memcpy prototype */
#include <sio\level0.h>         


short tx_iwrite(SIO *siop, BYTE *newbuff, short count)
{
     if (siop->tx_headp->inuseflag == TX_INUSE)  /* queue was full, try again */
          return Q_FULL;
     if (count > siop->tx_buffsize)
          return Q_BUF2BIG;
     if (count == 0)     
         return Q_OK;
     siop->tx_headp->buffp = siop->tx_headp->locbuff; /* reset pointer */
     memcpy(siop->tx_headp->buffp, newbuff, count);/* copy into local storage */
     siop->tx_headp->buffcnt = count;
     siop->tx_headp->inuseflag = TX_INUSE;         /* mark queue element busy */
     if (++siop->tx_headp == siop->tx_queue_end)   /* test boundary           */
          siop->tx_headp = &siop->tx_list[0];      /* wrap pointer            */
     if (siop->tx_idle == TRUE)          /* if transmitter is off, kickstart  */
          {
          siop->tx_idle = FALSE;
          (*siop->isr[INDEX_THRE])(siop);    /* call the transmit interrupt */
          }
     return Q_OK;
}


/*
FUNCTION NAME: isr_tx
 PROTOTYPE IN: U16X50.H
        LEVEL: 1
      LIBRARY: U16X50.LIB
  DESCRIPTION: Transmit interrupt subroutine. Transmits data from buffer at 
               tx_tailp.  Supports flow control.
      RETURNS: void
     COMMENTS: A circular buffer of queues.  Queues are allocated by the 
               tx_ion function. 
INCLUDE FILES: siodef.h, buos.h, sioctl.h
*/


#include <sio/siodef.h>
#include <sio/buos.h>
#include <sio/sioctl.h>


void isr_tx(SIO *siop)
{
     short tx_cnt;
     
     if (siop->tx_tailp->inuseflag == TX_FREE)    /* if spurious interrupt  */
          return;
     
     if (siop->tx_iflowstate == FLOW_OFF)         /* flow-off is in effect  */
          return;                                 /* will require kickstart */

     tx_cnt = siop->tx_fifo_depth - siop->tx_fifo_trigger; /* uint8_ts to xmit */
     if (siop->tx_tailp->buffcnt > tx_cnt)      /* don't pipeline last char */
        {
        short pipecnt = tx_cnt;       
        char *buffp = siop->tx_tailp->buffp;
        while (pipecnt--)
           s_xmit(siop, *buffp++);
        siop->tx_tailp->buffcnt -= tx_cnt;
        return;
        }
        
     while (tx_cnt-- > 0)                                  /* fill uart fifo*/
          {
          if (siop->tx_tailp->buffcnt == 0 )               /* buffer empty? */
               {
               siop->tx_tailp->inuseflag = TX_FREE;        /* Mark it free  */
               if (++siop->tx_tailp == siop->tx_queue_end) /* pointer wrap? */
                    siop->tx_tailp = &siop->tx_list[0];
               if (siop->tx_tailp->inuseflag == TX_FREE)   /* all done ?    */
                    {
                    siop->tx_idle = TRUE;               /* kickstart needed */
                    return;
                    }
               }
          s_xmit(siop, *siop->tx_tailp->buffp);   /* send next char in buff */
          --siop->tx_tailp->buffcnt;              /* adjust counter         */
          ++siop->tx_tailp->buffp;
          }
     return;
}

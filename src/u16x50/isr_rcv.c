// This file contains all receiver interrupt handlers--with and without flow
// control

#include <stdlib.h>
#include <sio/siodef.h>
#include <sio/buos.h>           
#include <sio/sioctl.h>           
#include <sio/level0.h>

/*-

FUNCTION NAME:  isr_rcv450
 PROTOTYPE IN:  U16X50.H
        LEVEL:  1
      LIBRARY:  SIO.LIB
  DESCRIPTION:  uint8-read Interrupt subhandler for 16450/8250 (index 2)
                interrupts. Also used for 16550 FIFO timeout 
                interrupt (index 6).
      RETURNS:  void
     COMMENTS:  Reads a uint8 from the UART's FIFO, places it in the 
                interrupt buffer at rcv_headp. If, after incrementation, 
                rcv_headp points past the end of the buffer, it is reset 
                to point to the beginning of the buffer. 
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h
*/



void isr_rcv450(register SIO *siop)
{
   *siop->rcv_headp = s_rcv(siop);         /* Read receiver       */
   	if ( ++siop->rcv_headp == siop->rcv_buffend)  /* If at end of buffer */
        siop->rcv_headp = siop->rcv_buff;              /* Reset pointer end */
}


/*-
FUNCTION NAME:  isr_rcv550
 PROTOTYPE IN:  U16X50.H
        LEVEL:  1
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Multiple uint8-read interrupt subhandler for 16550 
                level-trigger (index 2) interrupt. 
      RETURNS:  void
     COMMENTS:  Reads a uint8 from the UART's FIFO, places it in the 
                interrupt buffer at rcv_headp. If, after incrementation, 
                rcv_headp points past the end of the buffer, it is reset 
                to point to the beginning of the buffer. 
      CAUTION:  If used as a 16450 interrupt handler.
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h

*/

void isr_rcv550(register SIO *siop)
{
     short fifo_uint8_ts = siop->rcv_fifo_trigger;         /* Num uint8_ts in FIFO */
     while (fifo_uint8_ts--)                /* While there's a uint8 in the FIFO */
       {
       *siop->rcv_headp = s_rcv(siop);                      /* Read receiver */
       if ( ++siop->rcv_headp == siop->rcv_buffend)   /* If at end of buffer */
          siop->rcv_headp = siop->rcv_buff;                 /* Reset pointer */
       }
}



/*-
FUNCTION NAME:  isr_rcv450_xoxo
 PROTOTYPE IN:  U16X50.H
        LEVEL:  1
      LIBRARY:  SIO.LIB
  DESCRIPTION:  uint8-read Interrupt subhandler for 16450/8250 (index 2)
                interrupts. Also used for 16550 FIFO timeout 
                interrupt (index 6).  For XON/XOFF flow control.
      RETURNS:  void
     COMMENTS:  Reads a uint8 from the UART's FIFO, places it in the 
                interrupt buffer at rcv_headp. If, after incrementation, 
                rcv_headp points past the end of the buffer, it is reset 
                to point to the beginning of the buffer. 
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h

*/

void isr_rcv450_xoxo(register SIO *siop)
{
   ptrdiff_t diff;
   static size_t bytes_left = FLOW_HEADROOM +1;
   *siop->rcv_headp = s_rcv(siop);                   /* read char into buff */
     if (*siop->rcv_headp  == XOFF  || *siop->rcv_headp  == XON) 
          {
          if (*siop->rcv_headp == XOFF)
               siop->tx_iflowstate = FLOW_OFF; /* semaphore to transmit isr */
          else if (siop->tx_iflowstate == FLOW_OFF)          /* must be XON */
               {
               siop->tx_iflowstate = FLOW_ON;    /* kickstart transmitter   */
               siop->tx_idle = FALSE;            /* set kickstart flag      */
               #if 0 //TODO
               (*siop->isr[INDEX_THRE])(siop);   /* call the xmit interrupt */
               #endif               
               }
           return;                               /* xon/xoff not saved      */
          }

   diff = siop->rcv_headp - siop->rcv_tailp;
   bytes_left = (diff >= 0) ? siop->rcv_buffsize - diff : abs(diff);
   if (bytes_left > 1)                          /* don't let head wrap tail */
        {
        if ( ++siop->rcv_headp == siop->rcv_buffend) /* if at end of buffer */
             siop->rcv_headp = siop->rcv_buff;       /* Reset pointer       */
        diff = siop->rcv_headp - siop->rcv_tailp;    /* compute space       */
        bytes_left = (diff >= 0) ? siop->rcv_buffsize - diff : abs(diff);
        }
   if (bytes_left <= FLOW_HEADROOM)                  /* If at highwater     */
        {
        siop->rcv_iflowstate = OFF;                 /* publish this         */
        s_xmit(siop, XOFF);                         /* send flow-off char   */
        }
}

/*-
FUNCTION NAME:  isr_rcv450_rcts
 PROTOTYPE IN:  U16X50.H
        LEVEL:  1
      LIBRARY:  SIO.LIB
  DESCRIPTION:  uint8-read Interrupt subhandler for 16450/8250 (index 2)
                interrupts. Also used for 16550 FIFO timeout 
                interrupt (index 6).  For RTS/CTS flow control.
      RETURNS:  void
     COMMENTS:  Reads a uint8 from the UART's FIFO, places it in the 
                interrupt buffer at rcv_headp. If, after incrementation, 
                rcv_headp points past the end of the buffer, it is reset 
                to point to the beginning of the buffer. 
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h

*/

void isr_rcv450_rcts(register SIO *siop)
{
   ptrdiff_t diff;
   static ptrdiff_t bytes_left = FLOW_HEADROOM;
  
   *siop->rcv_headp = s_rcv(siop);         /* Read receiver       */
   diff = siop->rcv_headp - siop->rcv_tailp;
   bytes_left = (diff >= 0) ? siop->rcv_buffsize - diff : abs(diff);
   if (bytes_left > 1)                   /* Don't let head wrap tail */
        {
        if ( ++siop->rcv_headp == siop->rcv_buffend)  /* If at end of buffer */
       	    siop->rcv_headp = siop->rcv_buff;              /* Reset pointer end */
        diff = siop->rcv_headp - siop->rcv_tailp;     /* compute space */
        bytes_left = (diff >= 0) ? siop->rcv_buffsize - diff : abs(diff);
        }
   if (bytes_left <= FLOW_HEADROOM)
        {
        siop->rcv_iflowstate = OFF;
        set232(siop, RTS, OFF);
        }
}

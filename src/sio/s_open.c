/*-
FUNCTION NAME:  s_open
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Device-style open for serial port.
      RETURNS:  SIO*
*/

#include <stdio.h>            /*//*/
#include <malloc.h>
#include "sio/siodef.h"
#include "sio/buos.h"
#include "sio/sioctl.h"
#include "sio/uart.h"
#include "sio/level0.h"


int s_errno;

SIO *s_open(uint16_t portnum)
{
     extern struct SIOLIST __siolist[];
     extern uint16_t __maxsios;             /* global -- number of ports  */

     SIO *siop;                          /* SIO pointer to return      */

     if (portnum >= __maxsios)            /* is device number legal?    */
          {
          s_errno = BAD_PORT;
          return NIL;
          }
     if (__isport(portnum) == NUL)       /* is the hardware installed? */
          {
          s_errno = NO_PORT;
          return NIL;
          }
     if (__siolist[portnum].siop == NIL) /* does an SIO exist for it?  */
          {
          s_errno = NO_PORT;
          return NIL;
          }
     if (__siolist[portnum].sio_openflag != CLOSED)  /* is it already open? */
          {
          s_errno = OPEN_NOW;
          return NIL;
          }
     siop = __siolist[portnum].siop;     /* SIO pointer from table     */
     __sys_disable();
     s_config(siop);                     /* set up SIO's uart          */
     __sys_enable();
     (void) setformat(siop, PARITY, siop->par->start);
     (void) setformat(siop, STOPS,  siop->sb->start);
     (void) setformat(siop, DATALEN, siop->dl->start);
     (void) setbaud(siop, siop->br->start);
     (void) set232(siop, DTR, siop->dtr->start); /* set RS-232 and GP outputs */
     (void) set232(siop, RTS, siop->rts->start);
     (void) set232(siop, GPO1, siop->gpo1->start);
     (void) set232(siop, GPO2, siop->gpo2->start);
     (void) setuart(siop, SETCLK, siop->clkf->start); /* set clock factor     */
     (void) setuart(siop, RXHSON, siop->dcdhs->start);
     (void) setuart(siop, TXHSON, siop->ctshs->start);
     (void) setuart(siop, XMITON, siop->txenable->start);
     (void) setuart(siop, RCVON, siop->rxenable->start);
     siop->devnum = portnum;                     /* put device number in SIO  */

     if ( __siolist[siop->devnum].intrpt_supp == TRUE)
          {
          if (siop->intrpt_status.rs232_wanted)
              siop->intrpt_status.rs232_on   = rs232_ion(siop);

          if (siop->intrpt_status.serr_wanted)
              siop->intrpt_status.serr_on = serr_ion(siop);

          if (siop->intrpt_status.rcv_wanted)
              siop->intrpt_status.rcv_on = rcv_ion(siop);

          if (siop->intrpt_status.tx_wanted)
              siop->intrpt_status.tx_on  = tx_ion(siop, TX_NUMBUFFS, TX_BUFSIZ);
          __sysintron(siop, portnum);     /*  enable system and uart interrupts */
          }
     switch (siop->flow_wanted)
     	{
     	case NO_FLOW:
            	siop->flowon      = flowon_none;
            	siop->flowoff     = flowoff_none;
            	siop->getflow_req = flow_req_none;
     			break;
     	case XON_XOFF:
                if (siop->intrpt_status.rcv_on == ON)
                	{
            	    siop->flowon      = ixon;
            	    siop->flowoff     = ixoff;
                    (void) s_revector(siop, RXRDY, isr_rcv450_xoxo);
                    siop->s_read = s_ircv_xoxo;     /* reader for XON/XOFF */
                	}
                else
                    {
            	    siop->flowon      = xon;
            	    siop->flowoff     = xoff;
            	    }
                if (siop->intrpt_status.tx_on == ON)
            	    siop->getflow_req = flow_req_xoxo;
                else
            	    siop->getflow_req = flow_req_xoxo;
     	        break;
     	case RTS_CTS:
                if (siop->intrpt_status.rcv_on == ON)
                	{
    	            siop->flowon      = irtson;
    	            siop->flowoff     = irtsoff;
                    (void) s_revector(siop, RXRDY, isr_rcv450_rcts);
                    siop->s_read = s_ircv_rcts;   /* reader for RTS/CTS */
                    }
                else
                	{
    	            siop->flowon      = rtson;
    	            siop->flowoff     = rtsoff;
                    }
                if (siop->intrpt_status.tx_on == ON)
    	            siop->getflow_req = iflow_req_rcts;
                else
    	            siop->getflow_req = flow_req_rcts;
     	        break;
     	default:
     		   break;
        }
     __siolist[portnum].sio_openflag = OPEN;     /* mark SIO open in list */
     return siop;
}

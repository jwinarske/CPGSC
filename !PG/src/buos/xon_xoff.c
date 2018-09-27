/*-
FUNCTION NAME:  flow_req_xoxo, xon, xoff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.H
  DESCRIPTION:  Functions to support virtual flow control via XON/XOFF.
                under polled I/O.

      RETURNS:  uint16_t/VOID
     COMMENTS:  Get Flow Request: flow_req_xoxo
                    Turn Flow ON: xon
                    Turn Flow Off: xoff
                
 INCLUDE FILE:  stdio.h, siodef.h, buos.h, sioctl.h
*/

#include <stdio.h>
#include <sio/siodef.h>
#include <sio/buos.h>
#include <sio/sioctl.h>


uint16_t flow_req_xoxo(SIO *siop, ...)
{
     int i;
     i = s_inchar(siop);          /* read next char from input */
     if (i == -1)                 /* if not character ready  */
        return FLOW_NONE;
     if (i == XON)               
	    {
	    siop->tx_vflowstate = FLOW_ON;
        return FLOW_ON;
        }
     if (i == XOFF)
	    {
    	siop->tx_vflowstate = FLOW_OFF;
        return FLOW_OFF;
        }
     return FLOW_NONE;
}


void xon(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_ON;
	s_putc(siop, XON);            /* send DC3  (13hex) */
}

void xoff(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_OFF;
	s_putc(siop, XOFF);          /* send DC1  (11hex) */
}


/*-
FUNCTION NAME:  iflow_req_xoxo, ixon, ixoff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.H
  DESCRIPTION:  Functions to support virtual flow control via XON/XOFF
                under interrupt I/O.
      RETURNS:  uint16_t/VOID
     COMMENTS:  Get Flow Request: iflow_req_xoxo
                    Turn Flow ON:  ixon
                    Turn Flow Off: ixoff
 INCLUDE FILE:  stdio.h, siodef.h, buos.h, sioctl.h
*/

uint16_t iflow_req_xoxo(SIO *siop, ...)
{
//return FLOW_ON;   
return siop->tx_iflowstate;   
}

void ixon(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_ON;
}

void ixoff(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_OFF;
}

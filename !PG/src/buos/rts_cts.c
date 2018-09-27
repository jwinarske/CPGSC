/*-
FUNCTION NAME:  flow_req_rcts, rtson, rtsoff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.H
  DESCRIPTION:  Functions to support virtual flow control via RTS/CTS
                under polled I/O.
      RETURNS:  uint16_t/void
     COMMENTS:  Get Flow Request: flow_req_rcts
                    Turn Flow ON: rtson
                    Turn Flow Off: rtsoff
INCLUDE FILES: stdio.h, siodef.h, buos.h, sioctl.h
*/

#include <stdio.h>
#include <sio/siodef.h>
#include <sio/buos.h>
#include <sio/sioctl.h>


uint16_t flow_req_rcts(SIO *siop, ...)
{
     uint16_t i;
     i = get232(siop, CTS);
     if (i == ON)
     	{
        i = FLOW_ON;
        siop->tx_vflowstate = FLOW_ON;
        }
     else	
        {
     	i = FLOW_OFF;
        siop->tx_vflowstate = FLOW_OFF;
        }
     return i;
}


void rtson(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_ON;
    set232(siop, RTS, ON);
}

void rtsoff(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_OFF;
    set232(siop, RTS, OFF);
}


/*-
FUNCTION NAME:  iflow_req_rcts, irtson, irtsoff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.H
  DESCRIPTION:  Functions to support virtual flow control via RTS/CTS.
                under interrupt I/O.
      RETURNS:  uint16_t/void
     COMMENTS:  Get Flow Request: iflow_req_rcts
                    Turn Flow ON: irtson
                    Turn Flow Off: irtsoff
INCLUDE FILES: stdio.h, siodef.h, buos.h, sioctl.h
*/


uint16_t iflow_req_rcts(SIO *siop, ...)
{
     return FLOW_ON;
}


void irtson(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_ON;
}

void irtsoff(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_OFF;
}

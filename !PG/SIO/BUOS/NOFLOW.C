/*-
FUNCTION NAME:  flow_req_none, flowon_none, flowoff_none
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.H
  DESCRIPTION:  Virtual functions to support no flow control.
      RETURNS:  USHORT/VOID
     COMMENTS:  Get Flow Request: flow_req_none
                    Turn Flow ON: flowon_none
                    Turn Flow Off: flowoff_none
                
 INCLUDE FILE:  stdio.h, siodef.h, buos.h, sioctl.h
*/

#include <stdio.h>
#include <sio\siodef.h>
#include <sio\buos.h>
#include <sio\sioctl.h>


USHORT flow_req_none (SIO *siop, ...)
{
    siop->tx_vflowstate = FLOW_ON;
    return FLOW_NONE;
}

void flowon_none(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_ON;
}

void flowoff_none(SIO *siop)
{
    siop->rcv_vflowstate = FLOW_ON;
}


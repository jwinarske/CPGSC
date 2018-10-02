/*-
FUNCTION NAME:  setuart
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Enable transmitter and receiver; enable transmitter handshake
                on CTS and receiver handshake on DCD; set clock factor.
      RETURNS:  int:  OR_ARG if argument is out of range;  BAD_FCN if
                the function is not supported (SIO pointer is NIL); BAD_ARG
                if the requested setting is not supported by hardware; 0 if
                successful.
*/

#include "sio/siodef.h"
#include "sio/buos.h"

int setuart(SIO *siop, RANK whichone, uint16_t state)
{
     struct vregbits_ *tr_rcv;

     switch(whichone)
          {
          case XMITON: tr_rcv = siop->txenable; break;
          case RCVON : tr_rcv = siop->rxenable; break;
          case RXHSON: tr_rcv = siop->ctshs   ; break;
          case TXHSON: tr_rcv = siop->dcdhs   ; break;
          case SETCLK: tr_rcv = siop->clkf    ; break;
          default:  return OR_ARG;
          }
     return vsetbits(siop, tr_rcv, state);
}

/*-
FUNCTION NAME: s_xmitstat
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Polls the UART's transmitter holding register status bit.
      RETURNS: FAST: Non-zero if the transmit holding register is empty.
     COMMENTS: Compare to the s_txemtpy function
*/

#include <sio\siodef.h>

FAST s_xmitstat(register SIO *siop)
{
     return ( (*siop->readbyte)(siop->uart_base + siop->status_off) & siop->xmitmask);
}

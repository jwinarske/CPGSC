/*-
FUNCTION NAME: s_txempty
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Ascertains if the UART's transmitter is empty; ie., if
               its transmit shift register is empty.
      RETURNS: TRUE if transmitter shift register is empty.
*/

#include <sio\siodef.h>

FAST s_txempty(SIO *siop)
{
     return ( (*siop->readbyte)(siop->uart_base + siop->status_off) & siop->tx_emptymask);
}

/*-
FUNCTION NAME: s_rcv
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Fetches a byte from the UART's receive holding register.
      RETURNS: FAST: the byte received.
*/

#include <sio\siodef.h>

FAST s_rcv(register SIO *siop)
{
     return ( (*siop->readbyte)(siop->uart_base + siop->data_off));
}

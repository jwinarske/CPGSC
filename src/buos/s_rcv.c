/*-
FUNCTION NAME: s_rcv
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Fetches a uint8_t from the UART's receive holding register.
      RETURNS: FAST: the uint8_t received.
*/

#include "sio/siodef.h"

FAST s_rcv(register SIO *siop)
{
    return ( (*siop->readuint8_t)(siop->uart_base + siop->data_off));
}

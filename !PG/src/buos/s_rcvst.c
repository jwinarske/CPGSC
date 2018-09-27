/*-
FUNCTION NAME: s_rcvstat
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Ascertains if there is a uint8_t in the UART's receiver.
      RETURNS: FAST: non-zero if the receivers's holding register contains
               a uint8_t.
     COMMENTS:
*/

#include <sio/siodef.h>

FAST s_rcvstat(register SIO *siop)
{
     return ((*siop->readuint8_t)(siop->uart_base + siop->status_off) & siop->rcvmask);
}

/*-
FUNCTION NAME: s_rcvstat
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Ascertains if there is a byte in the UART's receiver.
      RETURNS: FAST: non-zero if the receivers's holding register contains
               a byte.
     COMMENTS:
*/

#include <sio\siodef.h>

FAST s_rcvstat(register SIO *siop)
{
     return ((*siop->readbyte)(siop->uart_base + siop->status_off) & siop->rcvmask);
}

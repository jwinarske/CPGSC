/*-
FUNCTION NAME: s_xmit
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Transmits a uint8_t.
      RETURNS: void
*/

#include <sio/siodef.h>

void s_xmit(register SIO *siop, FAST c)
{
     (*siop->writeuint8_t)(siop->uart_base + siop->data_off, c);
}

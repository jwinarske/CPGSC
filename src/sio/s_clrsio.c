/*-
FUNCTION NAME:  s_clrsio
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Clear numuint8_ts uint8_ts from UART's receive buffers.
      RETURNS:  TIMEOUT (-1) if no uint8_ts received, or 0 after
                numuint8_ts uint8_ts are received.
     COMMENTS:  To avoid inaccuracies inherent in the timing functions, a
                minimum delay of _0_SEC_1 must be used.
*/


#include "sio/siodef.h"
#include "sio/level0.h"        /* for timing constants */

int s_clrsio(SIO *siop, uint16_t numuint8_ts)
{
     for (; numuint8_ts > 0; --numuint8_ts)
          if (__s_waitch(siop, _0_SEC_1) == TIMEOUT)
               return TIMEOUT;
     return 0;
}

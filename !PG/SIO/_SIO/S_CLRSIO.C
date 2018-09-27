/*-
FUNCTION NAME:  s_clrsio
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Clear numbytes bytes from UART's receive buffers.
      RETURNS:  TIMEOUT (-1) if no bytes received, or 0 after
                numbytes bytes are received.
     COMMENTS:  To avoid inaccuracies inherent in the timing functions, a
                minimum delay of _0_SEC_1 must be used.
*/


#include <sio\siodef.h>
#include <sio\level0.h>        /* for timing constants */

int s_clrsio(SIO *siop, USHORT numbytes)
{
     for (; numbytes > 0; --numbytes)
          if (__s_waitch(siop, _0_SEC_1) == TIMEOUT)
               return TIMEOUT;
     return 0;
}

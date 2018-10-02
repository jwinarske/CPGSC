/*-
FUNCTION NAME:  s_ircvstat
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Interrupt equivalent to s_rcvstat. Ascertains whether a uint8_t
                is available in the interrupt buffer.
      RETURNS:  FAST: Non-zero if a uint8_t is avaialable.
     COMMENTS:  The interrupt buffer is empty when the two pointers
                are equal.
*/

#include "sio/siodef.h"
#include "sio/level0.h"

FAST s_ircvstat(SIO *siop)
{
    return siop->rcv_headp != siop->rcv_tailp;
}

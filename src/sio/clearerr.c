/*-
FUNCTION NAME: s_clearerr
  DESCRIPTION: Clears all pending serialization-error flags.
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.LIB
OTHER OBJECTS: Clears error flags in the SIO.
     RETURNS : void
     COMMENTS:
*/

#include <sio/siodef.h>
#include <sio/level0.h>


void s_clearerr(SIO *siop)
{
     __sys_disable();
     siop->serr.s_errors = siop->serr.bitmap.overrun
     = siop->serr.bitmap.parity = siop->serr.bitmap.frame
     = siop->serr.bitmap.Break 
     = FALSE;
     __sys_enable();
}

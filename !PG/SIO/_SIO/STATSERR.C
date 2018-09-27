/*-
FUNCTION NAME: serial_status
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.LIB
  DESCRIPTION: Reports serialization errors.
      RETURNS: short: 1 if the requested error has occured, 0 if it hasn't,
               and -1 if the error argument is out of range.
     COMMENTS: Error is cleared (made 0) upon exit.
               Array index constants are in UART.H. The value
               returned when the ANY_ERRORS is used can be treated
               as a BOOL, but it is actually a bit-map of the errors
               as follows:
                   Overrun = bit 0    Framing = bit 2
                   Parity  = bit 1    BREAK   = bit 3
*/

#include <sio\siodef.h>
#include <sio\level0.h>

short serial_status(SIO *siop, RANK whichone)
{
     short errtmp;
     switch (whichone)
          {
          case  ANY_ERRORS: errtmp = siop->serr.s_errors;
               siop->serr.s_errors = 0;
               break;
          case  PARITY_ERR: errtmp = siop->serr.bitmap.parity;
               siop->serr.bitmap.parity = FALSE;
               break;
          case OVERRUN_ERR: errtmp = siop->serr.bitmap.overrun;
               siop->serr.bitmap.overrun = FALSE;
               break;
          case   FRAME_ERR: errtmp = siop->serr.bitmap.frame;
               siop->serr.bitmap.frame = FALSE;
               break;
          case    BREAK_ON: errtmp = siop->serr.bitmap.Break;
               siop->serr.bitmap.Break = FALSE;
               break;
          default: errtmp = -1;
          }
     return errtmp;
}

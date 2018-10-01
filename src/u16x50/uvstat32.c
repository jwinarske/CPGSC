/*-
FUNCTION NAME:  _vstat232
        LEVEL:  1
 PROTOTYPE IN:  U16X50.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  Reads the UART register containing the status bit for the
                appropriate RS-232 input.  A pointer to this function
                resides in the SIO.
      RETURNS:  FAST
     COMMENTS:  This routine is responsible for setting the bits in the
                SIO's delta and status member as follows:
                     bit       status        delta
                     0          cts           cts
                     1          dsr           dsr
                     2          ri            ri
                     3          dcd           dcd
                     4          gpi1          gpi1
*/

#include <sio/siodef.h>

FAST _vstat232(register SIO *siop, struct vin232_ *p232)
{
     static FAST stat_reg;

     stat_reg = (*siop->readuint8_t)(siop->uart_base +  p232->offset);
     siop->delta.reg232 = stat_reg &0x0F;  /* mask off status, store deltas */
     siop->status.reg232 = (stat_reg &0xF0) >> 4;   /* store status bits */
     return stat_reg;
}

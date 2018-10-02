/*-

FUNCTION NAME:  _vsetbits
        LEVEL:  1
 PROTOTYPE IN:  U16X50.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  This is the primitive to write the format in the virtual
                register to the corresponding UART register.
      RETURNS:  void
     COMMENTS:  This function is called only by vsetbits.
*/

#include "sio/siodef.h"


void _vsetbits(register SIO *siop, struct vregbits_ *brp, REG binval)
{
     (*siop->writeuint8_t)(siop->uart_base + brp->offset, (FAST) binval);
}

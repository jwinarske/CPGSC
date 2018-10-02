/*-
FUNCTION NAME:  _vset232
        LEVEL:  1
 PROTOTYPE IN:  U16X50.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  Writes the virtual register containing the selected
                RS232 output pin to the corresponding UART register.
      RETURNS:  void
     COMMENTS:  This function is called only by vset232.
*/

#include "sio/siodef.h"

void _vset232(register SIO *siop, struct vout232_ *p232, REG binval)
{
     (*siop->writeuint8_t)(siop->uart_base + p232->offset, (FAST) binval);
}

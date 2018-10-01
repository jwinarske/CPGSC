/*-
FUNCTION NAME: isr_serr
        LEVEL: 1
 PROTOTYPE IN: U16X50.H
      LIBRARY: U16x50.LIB
  DESCRIPTION: Serial error interrupt handler.

     RETURNS : void
     COMMENTS: When an interrupt occurs, this function reads Line Status
               register, then one by one masks and copies the next
               four bits into the SIO variables. For portability, this
               routine is also  responsible for setting the bits in
               the SIO's s_errors  union as follows:

              Error     Overrun   Parity  Framing   BREAK
              Bit          0        1        2        3

*/


#include <sio/siodef.h>
#include <sio/U16x50.H>

void isr_serr(register SIO* siop)
{
     static short err_reg;
     err_reg = (*siop->readuint8_t)(siop->uart_base + SER_STAT);
     siop->serr.s_errors |= ((err_reg >> 1) & 0x0F);    /* store as bit map */
//     siop->serr.bitmap.overrun = (err_reg >> 1) &1;   /* bit 1 */
//     siop->serr.bitmap.parity  = (err_reg >> 2) &1;
//     siop->serr.bitmap.frame   = (err_reg >> 3) &1;
//     siop->serr.bitmap.Break   = (err_reg >> 4) &1;   /* bit 4 */
}

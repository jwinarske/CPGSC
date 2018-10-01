/*-
FUNCTION NAME: isr_stat232
        LEVEL: 1
 PROTOTYPE IN: U16X50.H
      LIBRARY: U16x50.LIB
  DESCRIPTION: RS232 status interrupt handler.
     RETURNS : void
     COMMENTS: When an interrupt occurs, this function reads RS232 Status
               register (aka Modem Status Register), then stores bits 0-3
               as deltas, bit 4-7 as status bits, then one-by-one masks and
               copies 4-7 into individual SIO variables. This routine is also
               responsible for setting the bits in the SIO's delta and
               status member as follows:

                        bit       status            delta
                        0          cts               cts
                        1          dsr               dsr
                        2          ri                ri
                        3          dcd               dcd
                        4          gpi1              gpi1
                        5          gpi2              gpi2
*/

#include <sio/siodef.h>
#include <sio/u16x50.h>

void isr_stat232(register SIO* siop)
{
     static short stat_reg;
     stat_reg = (*siop->readuint8_t)(siop->uart_base + STAT_232);
     siop->delta.reg232 = stat_reg &0x0F;  /* mask off status, store deltas */
     siop->status.reg232 = (stat_reg &0xF0) >> 4;   /* store status bits */
//     siop->cts->now = siop->status.bitmap.cts;
//     siop->dsr->now = siop->status.bitmap.dsr;
//     siop->ri ->now = siop->status.bitmap.ri;
//     siop->dcd->now = siop->status.bitmap.dcd;
     siop->cts->now = (stat_reg >> 4) &1;    /* bit 4 */
     siop->dsr->now = (stat_reg >> 5) &1;
     siop->ri ->now =  (stat_reg >> 6) &1;
     siop->dcd->now = (stat_reg >> 7) &1;    /* bit 7 */
}

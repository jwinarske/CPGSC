/*-
FUNCTION NAME:  serr_ioff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Disables UART transmitter interrupts.
      RETURNS:  short: Always returns OFF.
*/

#include "sio/siodef.h"      /* for constants */
#include "sio/buos.h"        /* for s_txempty */
#include "sio/uart.h"      /* for s_revector*/

short serr_ioff(SIO *siop)
{
    s_revector(siop, SERERR, siop->old_isr_serr );   /* restore old handler */
    u_intrpt_mgr(siop, SERERR, OFF);                /* UART interrupt on */
    return OFF;
}

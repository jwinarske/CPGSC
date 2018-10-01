/*-
FUNCTION NAME:  serr_ion
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Enables UART serialization interrupts.
     RETURNS:   short: Always returns ON.
*/

#include <sio/siodef.h>      /* for constants */
#include <sio/buos.h>        /* for s_txempty */
#include <sio/uart.h>      /* for s_revector*/

short serr_ion(SIO *siop)
{
    if (siop->intrpt_status.serr_on == ON)
        return ON;
    siop->old_isr_serr = s_revector(siop, SERERR, isr_serr); /* isr handler */
    u_intrpt_mgr(siop, SERERR, ON);                 /* UART interrupt on */
    return ON;
}

/*-49
FUNCTION NAME:  rs232_ioff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Disables UART RS232 input interrupts.
      RETURNS: short: Always returns OFF.
*/

#include <sio\siodef.h>      /* for constants */
#include <sio\buos.h>        /* for s_txempty */
#include <sio\uart.h>      /* for s_revector*/

short rs232_ioff(SIO *siop)
{
     s_revector(siop, RS232, siop->old_isr_232 );     /* restore old handler */
     u_intrpt_mgr(siop, RS232, OFF);                /* UART interrupt off */
     siop->read232 = _vstat232;                  /* restore polling funtion  */
     return OFF;
}


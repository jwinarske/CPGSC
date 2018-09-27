/*-
FUNCTION NAME:  rs232_ion
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Enables UART transmitter interrupts.
      RETURNS:  short: Always returns ON.
*/

#include <sio\siodef.h>      /* for constants */
#include <sio\buos.h>        /* for s_txempty */
#include <sio\uart.h>      /* for s_revector*/

short rs232_ion(SIO *siop)
{
     if (siop->intrpt_status.rs232_on == ON)                 /* already on */
         return ON;
     siop->read232 = NIL;               /* disable the polling funtion  */
     siop->old_isr_232 = s_revector(siop, RS232, isr_stat232);/* ISR subhandler*/
     u_intrpt_mgr(siop, RS232, ON);                  /* UART interrupt on */
     return ON;
}


/*-
FUNCTION NAME:  rcv_ioff
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Disables UART receiver interrupts.
      RETURNS: short: Always returns OFF.
*/

#include <malloc.h>      /* for constants */
#include <sio/siodef.h>      /* for constants */
#include <sio/buos.h>        /* for s_txempty */
#include <sio/uart.h>      /* for s_revector*/

short rcv_ioff(SIO *siop)
{
     s_revector(siop, RXRDY, siop->old_isr_rcv );     /* restore old handler */
     free((VOID*)siop->rcv_buff);                     /* free ring buffer    */
     siop->s_rstat = s_rcvstat;               /* restore poll status funct   */
     siop->s_read  = s_rcv;                   /* restore poll read funct     */
     siop->intrpt_status.rcv_on  = FALSE;
     u_intrpt_mgr(siop, RXRDY, OFF);                   /* UART interrupt off */
     return OFF;
}

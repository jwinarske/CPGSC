/*-58
FUNCTION NAME:  rcv_ion
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Enables UART receiver interrupts.
     RETURNS:  short: ON if successful; otherwise OFF.
*/

#include <malloc.h>      /* for constants */
#include <sio/siodef.h>      /* for constants */
#include <sio/buos.h>        /* for s_txempty */
#include <sio/uart.h>      /* for s_revector*/

short rcv_ion(SIO *siop)
{
    if (siop->intrpt_status.rcv_on == ON)                   /* Already on */
        return ON;

    siop->rcv_buff  = (FAST*)malloc(siop->rcv_buffsize * sizeof(FAST));

    if (siop->rcv_buff == NIL)                           /* If malloc fails */
        return OFF;

    /* initialize pointers */
    siop->rcv_headp  = siop->rcv_tailp = siop->rcv_buff;
    siop->rcv_buffend = siop->rcv_buff + siop->rcv_buffsize;

    /* swap pointers in SIO */
    siop->s_rstat = s_ircvstat;
    siop->s_read  = s_ircv;
    if (siop->rcv_fifo_depth > 1) {
        /* If 16550, install two sub handlers */
        s_revector(siop, RXTIMEOUT, isr_rcv450);   
    //       siop->old_isr_rcv = s_revector(siop, RXRDY, isr_rcv550);
        siop->old_isr_rcv = s_revector(siop, RXRDY, isr_rcv450);
    }
    else                             /* If 16450, install one sub handler */
    siop->old_isr_rcv = s_revector(siop, RXRDY, isr_rcv450);
    s_clearerr(siop);                               /* Clear garbage */
    u_intrpt_mgr(siop, RXRDY, ON);                  /* UART interrupt on */

    return ON;
}

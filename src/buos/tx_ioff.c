/*-
FUNCTION NAME: tx_ioff
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Disables UART transmit interrupts and restores pointers,
               vectors, and frees memory.
      RETURNS: short: Always returns OFF.
     COMMENTS: Mode argument causes either an immediate shutdown or
               causes a wait for the queue to empty and the last uint8_t
               to clear the UART. (s_txempty is a macro in uart.h)
*/


#include <malloc.h>
#include <sio/siodef.h>      /* for constants */
#include <sio/buos.h>        /* for s_txempty */
#include <sio/uart.h>        /* for s_revector*/


short tx_ioff(SIO *siop, short mode)
{
    short i;
    if (mode == WAIT_TIL_FINISH)  /* Gentle shutdown */
        while(!siop->tx_idle || !s_txempty(siop) )
            {;}         /* CAUTION: compiler optimizer may toss this! */

    u_intrpt_mgr(siop, THRE, OFF);               /* UART interrupt off */
    s_revector(siop, THRE, siop->old_isr_tx); /* ... restore old handler */ /* (void*) */
    /* clean up heap */
    for (i = 0; i < siop->tx_numbuffs; ++i)    
        free(siop->tx_list[i].locbuff);              /* release the buffers.... */
    free(siop->tx_list);                              /* ... release the queue */
    siop->tx_queue_end = siop->tx_headp = NIL;       /*... nul out ... */
    siop->tx_tailp     = NIL;                       /*... pointers.... */

    siop->s_xstat   = s_xmitstat;          /* restore the poll I/O pointers */
    siop->s_send    = s_xmit;
    siop->s_txblock = tx_write;
    siop->tx_idle   = FALSE;               /* mark ready for action */
    
    return OFF;
}

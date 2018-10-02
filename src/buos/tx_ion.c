/*-48
FUNCTION NAME: tx_ion
        LEVEL: 2
 PROTOTYPE IN: BUOS.H
      LIBRARY: BUOS.LIB
  DESCRIPTION: Enables UART transmitter interrupts, allocates
               and initializes buffers.
     RETURNS:  short: ON if successful; otherwise OFF.
*/

#include <stdio.h>      /* for constants */
#include <malloc.h>      /* for constants */
#include "sio/siodef.h"      /* for constants */
#include "sio/buos.h"        /* for s_txempty */
#include "sio/uart.h"      /* for s_revector*/
#include "sio/level0.h"

#define Q_SIZE (numbuffs*sizeof(struct tx_queue))

short tx_ion(SIO *siop, short numbuffs, short bufflen)
{
    int i;
    char *guinea_pig;
    unsigned q_size, local_size;

    if (siop->intrpt_status.tx_on == ON)   /* already on */
        return ON;

    /* before beginning, test that there's enough heap */
    q_size = numbuffs * sizeof(struct tx_queue);
    local_size = bufflen * sizeof(char) * numbuffs;
    guinea_pig = (char*)malloc(q_size + local_size);
    if (guinea_pig == NIL)                     /* if malloc fails */
        return OFF;
    free (guinea_pig);                       /* ok, release it */

    /* yep, enough memory */
    siop-> tx_numbuffs = numbuffs;   /* publish */ 
    siop->tx_buffsize  = bufflen;    

    /* allocate memory for queue and buffers */
    siop->tx_list = (struct tx_queue *) malloc(Q_SIZE);
    for (i = 0; i < numbuffs; ++i)             /* initialize queue */
        {
        siop->tx_list[i].id        = i;         /*//*/
        siop->tx_list[i].locbuff   = (char *) malloc(siop->tx_buffsize);
        siop->tx_list[i].buffp     = siop->tx_list[i].locbuff;
        siop->tx_list[i].inuseflag = TX_FREE;
        siop->tx_list[i].buffcnt   = 0;
        }

//printf("id   &buff        &buffp        &inuseflag       &buffcnt\n");
//
//     for (i = 0; i < numbuffs; ++i)             /* initialize queue */
//          {
//          printf("%d  ", siop->tx_list[i].id);
//          printf("%lp\t", (char far *) &siop->tx_list[i].locbuff);
//          printf("%lp\t", (char far *) &siop->tx_list[i].buffp);
//          printf("%lp\t", (short far *) &siop->tx_list[i].inuseflag);
//          printf("%lp\n", (char far *) &siop->tx_list[i].buffcnt);
//          }

    siop->tx_headp = siop->tx_tailp = &siop->tx_list[0];

    /* mark end with first out-of-bounds member */
    siop->tx_queue_end = &siop->tx_list[numbuffs];
    siop->old_isr_tx   = s_revector(siop, THRE, isr_tx);
    u_intrpt_mgr(siop, THRE, ON);        /* UART interrupts on */
    
    /* change SIO pointers to interrupt ones */
    siop->s_xstat   = s_ixmitstat;
    siop->s_send    = s_ixmit;
    siop->s_txblock = tx_iwrite;
    __sys_disable();
    siop->tx_idle             = TRUE;
    siop->intrpt_status.tx_on = TRUE;
    __sys_enable();

    return ON;
}

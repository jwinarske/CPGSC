/* Dummy ISRs to handle spurious interrupts */

#include "sio/siodef.h"
#include "sio/u16x50.h"

void isr_tx_dummy(SIO *siop)
{ /* No code: reading INT_ID clears a the interrupt */  } 

void isr_serr_dummy(SIO *siop)
{     (*siop->readuint8_t)(siop->uart_base + SER_STAT);    }

void isr_stat232_dummy(SIO *siop)
{     (*siop->readuint8_t)(siop->uart_base + STAT_232);    }

void isr_rcv_dummy(SIO *siop)
{     (*siop->readuint8_t)(siop->uart_base + DATA_IO);     }

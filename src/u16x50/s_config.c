/*-
FUNCTION NAME:  s_config
        LEVEL:  1
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  Copies the contents of the 16x50's write registers into the
                virtual array for siop.  Detects the presence of a 16550 and
                stores its state in the virtual array.
      RETURNS:  void
*/

#include "sio/siodef.h"
#include "sio/u16x50.h"

/* copy physical UART regs into virtual regs */
void s_config(SIO *siop)
{
     FAST tmp;
     short i;
     tmp = (*siop->readuint8_t)(siop->uart_base + FMT) | 0x80;
     (*siop->writeuint8_t)(siop->uart_base + FMT,  tmp);
     siop->v_regp[VBAUDLO][USR] = (*siop->readuint8_t)(siop->uart_base + siop->br->offsetlo);
     siop->v_regp[VBAUDHI][USR] = (*siop->readuint8_t)(siop->uart_base + siop->br->offsethi);
     (*siop->writeuint8_t)(siop->uart_base + FMT, (uint8_t)(tmp & 0x7f) );
     siop->v_regp[VINT_EN][USR]   = (*siop->readuint8_t)(siop->uart_base + INT_EN);
     siop->v_regp[VFMT][USR]    = (*siop->readuint8_t)(siop->uart_base + FMT);
     siop->v_regp[VOUT232][USR] = (*siop->readuint8_t)(siop->uart_base + OUT232);
     for (i = 0; i < V_REG_SIZE; i++)  /* copy USR column into VIR column */
          siop->v_regp[i][VIR] = siop->v_regp[i][USR];

     siop->v_regp[VFIFO][USR] = 0;

     if ( (*siop->readuint8_t)(siop->uart_base + FIFO) & 0xC0 )  /* if fifo already on */
          siop->v_regp[VFIFO][USR] = 0x81;
     (*siop->writeuint8_t)(siop->uart_base + FIFO, 1);   /* turn on bit 1 of IIR */
     if ( (*siop->readuint8_t)(siop->uart_base + FIFO) & 0xC0 )
          {
          (*siop->writeuint8_t)(siop->uart_base + FIFO, TRIG_8);/* turn on fifo */
          siop->tx_fifo_depth    = 16;
          siop->tx_fifo_trigger  =  0;
          siop->rcv_fifo_depth   = 16;
          siop->rcv_fifo_trigger =  8;          
          }
      else
          {
          siop->tx_fifo_depth    = 1;         
          siop->tx_fifo_trigger  = 0;         
          siop->rcv_fifo_depth   = 1;         
          siop->rcv_fifo_trigger = 0;         
          }                                   
}

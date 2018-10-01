/*
FUNCTION NAME: u_intrpt_mgr
        LEVEL: 1
 PROTOTYPE IN: U16X50.H
      LIBRARY: U16X50.LIB
     RETURNS : void
  DESCRIPTION: Activates and deactivates 16x50 UART interrupts.
     COMMENTS: These routines work by reading the Interrupt Enable registers,
               flipping the appropriate bits, then writing the register back
               out.
*/

#include <sio/siodef.h>
#include <sio/u16x50.h>
#include <sio/level0.h>


void u_intrpt_mgr(SIO * siop, short int_wanted, bool state)
{
     REG  reg;
     MASK mask;
     switch (int_wanted)
          {
          case RXRDY :  mask = I_RXRDY;  break;
          case THRE  :  mask = I_THRE;   break;
          case SERERR:  mask = I_SERERR; break;
          case RS232 :  mask = I_RS232;  break;
              default:  break;
          }
     reg = (*siop->readuint8_t)(siop->uart_base + INT_EN);
     if (state == ON)
          reg |= mask;     /* set bit  */
     else
          reg &= ~mask;    /* clear bit */
     __sys_disable();
     (*siop->writeuint8_t)(siop->uart_base + INT_EN, reg);
     __sys_enable();
}

/*-


FUNCTION NAME:  s_iadmin
        LEVEL:  1
 PROTOTYPE IN:  U16X50.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  16x50 Interrupt administrator.  When called by the assembly
                interrupt handler, it reads the Interrupt Identification
                register to identify the event that requires service,
                then calls the correct interrupt service routine.
      RETURNS:  void
     COMMENTS:  Bits 4-7 of the Interrupt Identification register are not
                relevent, and Bit 0 is 0 when an event needs service.  After
                right-shifting one place, this value becomes an index into
                an array of function pointers.
*/

#include <sio/siodef.h>
#include <sio/u16x50.h>
#include <sio/buos.h>


void s_iadmin(SIO *siop)
{
     FAST index;
     for (EVER)  /* loop while there are interrupts */
          {
          index = (*siop->readuint8_t)(siop->uart_base + INT_ID) & INT_ID_MASK;
          if (index & 01)   /* bit 1 indicates interrupt pending */
               break;
          index >>= 1;                       /* adjust index                 */
          (*siop->isr[index])(siop);         /* call the correct handler     */
          }
}

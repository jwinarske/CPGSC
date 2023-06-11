/*-
FUNCTION NAME:  _vsetbr
        LEVEL:  1
 PROTOTYPE IN:  U16X50.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  Primitive for setting the baud rate.
      RETURNS:  void.
     COMMENTS:  The baud rate is changed by lobaud and hibaud to the
                16x50's LSB and MSB baud registers.  These registers
                can be addressed only if bit 7 in the Data Format
                register is  TRUE. After writing to these two
                registers, the original  contents of the Data Format
                register are restored.

*/
//#include <stdio.h>
#include <sio\siodef.h>

void _vsetbr(register SIO *siop, struct vbaud_ *brp, REG lobaud, REG hibaud)
{
     FAST tmpfmt;
     tmpfmt = (*siop->readbyte)(siop->uart_base + siop->par->offset) | 0x80;
     (*siop->writebyte)(siop->uart_base + siop->par->offset, tmpfmt);
     (*siop->writebyte)(siop->uart_base + brp->offsetlo, (FAST)lobaud);
     (*siop->writebyte)(siop->uart_base + brp->offsethi, (FAST)hibaud);
     (*siop->writebyte)(siop->uart_base + siop->par->offset, (FAST)(tmpfmt & 0x7f));
//     printf("high: %x     low:   %x\n", (FAST)hibaud, (FAST)lobaud);
}

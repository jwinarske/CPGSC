/*-
FUNCTION NAME:  s_restore
        LEVEL:  1
 PROTOTYPE IN:  U16X50.H
      LIBRARY:  U16x50.LIB
  DESCRIPTION:  Restores the SIO pointed to by siop to its
                original state.
      RETURNS:  void
*/

#include <sio\siodef.h>
#include <sio\U16x50.H>

void s_restore(register SIO *siop)
{
     _vsetbr(siop,siop->br,siop->v_regp[VBAUDLO][USR],
            siop->v_regp[VBAUDHI][USR]);
     _vsetbits(siop,siop->par,siop->v_regp[VFMT][USR]);
     (*siop->writebyte)(siop->uart_base + INT_EN, siop->v_regp[VINT_EN][USR]);
     (*siop->writebyte)(siop->uart_base + OUT232, siop->v_regp[VOUT232][USR]);
     (*siop->writebyte)(siop->uart_base + FIFO, siop->v_regp[VFIFO][USR]);
}

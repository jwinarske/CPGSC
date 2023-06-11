/*-
FUNCTION NAME: tx_write
  DESCRIPTION: Transmit a block of data using polled I/O.
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.H
      RETURNS: 0 (always successful)
*/

#include <sio\siodef.h>
#include <sio\buos.h>

short tx_write(SIO *siop, BYTE *newbuff, short count)
{
     while (count > 0)
          {
          s_putc(siop, *newbuff);
          --count;
          ++newbuff;
          }
     return 0;
}

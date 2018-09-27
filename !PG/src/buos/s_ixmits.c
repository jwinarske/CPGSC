/*-
FUNCTION NAME:  s_ixmitstat
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Interrupt equivalent of s_xmitstat.  Returns whether there
                is a room in the transmit queue.
     RETURNS :  FAST: Non-zero if there is room in the queue.
     COMMENTS:  This function is never called directly but through a function
                pointer in the SIO.
*/

#include <sio/siodef.h>

FAST s_ixmitstat(register SIO *siop)
{
     return (siop->tx_headp->inuseflag == TX_FREE);
}

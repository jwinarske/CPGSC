/*-
FUNCTION NAME:  s_ixmit
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  The interrupt equivalent of x_xmit.  Adds a uint8_t to
                the transmit interrupt queue via a call to tx_iwrite.
                This function is never called directly, but through a
                function pointer in the SIO.  
      RETURNS:  void
     COMMENTS:  Can be written as a macro.
*/


#include <stdio.h>
#include "sio/siodef.h"

void s_ixmit(register SIO *siop, FAST c)
{
    while (tx_iwrite(siop, (uint8_t*)&c, 1) != Q_OK)
        {;} 
}

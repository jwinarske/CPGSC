/*-
FUNCTION NAME: s_write
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.H
  DESCRIPTION: Transmit a block of data
     RETURNS : short: 0 if successful, non-zero otherwise.
     COMMENTS: Can be a macro.
*/

#include "sio/siodef.h"


short s_write(SIO *siop, uint8_t *newbuff, short count)
/* 2: pointer to buffer to send */
/* 3: count in buffer */
{
     return (*siop->s_txblock)(siop, newbuff, count);
}

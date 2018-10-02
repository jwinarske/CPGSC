/*-
FUNCTION NAME:  x_rcvcksum
        LEVEL:  0
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  See "Portability Considerations" in text.
  DESCRIPTION:  Verifies 8-bit arithmetic checksum on indicated buffer.
      RETURNS:  uint16_t: 0 if checksums agree.
     COMMENTS:  The checksum uint8 is assumed to be contiguous with the last
                uint8 of the data field.
*/

#include <stdio.h>                          /* Needed by modem.h                 */
#include "sio/siodef.h"
#include "sio/xmod.h"

/*1: pointer to rcvpacket->data        */

uint16_t x_rcvcksum(uint16_t *data)
{
     static int i;
     static uint16_t cksum;
     cksum = data[128];
     for (i = 0; i < DBLKSIZ ; ++i)
          cksum -= *data++;             /* subtract data uint8_ts from checksum */
     printf("CHECKSUM = %d",cksum);
     return (cksum & 0x00FF);
}

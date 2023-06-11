/*-
FUNCTION NAME:  x_rcvcksum
        LEVEL:  0
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  See "Portability Considerations" in text.
  DESCRIPTION:  Verifies 8-bit arithmetic checksum on indicated buffer.
      RETURNS:  USHORT: 0 if checksums agree.
     COMMENTS:  The checksum byte is assumed to be contiguous with the last
                byte of the data field.
*/

#include <stdio.h>                          /* Needed by modem.h                 */
#include <sio\siodef.h>
#include <sio\xmod.h>

/*1: pointer to rcvpacket->data        */

USHORT x_rcvcksum(USHORT *data)
{
     static int i;
     static USHORT cksum;
     cksum = data[128];
     for (i = 0; i < DBLKSIZ ; ++i)
          cksum -= *data++;             /* subtract data bytes from checksum */
     printf("CHECKSUM = %d",cksum);
     return (cksum & 0x00FF);
}

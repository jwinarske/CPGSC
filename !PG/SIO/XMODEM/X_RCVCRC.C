/*-

FUNCTION NAME:  x_rcvcrc
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMODEM.C
  DESCRIPTION:  Calulate CRC for a rcvpacket.
      RETURNS:  USHORT
     COMMENTS:  The CRC bytes in the rcvpacket are assumed to be
                contiguous with data bytes. The CRC (in accum) is zero
                if no errors occurred.
*/

#include <stdio.h>                             /* Needed by modem.h                 */
#include <sio\siodef.h>
#include <sio\crc.h>
#include <sio\xmod.h>

/*1: pointer to rcvpacket->data */

USHORT x_rcvcrc(USHORT *data)
{
     extern USHORT *crctblp;    /* pointer to the CRC lookup table   */
     static USHORT i, accum;
     for (accum = i = 0; i < DBLKSIZ+2; i++)    /* include CRC bytes as data */
          crcupdate(*data++, &accum, crctblp);
     printf("CRC = %d ", accum);
     return accum;                            /* zero if no errors         */
}

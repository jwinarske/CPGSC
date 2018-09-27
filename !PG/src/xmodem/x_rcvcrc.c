/*-

FUNCTION NAME:  x_rcvcrc
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMODEM.C
  DESCRIPTION:  Calulate CRC for a rcvpacket.
      RETURNS:  uint16_t
     COMMENTS:  The CRC uint8_ts in the rcvpacket are assumed to be
                contiguous with data uint8_ts. The CRC (in accum) is zero
                if no errors occurred.
*/

#include <stdio.h>                             /* Needed by modem.h                 */
#include <sio/siodef.h>
#include <sio/crc.h>
#include <sio/xmod.h>

/*1: pointer to rcvpacket->data */

uint16_t x_rcvcrc(uint16_t *data)
{
     extern uint16_t *crctblp;    /* pointer to the CRC lookup table   */
     static uint16_t i, accum;
     for (accum = i = 0; i < DBLKSIZ+2; i++)    /* include CRC uint8_ts as data */
          crcupdate(*data++, &accum, crctblp);
     printf("CRC = %d ", accum);
     return accum;                            /* zero if no errors         */
}

/*-
FUNCTION NAME:  x_sndcksum
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMOD.LIB
  DESCRIPTION:  Calculates and returns an arithmetic checksum on the buffer
                indicated.
      RETURNS:  uint16_t
*/
#include <stdio.h>                      /* Needed by modem.h                 */
#include <sio/siodef.h>
#include <sio/xmod.h>


/*1: pointer to sndpacket->data   */

uint16_t x_sndcksum(uint8 *buff)
{
     static int cksum, i;
     for (cksum = i = 0; i < 128; ++i)       /* round 'em up                 */
          cksum += *buff++;                  /* add 'em up                   */
     return (cksum & 0x00FF);                   /* take 'em back                */
}

/*-

FUNCTION NAME:  x_sndcrc
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  IBMPC.C
  DESCRIPTION:  Calulates CRC for indicated data block.
      RETURNS:  uint16_t
      OMMENTS:  This function is inherently non-portable because there is
                no way to know how the processor stores words.  As shown, the
                we assume that the processor stores the LSB lower in memory
                than the MSB.
*/

#include <stdio.h>                      /* Needed by modem.h                 */
#include <sio/siodef.h>
#include <sio/xmod.h>
#include <sio/crc.h>

/*1: pointer to sndpacket->data        */
uint16_t x_sndcrc(uint8_t *buff)
{
     extern uint16_t *crctblp;      /* pointer to lookup table         */
     static uint16_t accum;         /* CRC accumulator                 */
     static int i;
     for (accum = i = 0; i < DBLKSIZ; ++buff, ++i)
          crcupdate(*buff, &accum, crctblp);          /* macro in CRC.H is better */
     return ( (accum >> 8) +  (accum << 8) );    /* non-portable:  see text  */
}

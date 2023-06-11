/*-

FUNCTION NAME:  crchware
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Simulates CRC hardware circuit.
      RETURNS:  USHORT: the new CRC.
     COMMENTS:  Generates a CRC directly--produces the same remainder as
                polynomial division with 2 zero bytes appended to the
                message.
*/

#include <sio\siodef.h>

/*1: the generator polynomial          */
/*2: accumulator                       */


USHORT crchware(USHORT data,  USHORT genpoly,  USHORT accum)
{
     static int i;
     data <<= 8;                        /* data to high byte                 */
     for (i = 8; i > 0; i--)
          {
          if ((data ^ accum) & 0x8000) /* if msb of (data XOR accum) is TRUE */
               accum = (accum << 1) ^ genpoly;  /* shift and subtract poly   */
          else
               accum <<= 1;             /* otherwise, transparent shift      */
          data <<= 1;                   /* move up next bit for XOR          */
          }
     return accum;
}

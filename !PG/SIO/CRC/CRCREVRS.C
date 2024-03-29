/*-

FUNCTION NAME:  crcrevhware
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Simulates a "reverse" CRC hardware circuit.
      RETURNS:  USHORT.
     COMMENTS:  The generator polynomial in the argument list must already
                be reversed.
*/

#include <sio\siodef.h>


/*1: NOT a char                        */
/*2: the generator polynomial          */
/*3: accumulator                       */




USHORT crcrevhware(USHORT data, USHORT genpoly, USHORT accum)
{
     static int i;
     data <<= 1;                        /* in preparation for loop below     */
     for (i = 8; i > 0; i--)
          {
          data >>= 1;
          if ((data ^ accum) & 0x0001) /* if msb of (data XOR accum) is TRUE */
               accum = (accum >> 1) ^ genpoly;  /* shift and subtract poly   */
          else
               accum >>= 1;             /* otherwise, transparent shift      */
          }
     return accum;
}

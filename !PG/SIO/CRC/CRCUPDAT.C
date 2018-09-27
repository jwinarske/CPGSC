/*-

FUNCTION NAME:  crcupdate
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Calculates CRC using table-lookup method.
      RETURNS:  void
     COMMENTS:  Looks up the CRC of combining value in the table pointed to by
                crctab.
*/

#include <sio\siodef.h>


/*2: pointer to a CRC accumulator */
/*3: pointer to a table of CRC combining values */



void crcupdate(USHORT data, USHORT *accum, USHORT *crctab)
{
     static short comb_val;
     comb_val  = (*accum >> 8) ^ data;
     *accum = (*accum << 8) ^ crctab[comb_val];
}

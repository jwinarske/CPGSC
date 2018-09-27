/*-

FUNCTION NAME:  crcrevupdate
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Calculates "reverse" CRC-16 on data byte passed using
                the lookup table.
      RETURNS:  void
     COMMENTS:  The genpoly is applied in the form it is passed.  For
                CRC-16, therefore, A001 (inverse CRC-16) must be passed.
*/

#include <sio\siodef.h>


void crcrevupdate(USHORT data, USHORT *accum, USHORT *crcrevtab)
{
     static int comb_val;
     comb_val   = *accum ^ data;
     *accum = (*accum >> 8) ^ crcrevtab[comb_val & 0x00ff];
}

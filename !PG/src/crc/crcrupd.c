/*-

FUNCTION NAME:  crcrevupdate
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Calculates "reverse" CRC-16 on data uint8_t passed using
                the lookup table.
      RETURNS:  void
     COMMENTS:  The genpoly is applied in the form it is passed.  For
                CRC-16, therefore, A001 (inverse CRC-16) must be passed.
*/

#include <sio/siodef.h>


void crcrevupdate(uint16_t data, uint16_t *accum, uint16_t *crcrevtab)
{
     static int comb_val;
     comb_val   = *accum ^ data;
     *accum = (*accum >> 8) ^ crcrevtab[comb_val & 0x00ff];
}

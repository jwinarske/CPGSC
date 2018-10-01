/*-

FUNCTION NAME:  polydiv
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Simulates longhand polynomial division.
      RETURNS:  uint16_t
     COMMENTS:  This function produces a remainder, not a CRC.
*/

#include <sio/siodef.h>


uint16_t polydiv(uint16_t data, uint16_t divisor, uint16_t remainder)
{
    static  uint16_t quotient, i;
    for (i = 8; i > 0; i--) {

        quotient = remainder & 0x8000;/* remember if bit 15 is set         */
        remainder <<= 1;              /* shift remainder; bit 0 = 0        */
        if ( (data <<= 1) & 0x0100)   /* shift data; if old bit 7 was 1    */
            remainder |= 1;          /* put into bit 0 of remainder       */
        if (quotient)                 /* if divisible                      */
            remainder ^=  divisor;   /* subtract polynomial               */
    }
    return remainder;
}

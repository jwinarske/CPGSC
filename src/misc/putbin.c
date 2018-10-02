/*-
FUNCTION NAME:  putbin
 PROTOTYPE IN:  MISC.H
        LEVEL:  3
      LIBRARY:  MISC.LIB
  DESCRIPTION:  Displays 16-bit integer in binary.
      RETURNS:  void
     COMMENTS:  Newline at the end is to accommodate program in
*/

#include  <stdio.h>
#include "sio/siodef.h"


/*1: 16 bit int */
void putbin(uint16_t data)
{
     uint16_t shifter = 0x8000;
     for (; shifter > 0; shifter >>= 1)
          putchar((data & shifter) ? '1' : '0');
     putchar('\n');
}

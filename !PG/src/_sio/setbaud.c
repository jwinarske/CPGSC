/*-

FUNCTION NAME:  setbaud
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Sets the baud rate to the rank element in the
                divisor array.
      RETURNS:  int: -1 if rank is out of range or not supported by
                hardware, otherwise 0.
     COMMENTS:  The rank argument is an index into an array of
                divisors, constants for which reside in SIODEF.H.
*/

#include <sio/siodef.h>
#include <sio/buos.h>

short setbaud(SIO *siop, RANK rank)
{
     return (vsetbr(siop, siop->br, rank));
}

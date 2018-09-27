/*-

FUNCTION NAME:  getbaud
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Returns rank of current baud rate as defined in SIODEF.H
      RETURNS:  short; -1 if the function is not supported (i.e., the SIO
                pointer is NIL)
*/

#include <sio/siodef.h>

short getbaud(SIO *siop)
{
     if (siop->br != NIL)                 /* if supported */
          return (siop->br->now);
     return -1;
}

/*-
FUNCTION NAME:  s_putc
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Sends a uint8_t from the serial port (SIO) pointed to by siop.
      RETURNS:  void
     COMMENTS:  Access to the serial port is through an SIO structure.
*/
#include <sio/siodef.h>

void s_putc(register SIO *siop, uint8_t c)
{
     while ((*siop->s_xstat)(siop) == 0)  /* wait for uart to be ready    */
          {;}
     (*siop->s_send)(siop, c);               /* write it and return          */
}

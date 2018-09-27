/*-

FUNCTION NAME:  s_puts
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Transmit string from SIO without control through the
                soctl_ structure.
      RETURNS:  void
*/


#include <sio/siodef.h>
#include <sio/buos.h>


void s_puts(SIO *siop, char *str)
{
     while (*str != '\0')
          s_putc(siop, *str++);
}

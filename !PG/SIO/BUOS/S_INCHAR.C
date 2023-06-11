/*-
FUNCTION NAME:  s_inchar
        LEVEL:  2 (or MACRO)
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Fetches a byte from the serial port (SIO) pointed to by siop
                if one is ready; otherwise returns.
      RETURNS:  int:  the byte if one is ready, otherwise -1.
     COMMENTS:  The function can also be written as a macro in STDIO.H:
*/

#include <sio\siodef.h>

int s_inchar(SIO *siop)
{
     if ((*siop->s_rstat)(siop) & siop->rcv_vflowstate)
          return ((*siop->s_read)(siop));
     return -1;
}

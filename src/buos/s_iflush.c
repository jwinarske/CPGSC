/*-
FUNCTION NAME:  s_iflush
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Returns pending uint8_t from s_octl's "look-back" buffer.
      RETURNS:  int:  uint8_t if available, otherwise -1;
*/

#include <sio/siodef.h>

int s_iflush(SIO *siop)
{
    return ((siop->s_ictl->rbakflag) ? siop->s_ictl->rbakc : -1);
}

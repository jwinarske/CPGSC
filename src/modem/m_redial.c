/*-
FUNCTION NAME:  m_redial
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Redial previously dialed number.
      RETURNS:  int: response code as described in SIODEF.H.
     COMMENTS:  The previously dialed number was left in the modem
                structure by m_dial.
*/

#include "sio/siodef.h"
#include "sio/modem.h"

int m_redial(SIO *siop)
{
     return (m_dial(siop, siop->sm->dialbuff));
}

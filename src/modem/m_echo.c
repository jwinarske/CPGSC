/*-
FUNCTION NAME:  m_echo
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Turns modem echo on or off conditional on existence of
                carrier and the presence of a configured modem.
                structure.
      RETURNS:  void
     COMMENTS:
*/

#include <sio/siodef.h>
#include <sio/modem.h>
#include <sio/sioctl.h>

void m_echo(SIO * siop, bool state)
{
     if ( siop->sm->configokflag && (!stat232(siop, GET)))
          m_cmd_OK(siop, (state == OFF) ? "E0" : "E1");
}

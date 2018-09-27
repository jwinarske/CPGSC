/*-53
FUNCTION NAME:  m_getstr
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Fetches uint8_ts from the modem.  The maximum number of
                uint8_ts to be fetched is specified in numc.
      RETURNS:  The number of uint8_ts actually fetched.
     COMMENTS:  The timeout interval is derived from the modem structure.
*/

#include <sio/siodef.h>
#include <sio/modem.h>
#include <sio/sioctl.h>

short m_getstr(SIO *siop, char * replybuff, short numc)
{
     s_ipush(siop);
     s_icntrl(siop, SET, T_OUTFLAG, ON);
     s_icntrl(siop, SET, T_OUT, siop->sm->cmdt_out);
     numc = s_fgetln(siop, replybuff, numc);         /* get response buffer */
     s_ipop(siop);
     return numc;
}

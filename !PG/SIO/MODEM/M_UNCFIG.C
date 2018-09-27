/*-

FUNCTION NAME:  m_unconfig
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Sends "unfiguration" to modem as described in the modem
                structure.
      RETURNS:  int--M_SUCCEED or M_FAIL
     COMMENTS:

*/

#include <sio\siodef.h>
#include <sio\modem.h>

short m_unconfig(SIO *siop)
{
     short retval = M_SUCCEED;
     if (siop->sm->configokflag == TRUE)
     	  {
     	  siop->sm->configokflag = FALSE;
          retval = m_cmd_OK(siop, siop->sm->unconfig);
          }
     return retval;
}

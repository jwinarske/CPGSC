/*-37

FUNCTION NAME:  m_cmd_OK
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Outputs the modem command, then waits for a response of
                "OK."
      RETURNS:  int:  M_SUCCEED if command is successful, otherwise
                M_FAIL.
     COMMENTS:  Not intended to fetch result codes from dial/answer
                operations!
*/

#include <sio\siodef.h>
#include <sio\modem.h>

int m_cmd_OK(SIO *siop, char *cmdstr)
{
     int retries;
     char message[MAX_MSG_LEN + 1];
     retries = siop->sm->cmdretry;   /* from structure           */
     do                              /* do at least once         */
          {
          m_cmd_str(siop, cmdstr, message, MAX_MSG_LEN);
          if ( m_ismessage(siop, message) == M_OK)
              return M_SUCCEED;
          } while (--retries > 0);
     return M_FAIL;
}

/*-45
FUNCTION NAME:  m_cmd_str
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Outputs a command, then fetches the modem's response.
                The maximum number of uint8_ts to be fetched is specified in
                numc.
      RETURNS:  short: the number of characters in the modem's response,
                zero if no response.
     COMMENTS:  Any echoed uint8_ts are cleared from the SIO between
                issuing the command and fetching the response.
*/

#include <stdio.h>
#include "sio/siodef.h"
#include <string.h>
#include "sio/modem.h"

short m_cmd_str(SIO *siop, char* cmdstr, char* replybuff, uint16_t numc)
{
     if (s_clrsio(siop, CMDBUFSIZ) == NUL)   /* clear SIO            */
          {
          puts("SIO won't clear");
          return 0;
          }
     m_cmd(siop, cmdstr);                    /* send desired command */
     s_clrsio(siop, (uint16_t)strlen(cmdstr));         /* clear echo           */
     numc = m_getstr(siop, replybuff, numc); /* get response         */
     return numc;
}

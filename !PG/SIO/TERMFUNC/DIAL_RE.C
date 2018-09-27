/*-
FUNCTION NAME:  dial and redial
        LEVEL: 3
 PROTOTYPE IN:  TERM.H
  DESCRIPTION:  Dials or redial telephone number on the modem.
*/

#include <stdio.h>
#include <sio\siodef.h>
#include <sio\modem.h>

int dial(SIO *siop)
{
     extern char *m_codes[];
     int result;
     char numbuff[CMDBUFSIZ +1];
     printf("\nEnter phone number:  ");
     gets(numbuff);
     result = m_dial(siop, numbuff);
#ifdef DEBUG_MODEM
     printf("DIAL: %s.  (%d)\n",m_codes[result], result);
#endif
     return result;
}

int redial(SIO *siop)
{
     printf("\nRedialing previous number:  %s\n",siop->sm->dialbuff);
     return (m_redial(siop));
}
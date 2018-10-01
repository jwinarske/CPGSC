/*-45
FUNCTION NAME:  m_dial
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Dials the number specified and waits for return a result code.
      RETURNS:  int: result code returned from dial operation.
     COMMENTS:  The duration of the wait for the response is given in
                the dcdwait structure member.  The filtered dial
                string is built into the modem structure for use by
                redial.
*/

#include <stdio.h>
#include <ctype.h>
#include <sio/siodef.h>
#include <sio/ascii.h>
#include <string.h>
#include <sio/buos.h>
#include <sio/modem.h>

int m_dial(SIO *siop, char  phonenum[])
{
     struct modem *smp = siop->sm;
     int  resultcode;
     char dialstr[CMDBUFSIZ];                /* build dial command here      */
     char *dbp = smp->dialbuff;
     do                                      /* filter string                */
          {
          if (isdigit(*phonenum) || strchr(smp->okalpha, *phonenum))
               *dbp++ = *phonenum;           /* copy and validate chars      */
          } while( *++phonenum != NUL );
     *dbp = '\0';                            /* terminate  buffer            */
     sprintf(dialstr,"D%c%s%c",smp->dialmode, smp->dialbuff, smp->enddial);
     printf("Dial string is %s\n",dialstr);  /*//*/
     if (strlen(smp->dialbuff) == 0)         /* exit if string is NIL        */
          return M_NILNUM;
     set232(siop, DTR, ON);
     m_cmd(siop, dialstr);                   /* output command to SIO        */
     resultcode = m_wait4dcd(siop);          /* go wait for carrier          */
//     printf("M_DIAL: resultcode = %d\n", resultcode);  /*//*/

     switch (resultcode)
          {
          case M_NODCD:                      /* no carrier (or timeout)      */
          case M_NOTONE:                     /* no dial tone heard           */
          case M_BUSY:                       /* busy signal heard            */
          case M_NOANSW:                     /* silence not heard after @    */
               set232(siop, DTR, OFF);       /* return to command state      */
               break;
          case M_USRCAN:                     /* call cancelled from keyboard */
               set232(siop, DTR, OFF);       /* return to command state      */
               s_putc(siop, SP);             /* cancel call                  */
               break;
          default:;
          }
     return resultcode;                      /* exit with DTR still high     */
}

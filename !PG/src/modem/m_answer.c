/*-49
FUNCTION NAME:  m_answer
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Answers incoming call.
      RETURNS:  int: integer response code from m_wait4dcd.
     COMMENTS:  The duration of the wait for carrier is given in
                the dcdwait structure member.  Waits for a RING message
                from the modem before sending answer command.
*/

#include <stdio.h>
#include <sio/siodef.h>
#include <sio/buos.h>
#include <sio/level0.h>
#include <sio/modem.h>

int m_answer(SIO *siop)
{
     int anscode, tmptime;
     char ringmsg[MAX_MSG_LEN + 1];
     siop->sm->cmdt_out = _1_SEC_0 * 10;         /* long time between rings  */
     s_clrsio(siop, CMDBUFSIZ);
     set232(siop, DTR, ON);
     printf("\nWaiting for RING.....\n");
     m_getstr(siop, ringmsg, MAX_MSG_LEN);       /* fetch relply             */
     siop->sm->cmdt_out = tmptime;               /* restore command time out */
     if (m_ismessage(siop, ringmsg) != M_RING)   /* wrong response           */
          return M_NORING;
     __delay (_0_SEC_3);                         /* superstitious wait       */
     printf("Ring Detected: Answering...\n");
     m_cmd(siop,"A");                            /* ok to send answer cmd    */
     anscode = m_wait4dcd(siop);
     switch (anscode)
          {
          case M_USRCAN:
               s_putc(siop, SPACE);
          case M_NODCD:
               set232(siop, DTR, OFF);
          }
     return anscode;
}

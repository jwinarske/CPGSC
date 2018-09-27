/*-42

FUNCTION NAME:  m_gocmd
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Forces modem from online to command state.
      RETURNS:  int: M_SUCCEED if modem exits to online command state.
     COMMENTS:  Three "escape" characters are sent, surrounded by the quiet
                interval given by the modem structure member
                guardtime.
*/

#include <stdio.h>
#include <sio\siodef.h>
#include <sio\sioctl.h>
#include <sio\buos.h>
#include <sio\level0.h>
#include <sio\modem.h>

int m_gocmd(SIO *siop, int escchar)
{
     char msgbuff[MAX_MSG_LEN+1];
     int time_tmp, errcode = M_FAIL;
     s_ipush(siop);
     __delay(siop->sm->guardtime);        /* silence on front end    */
     s_fputc(siop, escchar);              /* send three escape chars */
     s_fputc(siop, escchar);
     s_fputc(siop, escchar);
     time_tmp = siop->sm->cmdt_out;       /* save time out           */
     siop->sm->cmdt_out =  _1_SEC_0 * 5;  /* extend wait for OK      */
	 if (m_getstr(siop, msgbuff, MAX_MSG_LEN))
     	errcode = m_ismessage(siop, msgbuff);
     siop->sm->cmdt_out = time_tmp;       /* restore normal timeout  */
     s_ipop(siop);
     return (errcode == M_SUCCEED) ? M_SUCCEED : M_FAIL;
}

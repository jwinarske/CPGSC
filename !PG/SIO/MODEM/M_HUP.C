/*-49

FUNCTION NAME:  m_hup
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Hangs up phone.
      RETURNS:  int:  M_SUCCEED or M_FAIL
     COMMENTS:  If DCD indicates that a connection is in progress,
                an online escape command is issued to force the modem
                to command mode where an explicit hangup command can be
                issued. If this operation fails, DTR is inhibited to
                force hangup.
*/

#include <stdio.h>                               /*//*/
#include <stdlib.h>
#include <sio\siodef.h>
#include <sio\level0.h>                          /* for timing constants   */
#include <sio\modem.h>

int m_hup(SIO *siop)
{
    int time_tmp, errcode = 0;                   /* initialize this !      */
    if (stat232(siop, DCD))                      /* if DCD is asserted     */
         {
     	 time_tmp = siop->sm->cmdt_out;          /*save time out           */
     	 siop->sm->cmdt_out =  _1_SEC_0 * 1;     /* extend wait for OK     */
         errcode = m_gocmd(siop, siop->sm->escape_arg); /* onlinecmd state */
		 if (errcode != M_SUCCEED)
         	errcode = m_gocmd(siop, '+');        /* default online char    */
         errcode = m_cmd_OK(siop, "H0");         /* send hangup  cmd       */
         siop->sm->cmdt_out = time_tmp;          /* restore normal timeout */
         }
//    printf ("M_HUP: errcode = %d\n",errcode);      /*//*/
    set232(siop, DTR, OFF);
    __delay(_0_SEC_3);
    return errcode;
}

/*-39

FUNCTION NAME:  m_reset
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Attempts to reset the modem to default condition.
      RETURNS:  int: M_SUCCEED if reset is successful; M_FAIL
                if user aborts.
     COMMENTS:  Resetting +++ when online takes up to a minute,
                depending upon AT speed of modem.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sio\siodef.h>
#include <sio\ascii.h>
#include <sio\misc.h>
#include <sio\key.h>
#include <sio\level0.h>
#include <sio\modem.h>


int m_reset(SIO *siop)
{
     extern char *brstr[];
     struct modem *smp = siop->sm;
     int  i, j, errcode, user_redo;
     int  tmptries, tmptime;           /* temporary storage                 */
     puts("Entering M_RESET");
     s_clrsio(siop, CMDBUFSIZ);        /* clear SIO of garbage              */
     tmptime  = smp->cmdt_out;         /* save command response time out    */
     set232(siop, DTR, OFF);           /* inhibit DTR to force comatose mode*/
     __delay(_0_SEC_3);                /* a bit of DTR delay                */
     set232(siop, DTR, ON);            /* assert DTR to enable command mode */
     tmptries = smp->cmdretry;         /* save number of retries            */
     smp->cmdretry = 1;                /* make m_cmd_OK retry only once     */
     user_redo = FALSE;                /* TRUE = try online escape ('+++')  */
     for(EVER)                         /* only reset or user can end loop   */
          {
          for (i = 0; smp->baudtry[i] != -1; ++i) /* at every listed rate */
               {
               setbaud(siop, smp->baudtry[i]);
               printf("Trying Reset at %s\n", brstr[smp->baudtry[i]]);
               for (j = tmptries; j > 0; --j) /* reset command     */
                    {
                    if (user_redo && j <= 2) /* 2nd time through  */
                         {
                         m_gocmd(siop, '+');  /* default esc char  */
                         errcode = m_cmd_OK(siop, "H0"); /* hangup command    */
                         if (errcode != M_SUCCEED)
                            {
						    if (smp->escape_arg != '+')
                                 m_gocmd(siop,smp->escape_arg);
                         	m_gocmd(siop,smp->escape_arg);
                         	m_cmd_OK(siop, "H0"); /* hangup again */
                         	set232(siop, GPO1, ON); /* If PC card modem */
                         	__delay(_0_SEC_05);  /* leave on a while */
                         	set232(siop, GPO1, OFF);
                         	}
                         }
                    if ( (errcode = m_cmd_OK(siop, "")) == M_SUCCEED)
                         {             /* If modem says OK to AT            */
                         smp->max_DTE_baud = smp->baudtry[i]; /* save rate */
                         goto EXIT;
                         }
                    }
               }
          puts("\a\nModem won't reset. Press any key to retry, ESC to quit");
          if (getkbch() == ESC)
               {
               errcode = M_USRCAN;
               goto EXIT;
               }
          if (user_redo == FALSE)      /* next time, try online escape      */
               user_redo = !user_redo;
          }
EXIT:
     if (errcode == M_SUCCEED)
          {
          smp->cmdt_out = _1_SEC_0 * 3; /* at least 3 secs for reset */
          errcode = m_cmd_OK(siop, "Z");
          }
     set232(siop, DTR, OFF);
     smp->cmdt_out = tmptime;          /* restore from temporaries          */
     smp->cmdretry = tmptries;
     printf("Exiting M_RESET with return code of %d\n", errcode);
     return errcode;
}

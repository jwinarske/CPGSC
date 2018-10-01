/*-44

FUNCTION NAME:  m_wait4dcd
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Evaluates stream of modem messages until a 'terminal'
                message is received, DCD is asserted, or the command
                is terminated from the keyboard.
                RETURNS:  int:  an integer code to describing the result of dialing.
     COMMENTS:  The duration of the wait for carrier is determined by
                the modem's S7 register (set by m_config).
*/

#include <stdio.h>                          /*//*/
#include <string.h>                         /*//*/
#include <sio/siodef.h>
#include <sio/sioctl.h>
#include <sio/modem.h>

int m_wait4dcd(SIO *siop)
{
     extern char *brstr[];                  /* baud codes to strings                 */
     short retcode;
     char waitbuff[MAX_MSG_LEN + 1];
     struct modem *smp = siop->sm;
     s_clrsio(siop, CMDBUFSIZ);
     s_ipush(siop);
     s_icntrl(siop, SET, T_OUTFLAG, ON);    /* turn on timeout mode                  */
     s_icntrl(siop, SET, T_OUT, _0_SEC_2);  /* timeout for s_fgets                   */
/* bait baud/link protocol/compression variables */
     smp->connect_XXXX_code = getbaud(siop);
     smp->carrier_baud_code = getbaud(siop);
     strcpy (smp->compressname, "NONE");
     strcpy(smp->linkname, "NONE");
     retcode = MSG_NON_TERMINAL ;           /* initialize like this! *               */

     while (retcode == MSG_NON_TERMINAL)    /* timeout or non-terminal               */
          {
          if (s_fgetln(siop, waitbuff, MAX_MSG_LEN) != TIMEOUT)
               retcode = m_ismessage(siop, waitbuff);
          else if (stat232(siop, DCD))      /* if timeout and DCD is high            */
               retcode = M_DCD_HIGH;        /* connect phase is over                 */
          else if (retcode == MSG_INVALID)
               retcode = M_BADMSG;
          if (s_keybort(siop))
               retcode = M_USRCAN;          /* canceled call from keyboard           */
          }
//     printf("\nM_WAIT4DCD: autobrflag = %d Connect = %d\n",   /*//*/
//           smp->autobrflag, stat232(siop, DCD) );     /*//*/
     if (stat232(siop, DCD) == TRUE)
          printf("CONNECT: Carrier: %s Local: %s  LLP: %s  COMP: %s\n",
                brstr[smp->carrier_baud_code],
                brstr[smp->connect_XXXX_code],
                smp->linkname,
                smp->compressname);

     if (smp->autobrflag == TRUE
        &&  smp->connect_XXXX_code != getbaud(siop)
        &&  stat232(siop, DCD)== TRUE)
          {
          printf("Changing DTE baud rate to %s\n", brstr[smp->connect_XXXX_code]);
          setbaud(siop, smp->connect_XXXX_code);
          }
//     printf("\nM_WAIT4DCD: return code = %d\n", retcode);     /*//*/
     s_ipop(siop);
     return retcode;
}

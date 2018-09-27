/*-50
FUNCTION NAME:  m_cmd
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Builds a modem command in the modem structure's
                command buffer, then outputs it to the SIO.
      RETURNS:  void
     COMMENTS:  The following modem characteristics are forced:
                no command echo, word responses, and a fixed inter-uint8 delay
                and uppercase ASCII output.  Commands are echoed to
                the console based upon the cmdechoflag structure member.
*/

#include <stdio.h>
#include <string.h>
#include <sio/siodef.h>
#include <sio/modem.h>
#include <sio/sioctl.h>

void m_cmd(SIO *siop, char *cmdstr)
{
     struct modem *smp = siop->sm;                /* notational convenience  */
     RANK dtr_stat;                               /* save state of dtr       */
     if ((dtr_stat = get232(siop, DTR)) == OFF)   /* if dtr inhibited now... */
          set232(siop, DTR, ON);                  /* assert it               */
     s_opush(siop);                               /* preserve output struct  */
     s_ocntrl(siop, SET, CASEMODE, UPPER);        /* convert to upper case   */
     s_ocntrl(siop, SET, ASCIIFLAG, ON);          /* strip high bits         */
     s_ocntrl(siop, SET, IB_DLYFLAG, ON);         /* interuint8_t delay         */
     s_ocntrl(siop, SET, IB_DLY, smp->ibdelay);
     s_ocntrl(siop, SET, CONSFLAG, (uint16_t)smp->cmdechoflag); /* echo      */
     sprintf(smp->cmdbuff,"ATQ0E1V1%s\r", cmdstr);
     s_fputs(siop, smp->cmdbuff);                 /* output buffer to SIO    */
     if (dtr_stat == OFF)                         /* restore DTR             */
          set232(siop, DTR, OFF);
     s_opop(siop);                                /* restore output struct   */
}

/*-
FUNCTION NAME:  m_config
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Configures the modem as described in the modem structure.
      RETURNS:  int--M_SUCCEED or M_FAIL
     COMMENTS:  Builds two configuration strings: pri_config containing
                commands that are recognized by all modems, and
                sec_config containing commands that are supported by
                only some.  Note that sec_config must be sent first.
*/

#include <stdio.h>  /*//*/
#include <stdlib.h>
#include <sio/siodef.h>
#include <string.h>
#include <sio/modem.h>
#include <sio/sioctl.h>

int m_config(SIO *siop)
{
     struct modem *smp = siop->sm;
     int errcode = M_SUCCEED;
     char *pri_config, *sec_config;
     puts("Entering M_CONFIG");         /*//*/
     strcpy(smp->okalpha, ",*#()-R");        /* chars common to all          */
     if ( (pri_config = (char *)malloc(CMDBUFSIZ)) == NIL)
          return M_CONFIG_MEM;
     if ( (sec_config = (char *)malloc(CMDBUFSIZ)) == NIL)
          return M_CONFIG_MEM;
     s_opush(siop);
     s_ocntrl(siop, SET, IL_DLYFLAG, OFF);
     set232(siop, DTR, ON);

/* Build modem-indepenent primary string */
     sprintf(pri_config,"M%dS0=%dS2=%dS6=%dS7=%d",
             smp->speaker_arg, smp->autoans_arg,
             smp->escape_arg, smp->dtwait_arg,  smp->dcdwait_arg
             );

/* Build modem-dependent secondary string */
     switch (smp->modtype)
          {
          case ID_12:
               smp->xcmd_arg = 1;            /* only X1 supported            */
               sprintf(sec_config,"X%d", smp->xcmd_arg);
               break;
          case ID_12PLUS: strcat(smp->okalpha, "/!@W");
               sprintf(sec_config,"X%dL%d",
               smp->xcmd_arg,
               smp->speakvol_arg);
               break;
          case ID_14K4:
          case ID_24:
          case ID_96:
         strcat(smp->okalpha, "/!@WABCD");
               sprintf(sec_config,"&FX%dL%d&D%d&C%d", smp->xcmd_arg,
                      smp->speakvol_arg,smp->firmdtr_arg, smp->firmdcd_arg);
               break;
          }

     errcode |= m_cmd_OK(siop, sec_config);       /* Send secondary first!   */
     free(sec_config);
//     printf("~!m_config: %d-uint8 sec-config sent at %d, errcode =  %s\n",strlen(pri_config), getbaud(siop),errcode ?"FAIL":"OK"); /*//*/
//     printf("m_config: sec_config: %s\n", sec_config);      /*//*/
     errcode |= m_cmd_OK(siop, pri_config);
     free(pri_config);
//     printf("m_config: %d-uint8 Pri-config sent at %d, errcode =  %s\n",strlen(pri_config), getbaud(siop),errcode ?"FAIL":"OK");   /*//*/
//     printf("m_config: pri_config: %s\n", pri_config);      /*//*/

     switch (smp->baudmode)                  /* set baud rate                */
          {
          case BAUD_MAX:                     /* to modem's highest speed     */
               setbaud(siop, smp->max_carrier_speed);
               break;
          case BAUD_FOUND:                   /* where modem reset            */
               setbaud(siop, smp->max_DTE_baud);
               break;
          }
     set232(siop, DTR, ON);
     errcode |= m_cmd_OK(siop, "");          /* Send AT at current baud rate */
     if (errcode == M_SUCCEED)
          smp->configokflag = TRUE;          /* broadcast init               */
     set232(siop, DTR, OFF);  /* inhibit DTR                  */
//     printf("m_config: Final AT sent at %d; exiting with errcode = %s\n", getbaud(siop),errcode ?"FAIL":"OK");/*//*/
     s_opop(siop);
     if (errcode != M_SUCCEED)
          errcode = M_CONFIG_NOK;
//     puts("Exiting M_CONFIG");       /*//*/
     return errcode;                         /* return 0 if "OK"             */
}

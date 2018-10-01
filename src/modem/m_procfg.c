/*-

FUNCTION NAME:  m_protoconfig
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Configures a modem for protocol operation.
      RETURNS:  int--M_SUCCEED or M_FAIL
     COMMENTS:
*/

#define PROTO_ENABLE          "&Q5"
#define SPEED_SELECT          "N1S37=0"
#define PROTO_SEL             "S46=136"
#define NEGOTIATION           "S48=7"
#define FALLBACK              "S36=5"
#define COMPRESSION           "S46=138"
#define EXTEND_MSG            "W1S95=44"

#include <stdio.h>            /*//*/
#include <stdlib.h>
#include <sio/siodef.h>
#include <string.h>
#include <sio/modem.h>
#include <sio/sioctl.h>

int m_protoconfig(SIO *siop)
{
     int bozo;                    /*//*/
     struct modem *smp = siop->sm;
     int errcode = M_SUCCEED;
	 char *flowcmd, *proto_config;
     puts("Entering m_protoconfig");             /*//*/
     if (smp->linkprot_wanted == FALSE)
        return M_SUCCEED;
     if (smp->max_carrier_speed < BAUD2400)
          return M_SUCCEED;
     if ( (proto_config = (char *)malloc(CMDBUFSIZ)) == NIL)
          return M_CONFIG_MEM;
     s_opush(siop);
     s_ocntrl(siop, SET, IL_DLYFLAG, OFF);
     set232(siop, DTR, ON);
     smp->linkprot_supported = smp->compress_supported = FALSE;

/* Probe for Link-Layer Protocol Services */

     if ( (errcode |= bozo = m_cmd_OK(siop, PROTO_ENABLE)) == M_SUCCEED)
          {
          smp->linkprot_supported = TRUE;
          strcpy(proto_config, PROTO_ENABLE);
          printf("Q5 %s\n", bozo ? "Failed" : "Succeeded");       /*//*/
          if ( (errcode |= bozo = m_cmd_OK(siop, NEGOTIATION)) == M_SUCCEED)
               strcat(proto_config, NEGOTIATION);
          printf("S48=7 %s\n", bozo ? "Failed" : "Succeeded");    /*//*/
          if ( (errcode |= bozo = m_cmd_OK(siop, FALLBACK)) == M_SUCCEED)
               strcat(proto_config, FALLBACK);
          printf("FALLBACK %s\n", bozo ? "Failed" : "Succeeded"); /*//*/
          }
      if (errcode == M_FAIL)
          goto EXIT;

/* Probe for Compression */
     if (smp->compress_wanted)
         {
         if ( (errcode |= bozo = m_cmd_OK(siop, COMPRESSION)) == M_SUCCEED)
             {
             smp->compress_supported = TRUE;
             strcat(proto_config, COMPRESSION);
             printf("COMPRESSION %s\n", bozo ? "Failed" : "Succeeded"); /*//*/
             }
         }

/* Probe for Flow Control */
    switch (siop->flow_wanted)
    	{
    	case NO_FLOW : flowcmd = "&K0";  break;
    	case XON_XOFF: flowcmd = "&K4";  break;
    	case RTS_CTS : flowcmd = "&K3";  break;
    	default:       flowcmd = "&K0";  break;
        }
    if ( (errcode |= bozo = m_cmd_OK(siop, flowcmd)) == M_SUCCEED)
    	strcat(proto_config, flowcmd);
     printf("Flow command %s\n", bozo ? "Failed" : "Succeeded");   /*//*/

/* Probe for Physical-Layer Conditioning */
     if ( (errcode |= bozo = m_cmd_OK(siop, SPEED_SELECT)) == M_SUCCEED)
          strcat(proto_config, SPEED_SELECT);
          printf("SPEED_SELECT %s\n", bozo ? "Failed" : "Succeeded");   /*//*/

     if ( ( errcode |= bozo = m_cmd_OK(siop, EXTEND_MSG)) == M_SUCCEED)
          strcat(proto_config, EXTEND_MSG);
     printf("S95=44 %s\n", bozo ? "Failed" : "Succeeded");            /*//*/

     errcode |= m_cmd_OK(siop, proto_config);   /* send primary to modem */
     printf("m_protoconfig: %zd-uint8 proto-config sent at %d, errcode =  %s\n",strlen(proto_config), getbaud(siop), errcode ?"FAIL":"OK"); /*//*/
     printf("m_protoconfig: Ter-config: %s\n", proto_config);      /*//*/
EXIT:
     free(proto_config);
     s_opop(siop);
     puts("Exiting m_protoconfig");               /*//*/
     return (errcode ? M_CONFIG_NOK : M_SUCCEED);
}

/*-44

FUNCTION NAME:  m_whoru
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Queries modem to ascertain its identity. The results
                are stored in the modem structure.
      RETURNS:  int:  M_FAIL if the response is unidentifiable;
                otherwise M_SUCCEED.
     COMMENTS:  Only the first two digits in the product ID are
                used.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sio\siodef.h>
#include <sio\modem.h>
#include <sio\misc.h>

int m_whoru(SIO *siop)
{
     struct modem *smp = siop->sm;
     int errcode = M_SUCCEED;
     char id_string[MAX_MSG_LEN+1];
     puts("Entering M_WHORU");
     set232(siop, DTR, ON);
     m_cmd_str(siop, "I0", id_string, MAX_MSG_LEN);  /* get ID  */
     if (id_string == NIL)
        return M_FAIL;
     id_string[2] = NUL;                    /* First two characters      */
     switch (str_atoi(id_string))           /* Convert string to integer */
          {
          case 12: smp->modtype  = ID_12;
               smp->max_carrier_speed = BAUD1200;
               break;
          case 13: smp->modtype = ID_12PLUS;
               smp->max_carrier_speed = BAUD1200;
               break;
          case 14: smp->modtype = ID_14K4;
               smp->max_carrier_speed = BAUD14K4;
               break;
          case 24: smp->modtype = ID_24;
               smp->max_carrier_speed = BAUD2400;
               break;
          case 96: smp->modtype = ID_96;
               smp->max_carrier_speed = BAUD9600;
               break;
          default: smp->modtype = ID_UNKNOWN;
               smp->max_carrier_speed = BAUD300;
               errcode = M_FAIL;
               break;
          }
     puts("Exiting M_WHORU");
     return errcode;
}

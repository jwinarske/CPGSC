/*-
FUNCTION NAME:  m_parsemsg
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Parses CONNECT, CARRIER, PROTOCOL, and COMPRESSION
                messages into constituent parts.
      RETURNS:  void
     COMMENTS:
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sio/siodef.h>
#include <sio/modem.h>
#include <sio/misc.h>

void m_parsemsg(SIO *siop, struct parse_info *msgp, char * modemstr)
{
     short baudcode;
     struct modem *smp = siop->sm;
     char *parsep, *destp;
     switch (msgp->id)
          {
          case M_CONN:
          case M_CARRIER:
               baudcode = br_to_bcode(str_atoi(modemstr));
               if(baudcode == -1 )
                    printf("M_parsemsg: baudrate not in table\n");
               else
                   {
                   if (msgp->id == M_CONN)
                      smp->connect_XXXX_code = baudcode;
                   else
                      smp->carrier_baud_code = baudcode;
                    }
               break;
          case M_PROTOCOL:
          case M_COMPRESS:
               parsep = strchr(modemstr,':');
               if (parsep == NIL)
                    break;
               if (msgp->id == M_PROTOCOL)
               	    destp = &smp->linkname[0];
               else
                    destp = &smp->compressname[0];
               while (*++parsep != '\0')
                    {
                    if (*parsep == ' ' || iscntrl(*parsep))
                         continue;
                    *destp++ = *parsep;
                    }
               *destp = '\0';
               break;
          }
}

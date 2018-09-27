/*-
FUNCTION NAME:  get232
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Fetch current state of RS-232 outputs.
      RETURNS:  int:  0 if successful.  OR_ARG if argument is out
                of range;  BAD_FCN if the function is not supported
                (SIO pointer is NIL).
*/

#include <sio/siodef.h>

RANK get232(SIO *siop, RANK whichone)
{
     RANK retval = BAD_FCN;
     switch (whichone)
          {
          case  DTR:
               if (siop->dtr != NIL)
                    retval = (siop->dtr->now);
               break;
          case  RTS:
               if (siop->rts != NIL)
                    retval = (siop->rts->now);
               break;
          case  GPO1:
               if (siop->gpo1 != NIL)
                    retval = (siop->gpo1->now);
               break;
          case  GPO2:
               if (siop->gpo2 != NIL)
                    retval = (siop->gpo2->now);
               break;
          default:
               retval = OR_ARG;
          }
     return retval;
}

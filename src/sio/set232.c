/*-
FUNCTION NAME:  set232
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Set RS-232 output pins.
      RETURNS:  short: 0 if successful.  OR_ARG if either argument is out
                of range;  BAD_FCN if the function is not supported.
*/


#include <sio/siodef.h>
#include <sio/buos.h>
#include <sio/level0.h>        /* for timing constants */

short set232(SIO* siop, RANK whichone, bool state)
{
    short retval = 0;
    struct vout232_ *p232 = NIL;
    switch (whichone) {

        case  DTR:
            p232 = siop->dtr;
//               if (siop->dtr != NIL)
//                    retval =  vset232(siop, siop->dtr, state);
            break;
        case  RTS:
            p232 = siop->rts;
//               if (siop->rts != NIL)
//                    retval =  vset232(siop, siop->rts, state);
            break;
        case  GPO1:
            p232 = siop->gpo1;
//               if (siop->gpo1 != NIL)
//                    retval = vset232(siop, siop->gpo1, state);
            break;
        case  GPO2:
            p232 = siop->gpo2;
//               if (siop->gpo2 != NIL)
//                    retval =  vset232(siop, siop->gpo2, state);
            break;
        case  BRK:
            p232 = siop->brkbit;
//               if (siop->brkbit != NIL)
//                    {
//                    vset232(siop, siop->brkbit, ON);
//                    __delay(_0_SEC_3);
//                    retval =  vset232(siop, siop->brkbit, OFF);
//                    }
            break;
        default:
            retval  = OR_ARG;
    }

    if ( (p232 != NIL) && (retval == 0)) {

        if (whichone != BRK) {

            retval = vset232(siop, p232, state);
        }
        else {
            
            vset232(siop, p232, ON);
            __delay(_0_SEC_3);
            retval = vset232(siop, p232, OFF);
        }
    }

    return retval;
}

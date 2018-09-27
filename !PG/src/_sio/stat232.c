/*-
FUNCTION NAME:  stat232
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Returns current state of an RS232 input.
      RETURNS:  short:  the state of the input (ON or OFF);
                BAD_FCN or OR_ARG if the function is not supported or if
                the rank argument is out of range.
*/

#include <sio/siodef.h>
#include <sio/buos.h>

short stat232(SIO *siop, RANK whichone)
{
     short retval;
     switch (whichone)
          {
          case  CTS: retval = vstat232(siop, siop->cts);  break;
          case  DCD: retval = vstat232(siop, siop->dcd);  break;
          case  DSR: retval = vstat232(siop, siop->dsr);  break;
          case   RI: retval = vstat232(siop, siop->ri);   break;
          case GPI1: retval = vstat232(siop, siop->gpi1); break;
          case GPI2: retval = vstat232(siop, siop->gpi2); break;
          default: retval = OR_ARG;
          }
     return retval;
}

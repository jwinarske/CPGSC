/*-
FUNCTION NAME:  setformat
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  This function sets the respective data format elements.
      RETURNS:  short:  the rank of the setting as defined in
                SIODEF.H. BAD_FCN or BAD_ARG if the function is
                not supported.
*/

#include <sio/siodef.h>
#include <sio/buos.h>

short setformat(SIO *siop, RANK whichone, RANK newval)
{
     short retval;
     switch(whichone)
          {
          case STOPS:   return vsetbits(siop, siop->sb, newval);
          case DATALEN: return vsetbits(siop, siop->dl, newval);
          case PARITY:  return vsetbits(siop, siop->par, newval);
          default:      retval = OR_ARG;
          }
     return retval;
}

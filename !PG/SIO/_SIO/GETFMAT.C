/*-
FUNCTION NAME:  getformat
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Returns current setting of data format element
      RETURNS:  int:  0 if successful.  OR_ARG if argument is out
                of range;  BAD_FCN if the function is not supported
                (SIO pointer is NIL).
*/

#include <sio\siodef.h>

short getformat(SIO *siop, RANK whichone)
{
     short retval = BAD_FCN;
     switch(whichone)
          {
          case STOPS:
               if (siop->sb != NIL)
                    retval = siop->sb->now;
               break;
          case DATALEN:
               if (siop->dl != NIL)
                    retval = siop->dl->now;
               break;
          case PARITY:
               if (siop->par != NIL)
                    retval = siop->par->now;
               break;
          default:
               retval = OR_ARG;
          }
     return retval;
}

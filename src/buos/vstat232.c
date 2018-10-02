/*-
FUNCTION NAME:  vstat232
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Return status of RS-232 input described in p232.
   PARAMETERS:  *p232: pointer to a vin232_ structure
      RETURNS:  int:  TRUE if the input is asserted, FALSE if inhibited;
                BAD_FCN if the RS-232 input requested is not supported.
     COMMENTS:  The call to the level 1 function is through a function
                pointer in the vin232_ structure.
*/


#include "sio/siodef.h"

short vstat232(SIO *siop, struct vin232_ *p232)
{
    if (p232 == NIL)
        return BAD_FCN;                    /* this input not supported     */
    if (siop->read232 != NIL)
        p232->now = (uint8_t) (*siop->read232)(siop, p232) & p232->mask;
        
    return (p232->now  ? TRUE : FALSE);     /* return status                */
}

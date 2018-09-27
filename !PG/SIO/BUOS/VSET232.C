/*-
FUNCTION NAME:  vset232
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Turns selected RS-232 output ON or OFF.
      RETURNS:  int: OR_ARG if state argument is other than 0 or 1;
                BAD_FCN if the requested function is not supported in
                hardware; otherwise 0.
     COMMENTS:  The test for a NIL pointer must be the first test.
                OFF and ON are defined in SIODEF.H
*/

#include <sio\siodef.h>
#include <sio\uart.h>


int vset232(SIO *siop, struct vout232_ *p232, BOOL state)
{
     if (p232 == NIL)
          return BAD_FCN;
     if (state != OFF && state != ON)           /* range check                   */
          return OR_ARG;
     siop->v_regp[p232->vregnum][VIR] &= p232->resetmask;  /* reset bit     */
     if (state == ON)
          siop->v_regp[p232->vregnum][VIR] |= ~p232->resetmask;  /* set bit */
     p232->now = state;                    /* update current state variable */
     _vset232(siop, p232, siop->v_regp[p232->vregnum][VIR]);

     return 0;
}

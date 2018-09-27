/*-
FUNCTION NAME:  vsetbits
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Builds a new bit pattern in the virtual register in
                v_regp by ANDing and ORing, then calls the level-0
                _setbits, to install that bit pattern in the physical
                UART's register.
      RETURNS:  int:  0 if successful OR_ARG if argument is out of
                range;  BAD_FCN if the function is not supported (SIO
                pointer is NIL); BAD_ARG if the requested setting is not
                supported by hardware (mask initialized to -1).
     COMMENTS:  More than one virtual register may be attached to a
                function by the linked list of next pointers.
*/

#include <sio\siodef.h>
#include <sio\uart.h>

int vsetbits(SIO *siop, struct vregbits_ *rbp, RANK rank)
{
     REG tmp;
     if (rbp == NIL)                   /* function not supported in hardware */
          return BAD_FCN;
     if ( rank >= NUMMASKS)            /* argument range check               */
          return OR_ARG;
     if (rbp->setmask[rank] == -1)     /* argument not supported in hardware */
          return BAD_ARG;
     do
          {
          siop->v_regp[rbp->vregnum][VIR] &= rbp->resetmask; /* reset bits   */
          tmp = siop->v_regp[rbp->vregnum][VIR] |= rbp->setmask[rank];
          rbp->now = rank;              /* update current table rank         */
          _vsetbits(siop, rbp, tmp);     /* write vreg to the UART            */
          rbp = rbp->next;              /* another structure involved?       */
          } while (rbp != NIL);         /* no, done                          */
     return 0;
}

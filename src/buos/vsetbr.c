/*-
FUNCTION NAME:  vsetbr
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Sets the baud rate to the rank element of the
                structure's divisor array.  Passes high- and low-order
                divisors to level 1 function, _vsetbr
      RETURNS:  int:  0 if successful.  OR_ARG if argument is out
                of range;  BAD_FCN if the function is not supported
                (SIO pointer is NIL); BAD_ARG if the requested setting
                is not supported by hardware (divisor is -1).
     COMMENTS:  The rank argument is an index for the array of divisors,
                constants for that reside in SIODEF.H.  Notice that
                the low uint8_t is passed before the high uint8_t.
*/

#include <sio/siodef.h>
#include <sio/uart.h>

int vsetbr(SIO *siop, struct vbaud_ *brp, RANK rank) /* rank of value to install  */
{
    REG brlo, brhi;                   /* intermediates simplify syntax     */
    if (brp == NIL)                  /* baud rate not supported in hardware */
        return BAD_FCN;
    if ( rank >= NUMBAUDS)             /* requested rank out of range       */
        return OR_ARG;
    if (brp->divisor[rank][1] == -1 || brp->divisor[rank][0] == -1)
        return BAD_ARG;              /* request baud rate not available   */
    brlo =  brp->divisor[rank][1];     /* lo uint8_t of divisor                */
    brhi =  brp->divisor[rank][0];     /* lo uint8_t of divisor                */
    brp->now = rank;                   /* update baud in effect             */
    _vsetbr(siop, brp, brlo, brhi);    /* call level-1 to do it             */
    
    return 0;
}

#ifdef DEBUG
..#include <stdio.h>
..void printbauds(SIO *siop)
..
{
     ..int i;
     ..for (i=0; i<NUMBAUDS; i++)
          ..printf("%d:  %x   %x \n", i, siop->br->divisor[i][0], siop->br->divisor[i][1]);
     ..
}
#endif

/*-

FUNCTION NAME:  s_opush, s_opop
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Save and restore s_octl structures on local stack.
      RETURNS:  int: 0 if stack operation was successful; otherwise 1.
     COMMENTS:  Both functions check for balance of the local stack, so
                take care that every "push" is balanced with
                a corresponding "pop."
*/

#include <stdio.h>
#include <stdlib.h>
#include <sio\siodef.h>
#include <sio\sioctl.h>


static struct soctl_ *ostack[IO_STKSIZ] = { NIL }; /* init 1st element to NIL  */
static struct soctl_ **ostackp = ostack;         /* pointer to top of stack  */


int s_opush(SIO *siop)
{
     if (ostackp >= &ostack[IO_STKSIZ])        /* check for end of array       */
          {
          puts("\aOstack overflow.");
          return 1;
          }
     *ostackp = (struct soctl_ *)malloc(sizeof(struct soctl_)); /* get mem   */
     if (*ostackp == NIL)                    /* out of memory                */
          return 1;
     **ostackp = *siop->s_octl;              /* make copy in allocated memory*/
     ++ostackp;                              /* point to next slot           */
     return 0;
}

int s_opop(SIO *siop)
{
     if (ostackp <= ostack)             /* don't let stack become unbalanced */
          {
          puts("\aIstack underflow.");
          return 1;
          }
     --ostackp;                         /* point at first active element     */
     *siop->s_octl = **ostackp;         /* restore old structure from stack  */
     free((VOID*) *ostackp);                    /* release allocated memory          */
     return 0;
}

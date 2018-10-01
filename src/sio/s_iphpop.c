/*-

FUNCTION NAME:  s_ipush, s_ipop
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Save and restore s_ictl structures on local stack.
      RETURNS:  int: 0 if stack operation was successful; otherwise 1.
     COMMENTS:  Both funtions check for balance of the local stack, so
                take care that every "push" is balanced with
                a corresponding "pop."

*/
#include <stdio.h>
#include <stdlib.h>
#include <sio/siodef.h>
#include <sio/sioctl.h>

static struct sictl_ *istack[IO_STKSIZ] = { NIL }; /* init 1st element to NIL  */
static struct sictl_ **istackp = istack;         /* pointer to top of stack  */

int s_ipush(SIO *siop)
{
     if (istackp >= &istack[IO_STKSIZ])
          {
          puts("\aIstack overflow.");
          return 1;
          }
     *istackp = (struct sictl_ *)malloc(sizeof(struct sictl_));
     if (*istackp == NIL)
          return 1;
     **istackp = *siop->s_ictl;
     ++istackp;
     return 0;
}

int s_ipop(SIO *siop)
{
     if (istackp <= istack)
          {
          puts("\aIstack underflow.");
          return 1;
          }
     --istackp;
     *siop->s_ictl = **istackp;
     free((VOID*)*istackp);
     return 0;
}

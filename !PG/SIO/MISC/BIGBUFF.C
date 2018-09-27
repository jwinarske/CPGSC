/*-
FUNCTION NAME:  bigbuff
 PROTOTYPE IN:  MISC.H
        LEVEL:  3
      LIBRARY:  MISC.LIB
  DESCRIPTION:  Allocate large buffer.
      RETURNS:  char *: the address of the allocated buffer or NIL if
                no memory available.
     COMMENTS:  Allocates nblks of memory, in  blksize chunks.  The
                headroom argument is the number of blksize chunks
                to return to the system for local use.  The actual number
                of blocks allocated is returned to the caller with the
                pointer numblkp.
*/

#include <stdlib.h>
#include <sio\siodef.h>

/*1: block size for allocation         */
/*2: number of blocks NOT to allocate  */
/*3: pointer caller's count variable   */

char *bigbuff(USHORT blksize, USHORT headroom, USHORT *numblkp)
{
     char *p;
     unsigned nblks = 1;
     while ( (p = malloc(nblks * blksize)) != NIL)     /* call until failure */
          {
          free((VOID*)p);                             /* release it                   */
          ++nblks;                            /* ask for more next time       */
          }
     if (headroom >= --nblks)                /* not enough memory            */
          {
          nblks = 0;
          return NIL;
          }
     nblks -= headroom;                      /* adjust for headroom          */
     *numblkp = nblks;                       /* pass back to caller          */
     return (malloc(nblks * blksize));      /* allocate & return the pointer */
}

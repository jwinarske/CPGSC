/*-
FUNCTION NAME:  mk_crctbl
        LEVEL:  3
 PROTOTYPE IN:  CRC.H
      LIBRARY:  CRC.LIB
  DESCRIPTION:  Builds a CRC look up table based upon specified polynomial
                and CRC function.
      RETURNS:  uint16_t*: a pointer to the table.
     COMMENTS:  Each table element contains the CRC of its rank in the
                table. For example, element 50 contains the CRC of 50.
*/

#include <stdlib.h>           /* for malloc function prototype */
#include "sio/siodef.h"


/*3: pointer to CRC function      */

uint16_t *mk_crctbl( uint16_t poly, uint16_t (*crcfn)(uint16_t, uint16_t, uint16_t) )
{
    uint16_t *crctp;                  /* pointer to the table         */
    int i;
    if ( (crctp = (uint16_t *)malloc(256 * sizeof(unsigned))) == NIL)
        return NIL;
    for (i = 0; i < 256; i++ )         /* fill table with CRCs of values... */
        crctp[i] = (*crcfn)(i, poly, 0);  /* ... 0 -255                     */
    return crctp;                    /* return a table to the pointer     */
}

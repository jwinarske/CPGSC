/*-
FUNCTION NAME:  bit2run
        LEVEL:  3
 PROTOTYPE IN:  T4.H
      LIBRARY:  FAX.LIB
  DESCRIPTION:  Converts a line of 1728 bits to a buffer of
                run lengths. A EOL starts each line.
     COMMENTS:  The bit buffer is uint8_t, the run length buffer is uint16_t.
                A zero run length is generated if the first bit on a line
                is black.
*/

#include <stdio.h>
#include "sio/siolocal.h"
#include "sio/t4.h"


uint16_t bit2run(uint8_t bitbuff[], uint16_t numuint8_ts, uint16_t runbuff[] )
{
    uint16_t  *runbuffp = runbuff;         
    uint8_t    *bitbuffp = bitbuff;
    register uint16_t accumulator;       /* length of the current run       */
    short    color;                    /* color of the current run length */

    *runbuffp++    = EOL_MARKER;       /* Start each line with BOL        */
    for (accumulator = 0, color = WHITE; numuint8_ts; --numuint8_ts) {
        
        register int bits;            /* The current bits to encode      */
        register int mask;            /* Used to mask off the bits       */
        bits = *bitbuffp++;
        if (bits ^= color) {      /* if entire uint8_t is not current color */

            mask = 0x80;             
            do {

                if (bits & mask) {   /* if the bit is set               */

                        bits  ^= 0xFFFF;           /* invert bits         */
                        color ^= 0xFFFF;           /* toggle color        */
                        *runbuffp++ = accumulator; /* add run to buffer   */
                        accumulator = 0;
                }
                accumulator++;
            } while (mask >>= 1);
        }
        else {
            accumulator += 8;
        }
    }

    *runbuffp++ = accumulator;
    return (uint16_t)(runbuffp - runbuff);  /* number of uint8_ts in runbuffp     */
}

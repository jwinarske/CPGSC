/*-45
FUNCTION NAME:  run2bits
        LEVEL:  3
 PROTOTYPE IN:  T4.H
      LIBRARY:  FAX.LIB
  DESCRIPTION:  Converts a buffer of run lengths to a line
                of 1728 bits . An EOL starts each line.
     COMMENTS:  The bit buffer is uint8_t, the run length buffer is short.
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "sio/siolocal.h"
#include "sio/t4.h"


#define NUMBITS  8
#define WIDTH    NUMBITS/8
#define BUFF_LEN (bitbufp-bitbuff_start)*WIDTH

int run2bits(FILE *infilep, FILE *outfilep, uint8_t *bitbufp,
             short bitbuf_len, short *runbufp, short runbuffp)
{
    size_t num_read = 0;
    FAST   accum;
    uint16_t accum_len;
    uint8_t  *bitbuff_start = bitbufp;
    short *runbuff_start = runbufp;
    FAST whole_uint8_ts, space_left;       /* For pipelining                */
    uint8_t color;                         /* The color of the current run  */
    register short runlen = 0;          /* The length of the current run */
    register short mask = 0x01;
    space_left = bitbuf_len;
    accum = accum_len = 0;
    while((num_read = fread(runbufp, sizeof(short), runbuffp, infilep)) > 0)
        {
        ++num_read;
         while (--num_read)
            {
            runlen = *runbufp++;
            if (runlen > space_left * NUMBITS)
                {
               if ((int)fwrite(bitbuff_start, 1, BUFF_LEN, outfilep) != BUFF_LEN)
                    return 1;
                space_left = bitbuf_len;
                bitbufp = bitbuff_start;
                }
            if(runlen == EOL_MARKER)       /* Toss EOL codes */
                 {
                 mask = 0x01;
                 color = (uint8_t)BLACK;
                 continue;
                 }
            color = (uint8_t) ~color;         /* Invert color   */
            mask ^= 0x1;                   /* Invert mask    */
            while(runlen)
                 {
                 if ((runlen >= NUMBITS) && (accum_len == 0))
                    {                     /* Pipeline whole uint8_ts  */
                    whole_uint8_ts = runlen/NUMBITS;
                    memset(bitbufp, color, whole_uint8_ts);
                    bitbufp += whole_uint8_ts;
                    space_left -= whole_uint8_ts;
                    runlen = runlen % NUMBITS;
                    }
                 while (runlen)    /* Stay in tight loop here */
                     {
                     accum <<= 1;
                     accum |= mask;
                     ++accum_len;
                     --runlen;
                     if (accum_len == NUMBITS)
                         {
                         *bitbufp++ = (uint8_t)accum;
                         accum = accum_len = 0;
                         --space_left;
                         break;      /* for possible pipleline   */
                         }
                     }
                 }
            }
        runbufp = runbuff_start;
        }
      if (fwrite(bitbuff_start, 1, BUFF_LEN, outfilep) != BUFF_LEN)
         return 1;
    return 0;
}

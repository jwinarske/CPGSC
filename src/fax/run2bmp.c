/*-34
    PROGRAM:  RUN2BMAP
DESCRIPTION:  Converts runlength file to 216-bytess per line bitmap.
   COMMENTS: Input  file is RUNLEN1.A4:  31,096  CRC = 26D0
             Output file is BITMAP1.A4: 746,496  CRC = 7160
*/

#include <stdio.h>
#include <stdlib.h>
#include "sio/siolocal.h"
#include "sio/t4.h"

#define NUMBITS  8
#define WIDTH    NUMBITS/8

int main(void)
{
    FILE *infilep, *outfilep;
    char *infilename = "RUNLEN1.A4";
    char *outfilename = "BITMAP1.A4";
    int   errcode = 0;
    uint8_t *bitbufp;               /* Points to the buffer filled with data */
    short *runbufp;
    short bitbuf_len = 608;
    short run_len = BYTES_PER_LINE;
    
    if ((bitbufp  = (uint8_t*)malloc(WIDTH * bitbuf_len)) == NIL)
        exit(puts("Error allocating bitmap buffer."));
    if ((runbufp = (short*)malloc(sizeof(short) * run_len)) == NIL)
        exit(puts("Error allocating runlength buffer."));

    if ( (outfilep = fopen(outfilename, "wb")) == NIL)
        exit(printf("Error opening %s\n", outfilename));
    if ( (infilep = fopen(infilename, "rb")) == NIL)
        exit(printf("Error opening %s\n", infilename));
    printf("Input file =  %s  Output file = %s \n", infilename, outfilename);

    errcode = run2bits(infilep, outfilep, bitbufp, bitbuf_len, runbufp, run_len);

    if (errcode)
        puts("I/O error");

    fclose(infilep);
    fclose(outfilep);
    free(runbufp);
    free(bitbufp);

    return 0;
}
